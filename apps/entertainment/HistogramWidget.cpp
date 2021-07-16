//
// Created by Raffaele Montella on 16/07/21.
//

#include "HistogramWidget.hpp"

#include <QPainter>
#include <QHBoxLayout>

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

class QAudioLevel : public QWidget
{
Q_OBJECT
public:
    explicit QAudioLevel(QWidget *parent = nullptr);

    // Using [0; 1.0] range
    void setLevel(qreal level);

protected:
    void paintEvent(QPaintEvent *event);

private:
    qreal m_level = 0;
};

QAudioLevel::QAudioLevel(QWidget *parent)
        : QWidget(parent)
{
    setMinimumHeight(15);
    setMaximumHeight(50);
}

void QAudioLevel::setLevel(qreal level)
{
    if (m_level != level) {
        m_level = level;
        update();
    }
}

void QAudioLevel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // draw level
    qreal widthLevel = m_level * width();
    painter.fillRect(0, 0, widthLevel, height(), Qt::red);
    // clear the rest of the control
    painter.fillRect(widthLevel, 0, width(), height(), Qt::black);
}

fairwind::apps::entertainment::HistogramWidget::HistogramWidget(QWidget *parent)
        : QWidget(parent)
{
    m_processor.moveToThread(&m_processorThread);
    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    connect(&m_processor, &FrameProcessor::histogramReady, this, &HistogramWidget::setHistogram);
    m_processorThread.start(QThread::LowestPriority);
    setLayout(new QHBoxLayout);
}

fairwind::apps::entertainment::HistogramWidget::~HistogramWidget()
{
    m_processorThread.quit();
    m_processorThread.wait(10000);
}

void fairwind::apps::entertainment::HistogramWidget::processFrame(const QVideoFrame &frame)
{
    if (m_isBusy && frame.isValid())
        return; //drop frame

    m_isBusy = true;
    QMetaObject::invokeMethod(&m_processor, "processFrame",
                              Qt::QueuedConnection, Q_ARG(QVideoFrame, frame), Q_ARG(int, m_levels));
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
        case QAudioFormat::Unknown:
            break;
        case QAudioFormat::Float:
            if (format.sampleSize() != 32) // other sample formats are not supported
                return qreal(0);
            return qreal(1.00003);
        case QAudioFormat::SignedInt:
            if (format.sampleSize() == 32)
                return qreal(INT_MAX);
            if (format.sampleSize() == 16)
                return qreal(SHRT_MAX);
            if (format.sampleSize() == 8)
                return qreal(CHAR_MAX);
            break;
        case QAudioFormat::UnSignedInt:
            if (format.sampleSize() == 32)
                return qreal(UINT_MAX);
            if (format.sampleSize() == 16)
                return qreal(USHRT_MAX);
            if (format.sampleSize() == 8)
                return qreal(UCHAR_MAX);
            break;
    }

    return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.isValid())
        return values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
        case QAudioFormat::Unknown:
        case QAudioFormat::UnSignedInt:
            if (buffer.format().sampleSize() == 32)
                values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 16)
                values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 8)
                values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
            break;
        case QAudioFormat::Float:
            if (buffer.format().sampleSize() == 32) {
                values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
                for (int i = 0; i < values.size(); ++i)
                    values[i] /= peak_value;
            }
            break;
        case QAudioFormat::SignedInt:
            if (buffer.format().sampleSize() == 32)
                values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 16)
                values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
            if (buffer.format().sampleSize() == 8)
                values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
            break;
    }

    return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

void fairwind::apps::entertainment::HistogramWidget::processBuffer(const QAudioBuffer &buffer)
{
    if (m_audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(m_audioLevels);
        m_audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            QAudioLevel *level = new QAudioLevel(this);
            m_audioLevels.append(level);
            layout()->addWidget(level);
        }
    }

    QVector<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i)
        m_audioLevels.at(i)->setLevel(levels.at(i));
}

void fairwind::apps::entertainment::HistogramWidget::setHistogram(const QVector<qreal> &histogram)
{
    m_isBusy = false;
    m_histogram = histogram;
    update();
}

void fairwind::apps::entertainment::HistogramWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!m_audioLevels.isEmpty())
        return;

    QPainter painter(this);

    if (m_histogram.isEmpty()) {
        painter.fillRect(0, 0, width(), height(), QColor::fromRgb(0, 0, 0));
        return;
    }

    qreal barWidth = width() / (qreal)m_histogram.size();

    for (int i = 0; i < m_histogram.size(); ++i) {
        qreal h = m_histogram[i] * height();
        // draw level
        painter.fillRect(barWidth * i, height() - h, barWidth * (i + 1), height(), Qt::red);
        // clear the rest of the control
        painter.fillRect(barWidth * i, 0, barWidth * (i + 1), height() - h, Qt::black);
    }
}

void fairwind::apps::entertainment::FrameProcessor::processFrame(QVideoFrame frame, int levels)
{
    QVector<qreal> histogram(levels);

    do {
        if (!levels)
            break;

        if (!frame.map(QAbstractVideoBuffer::ReadOnly))
            break;

        if (frame.pixelFormat() == QVideoFrame::Format_YUV420P ||
            frame.pixelFormat() == QVideoFrame::Format_NV12) {
            // Process YUV data
            uchar *b = frame.bits();
            for (int y = 0; y < frame.height(); ++y) {
                uchar *lastPixel = b + frame.width();
                for (uchar *curPixel = b; curPixel < lastPixel; curPixel++)
                    histogram[(*curPixel * levels) >> 8] += 1.0;
                b += frame.bytesPerLine();
            }
        } else {
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
            if (imageFormat != QImage::Format_Invalid) {
                // Process RGB data
                QImage image(frame.bits(), frame.width(), frame.height(), imageFormat);
                image = image.convertToFormat(QImage::Format_RGB32);

                const QRgb* b = (const QRgb*)image.bits();
                for (int y = 0; y < image.height(); ++y) {
                    const QRgb *lastPixel = b + frame.width();
                    for (const QRgb *curPixel = b; curPixel < lastPixel; curPixel++)
                        histogram[(qGray(*curPixel) * levels) >> 8] += 1.0;
                    b = (const QRgb*)((uchar*)b + image.bytesPerLine());
                }
            }
        }

        // find maximum value
        qreal maxValue = 0.0;
        for (int i = 0; i < histogram.size(); i++) {
            if (histogram[i] > maxValue)
                maxValue = histogram[i];
        }

        if (maxValue > 0.0) {
            for (int i = 0; i < histogram.size(); i++)
                histogram[i] /= maxValue;
        }

        frame.unmap();
    } while (false);

    emit histogramReady(histogram);
}

#include "HistogramWidget.moc"