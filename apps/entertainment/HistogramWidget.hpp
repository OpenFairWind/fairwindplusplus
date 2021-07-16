//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_HISTOGRAMWIDGET_HPP
#define FAIRWIND_HISTOGRAMWIDGET_HPP

#include <QThread>
#include <QVideoFrame>
#include <QAudioBuffer>
#include <QWidget>

class QAudioLevel;

namespace fairwind::apps::entertainment {
    class FrameProcessor: public QObject
    {
    Q_OBJECT

    public slots:
        void processFrame(QVideoFrame frame, int levels);

    signals:
        void histogramReady(const QVector<qreal> &histogram);
    };

    class HistogramWidget : public QWidget
    {
    Q_OBJECT

    public:
        explicit HistogramWidget(QWidget *parent = nullptr);
        ~HistogramWidget();
        void setLevels(int levels) { m_levels = levels; }

    public slots:
        void processFrame(const QVideoFrame &frame);
        void processBuffer(const QAudioBuffer &buffer);
        void setHistogram(const QVector<qreal> &histogram);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QVector<qreal> m_histogram;
        int m_levels = 128;
        FrameProcessor m_processor;
        QThread m_processorThread;
        bool m_isBusy = false;
        QVector<QAudioLevel *> m_audioLevels;
    };
}


#endif //FAIRWIND_HISTOGRAMWIDGET_HPP
