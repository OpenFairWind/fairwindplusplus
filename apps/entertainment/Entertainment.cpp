//
// Created by Raffaele Montella on 15/07/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QMessageBox>
#include "Entertainment.hpp"

#include "PlayerControls.hpp"
#include "PlaylistModel.hpp"
#include "HistogramWidget.hpp"
#include "VideoWidget.hpp"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>

/*
 * Returns the application icon
 */
QImage fairwind::apps::entertainment::Entertainment::getIcon() const {
    return QImage(":/resources/images/icons/entertainment_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::entertainment::Entertainment::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Entertainment();
    ui->setupUi(m_widget);

    auto fairwind=FairWind::getInstance();
    auto config = getConfig();

    m_player = new QMediaPlayer(m_widget);
    m_player->setAudioRole(QAudio::VideoRole);
    qInfo() << "Supported audio roles:";
    for (QAudio::Role role : m_player->supportedAudioRoles())
        qInfo() << "    " << role;
    // owned by PlaylistModel
    m_playlist = new QMediaPlaylist();
    m_player->setPlaylist(m_playlist);
//! [create-objs]

    connect(m_player, &QMediaPlayer::durationChanged, this, &fairwind::apps::entertainment::Entertainment::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &fairwind::apps::entertainment::Entertainment::positionChanged);
    connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &fairwind::apps::entertainment::Entertainment::metaDataChanged);
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &fairwind::apps::entertainment::Entertainment::playlistPositionChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &fairwind::apps::entertainment::Entertainment::statusChanged);
    connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &fairwind::apps::entertainment::Entertainment::bufferingProgress);
    connect(m_player, &QMediaPlayer::videoAvailableChanged, this, &fairwind::apps::entertainment::Entertainment::videoAvailableChanged);
    connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &fairwind::apps::entertainment::Entertainment::displayErrorMessage);
    connect(m_player, &QMediaPlayer::stateChanged, this, &fairwind::apps::entertainment::Entertainment::stateChanged);

//! [2]
    m_videoWidget = new VideoWidget(m_widget);
    m_player->setVideoOutput(m_videoWidget);

    m_playlistModel = new PlaylistModel(m_widget);
    m_playlistModel->setPlaylist(m_playlist);
//! [2]

    m_playlistView = new QListView(m_widget);
    m_playlistView->setModel(m_playlistModel);
    m_playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));

    connect(m_playlistView, &QAbstractItemView::activated, this, &fairwind::apps::entertainment::Entertainment::jump);

    m_slider = new QSlider(Qt::Horizontal, m_widget);
    m_slider->setRange(0, m_player->duration() / 1000);

    m_labelDuration = new QLabel(m_widget);
    connect(m_slider, &QSlider::sliderMoved, this, &fairwind::apps::entertainment::Entertainment::seek);

    /*
    m_labelHistogram = new QLabel(m_widget);
    m_labelHistogram->setText("Histogram:");
    m_videoHistogram = new HistogramWidget(m_widget);
    m_audioHistogram = new HistogramWidget(m_widget);
    QHBoxLayout *histogramLayout = new QHBoxLayout;
    histogramLayout->addWidget(m_labelHistogram);
    histogramLayout->addWidget(m_videoHistogram, 1);
    histogramLayout->addWidget(m_audioHistogram, 2);

    m_videoProbe = new QVideoProbe(m_widget);
    connect(m_videoProbe, &QVideoProbe::videoFrameProbed, m_videoHistogram, &HistogramWidget::processFrame);
    m_videoProbe->setSource(m_player);

    m_audioProbe = new QAudioProbe(m_widget);
    connect(m_audioProbe, &QAudioProbe::audioBufferProbed, m_audioHistogram, &HistogramWidget::processBuffer);
    m_audioProbe->setSource(m_player);
    */
    QPushButton *openButton = new QPushButton(tr("Open"), m_widget);

    connect(openButton, &QPushButton::clicked, this, &fairwind::apps::entertainment::Entertainment::open);

    PlayerControls *controls = new PlayerControls(m_widget);
    controls->setState(m_player->state());
    controls->setVolume(m_player->volume());
    controls->setMuted(controls->isMuted());

    connect(controls, &PlayerControls::play, m_player, &QMediaPlayer::play);
    connect(controls, &PlayerControls::pause, m_player, &QMediaPlayer::pause);
    connect(controls, &PlayerControls::stop, m_player, &QMediaPlayer::stop);
    connect(controls, &PlayerControls::next, m_playlist, &QMediaPlaylist::next);
    connect(controls, &PlayerControls::previous, this, &fairwind::apps::entertainment::Entertainment::previousClicked);
    connect(controls, &PlayerControls::changeVolume, m_player, &QMediaPlayer::setVolume);
    connect(controls, &PlayerControls::changeMuting, m_player, &QMediaPlayer::setMuted);
    connect(controls, &PlayerControls::changeRate, m_player, &QMediaPlayer::setPlaybackRate);
    connect(controls, &PlayerControls::stop, m_videoWidget, QOverload<>::of(&QVideoWidget::update));

    connect(m_player, &QMediaPlayer::stateChanged, controls, &PlayerControls::setState);
    connect(m_player, &QMediaPlayer::volumeChanged, controls, &PlayerControls::setVolume);
    connect(m_player, &QMediaPlayer::mutedChanged, controls, &PlayerControls::setMuted);

    /*
    m_fullScreenButton = new QPushButton(tr("FullScreen"), m_widget);
    m_fullScreenButton->setCheckable(true);

    m_colorButton = new QPushButton(tr("Color Options..."), m_widget);
    m_colorButton->setEnabled(false);
    connect(m_colorButton, &QPushButton::clicked, this, &fairwind::apps::entertainment::Entertainment::showColorDialog);
    */

    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(m_videoWidget, 2);
    displayLayout->addWidget(m_playlistView);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);

    /*
    controlLayout->addWidget(m_fullScreenButton);
    controlLayout->addWidget(m_colorButton);
    */

    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(displayLayout);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_slider);
    hLayout->addWidget(m_labelDuration);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);
    /*
    layout->addLayout(histogramLayout);
    */
#if defined(Q_OS_QNX)
    // On QNX, the main window doesn't have a title bar (or any other decorations).
    // Create a status bar for the status information instead.
    m_statusLabel = new QLabel;
    m_statusBar = new QStatusBar;
    m_statusBar->addPermanentWidget(m_statusLabel);
    m_statusBar->setSizeGripEnabled(false); // Without mouse grabbing, it doesn't work very well.
    layout->addWidget(m_statusBar);
#endif

    m_widget->setLayout(layout);

    if (!isPlayerAvailable()) {
        QMessageBox::warning(m_widget, tr("Service not available"),
                             tr("The QMediaPlayer object does not have a valid service.\n"\
                                "Please check the media service plugins are installed."));

        controls->setEnabled(false);
        m_playlistView->setEnabled(false);
        openButton->setEnabled(false);
        /*
        m_colorButton->setEnabled(false);
        m_fullScreenButton->setEnabled(false);
         */
    }

    metaDataChanged();

    return m_widget;
}



QString fairwind::apps::entertainment::Entertainment::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::entertainment::Entertainment::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::entertainment::Entertainment::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::entertainment::Entertainment::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::entertainment::Entertainment::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::entertainment::Entertainment::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::entertainment::Entertainment::getLicense() const {
    return fairwind::AppBase::getLicense();
}

void fairwind::apps::entertainment::Entertainment::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::entertainment::Entertainment::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::entertainment::Entertainment::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::entertainment::Entertainment::getMetaData() {
    return AppBase::getMetaData();
}

bool fairwind::apps::entertainment::Entertainment::isPlayerAvailable() const
{
    return m_player->isAvailable();
}

void fairwind::apps::entertainment::Entertainment::open()
{
    QFileDialog fileDialog(m_widget);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    QStringList supportedMimeTypes = m_player->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls());
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void fairwind::apps::entertainment::Entertainment::addToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) {
        if (isPlaylist(url))
            m_playlist->load(url);
        else
            m_playlist->addMedia(url);
    }
}

void fairwind::apps::entertainment::Entertainment::setCustomAudioRole(const QString &role)
{
    m_player->setCustomAudioRole(role);
}

void fairwind::apps::entertainment::Entertainment::durationChanged(qint64 duration)
{
    m_duration = duration / 1000;
    m_slider->setMaximum(m_duration);
}

void fairwind::apps::entertainment::Entertainment::positionChanged(qint64 progress)
{
    if (!m_slider->isSliderDown())
        m_slider->setValue(progress / 1000);

    updateDurationInfo(progress / 1000);
}

void fairwind::apps::entertainment::Entertainment::metaDataChanged()
{
    if (m_player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2")
                             .arg(m_player->metaData(QMediaMetaData::AlbumArtist).toString())
                             .arg(m_player->metaData(QMediaMetaData::Title).toString()));

        if (m_coverLabel) {
            QUrl url = m_player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            m_coverLabel->setPixmap(!url.isEmpty()
                                    ? QPixmap(url.toString())
                                    : QPixmap());
        }
    }
}

void fairwind::apps::entertainment::Entertainment::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if (m_player->position() <= 5000)
        m_playlist->previous();
    else
        m_player->setPosition(0);
}

void fairwind::apps::entertainment::Entertainment::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        m_playlist->setCurrentIndex(index.row());
        m_player->play();
    }
}

void fairwind::apps::entertainment::Entertainment::playlistPositionChanged(int currentItem)
{
    clearHistogram();
    m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
}

void fairwind::apps::entertainment::Entertainment::seek(int seconds)
{
    m_player->setPosition(seconds * 1000);
}

void fairwind::apps::entertainment::Entertainment::statusChanged(QMediaPlayer::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
        case QMediaPlayer::UnknownMediaStatus:
        case QMediaPlayer::NoMedia:
        case QMediaPlayer::LoadedMedia:
            setStatusInfo(QString());
            break;
        case QMediaPlayer::LoadingMedia:
            setStatusInfo(tr("Loading..."));
            break;
        case QMediaPlayer::BufferingMedia:
        case QMediaPlayer::BufferedMedia:
            setStatusInfo(tr("Buffering %1%").arg(m_player->bufferStatus()));
            break;
        case QMediaPlayer::StalledMedia:
            setStatusInfo(tr("Stalled %1%").arg(m_player->bufferStatus()));
            break;
        case QMediaPlayer::EndOfMedia:
            QApplication::alert(m_widget);
            break;
        case QMediaPlayer::InvalidMedia:
            displayErrorMessage();
            break;
    }
}

void fairwind::apps::entertainment::Entertainment::stateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState)
        clearHistogram();
}

void fairwind::apps::entertainment::Entertainment::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
        status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        m_widget->setCursor(QCursor(Qt::BusyCursor));
    else
        m_widget->unsetCursor();
#endif
}

void fairwind::apps::entertainment::Entertainment::bufferingProgress(int progress)
{
    if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
        setStatusInfo(tr("Stalled %1%").arg(progress));
    else
        setStatusInfo(tr("Buffering %1%").arg(progress));
}

void fairwind::apps::entertainment::Entertainment::videoAvailableChanged(bool available)
{
    /*
    if (!available) {
        disconnect(m_fullScreenButton, &QPushButton::clicked, m_videoWidget, &QVideoWidget::setFullScreen);
        disconnect(m_videoWidget, &QVideoWidget::fullScreenChanged, m_fullScreenButton, &QPushButton::setChecked);
        m_videoWidget->setFullScreen(false);
    } else {
        connect(m_fullScreenButton, &QPushButton::clicked, m_videoWidget, &QVideoWidget::setFullScreen);
        connect(m_videoWidget, &QVideoWidget::fullScreenChanged, m_fullScreenButton, &QPushButton::setChecked);

        if (m_fullScreenButton->isChecked())
            m_videoWidget->setFullScreen(true);
    }
    m_colorButton->setEnabled(available);
     */
}

void fairwind::apps::entertainment::Entertainment::setTrackInfo(const QString &info)
{
    m_trackInfo = info;

    if (m_statusBar) {
        m_statusBar->showMessage(m_trackInfo);
        m_statusLabel->setText(m_statusInfo);
    } else {
        if (!m_statusInfo.isEmpty())
            m_widget->setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
        else
            m_widget->setWindowTitle(m_trackInfo);
    }
}

void fairwind::apps::entertainment::Entertainment::setStatusInfo(const QString &info)
{
    m_statusInfo = info;

    if (m_statusBar) {
        m_statusBar->showMessage(m_trackInfo);
        m_statusLabel->setText(m_statusInfo);
    } else {
        if (!m_statusInfo.isEmpty())
            m_widget->setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
        else
            m_widget->setWindowTitle(m_trackInfo);
    }
}

void fairwind::apps::entertainment::Entertainment::displayErrorMessage()
{
    setStatusInfo(m_player->errorString());
}

void fairwind::apps::entertainment::Entertainment::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || m_duration) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
                          currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
                        m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    m_labelDuration->setText(tStr);
}

void fairwind::apps::entertainment::Entertainment::showColorDialog()
{
    /*
    if (!m_colorDialog) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(m_videoWidget->brightness());
        connect(brightnessSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setBrightness);
        connect(m_videoWidget, &QVideoWidget::brightnessChanged, brightnessSlider, &QSlider::setValue);

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(m_videoWidget->contrast());
        connect(contrastSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setContrast);
        connect(m_videoWidget, &QVideoWidget::contrastChanged, contrastSlider, &QSlider::setValue);

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(m_videoWidget->hue());
        connect(hueSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setHue);
        connect(m_videoWidget, &QVideoWidget::hueChanged, hueSlider, &QSlider::setValue);

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(m_videoWidget->saturation());
        connect(saturationSlider, &QSlider::sliderMoved, m_videoWidget, &QVideoWidget::setSaturation);
        connect(m_videoWidget, &QVideoWidget::saturationChanged, saturationSlider, &QSlider::setValue);

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        m_colorDialog = new QDialog(m_widget);
        m_colorDialog->setWindowTitle(tr("Color Options"));
        m_colorDialog->setLayout(layout);

        connect(button, &QPushButton::clicked, m_colorDialog, &QDialog::close);
    }
    m_colorDialog->show();
     */
}

void fairwind::apps::entertainment::Entertainment::clearHistogram()
{
    /*
    QMetaObject::invokeMethod(m_videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
    QMetaObject::invokeMethod(m_audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
     */
}