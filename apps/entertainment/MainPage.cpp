//
// Created by Raffaele Montella on 13/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

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

#include "MainPage.hpp"
#include "ui_MainPage.h"
#include "Entertainment.hpp"

namespace fairwind::apps::entertainment {
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {
        ui->setupUi((QWidget *)this);

        auto *widget = (QWidget *)this;

        m_player = new QMediaPlayer(widget);
        m_player->setAudioRole(QAudio::VideoRole);

        qInfo() << "Supported audio roles:";
        for (QAudio::Role role : m_player->supportedAudioRoles())
            qInfo() << "    " << role;

        // owned by PlaylistModel
        m_playlist = new QMediaPlaylist();
        m_player->setPlaylist(m_playlist);

        m_videoWidget = new VideoWidget(widget);
        m_player->setVideoOutput(m_videoWidget);

        m_playlistModel = new PlaylistModel(widget);
        m_playlistModel->setPlaylist(m_playlist);
        ui->playlistView->setModel(m_playlistModel);
        ui->playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));

        ui->slider->setRange(0, m_player->duration() / 1000);

        connect(m_player, &QMediaPlayer::durationChanged, this, &fairwind::apps::entertainment::MainPage::durationChanged);
        connect(m_player, &QMediaPlayer::positionChanged, this, &fairwind::apps::entertainment::MainPage::positionChanged);
        connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &fairwind::apps::entertainment::MainPage::metaDataChanged);
        connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &fairwind::apps::entertainment::MainPage::playlistPositionChanged);
        connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &fairwind::apps::entertainment::MainPage::statusChanged);
        connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &fairwind::apps::entertainment::MainPage::bufferingProgress);
        connect(m_player, &QMediaPlayer::videoAvailableChanged, this, &fairwind::apps::entertainment::MainPage::videoAvailableChanged);
        connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &fairwind::apps::entertainment::MainPage::displayErrorMessage);
        connect(m_player, &QMediaPlayer::stateChanged, this, &fairwind::apps::entertainment::MainPage::stateChanged);
        connect(ui->playlistView, &QAbstractItemView::activated, this, &fairwind::apps::entertainment::MainPage::jump);
        connect(ui->slider, &QSlider::sliderMoved, this, &fairwind::apps::entertainment::MainPage::seek);

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


        connect(ui->openButton, &QPushButton::clicked, this, &fairwind::apps::entertainment::MainPage::open);

        PlayerControls *controls = new PlayerControls(widget);
        controls->setState(m_player->state());
        controls->setVolume(m_player->volume());
        controls->setMuted(controls->isMuted());

        connect(controls, &PlayerControls::play, m_player, &QMediaPlayer::play);
        connect(controls, &PlayerControls::pause, m_player, &QMediaPlayer::pause);
        connect(controls, &PlayerControls::stop, m_player, &QMediaPlayer::stop);
        connect(controls, &PlayerControls::next, m_playlist, &QMediaPlaylist::next);
        connect(controls, &PlayerControls::previous, this, &fairwind::apps::entertainment::MainPage::previousClicked);
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

        ui->displayLayout->addWidget(m_videoWidget, 2);
        ui->controlLayout->addWidget(controls);

        /*
        controlLayout->addWidget(m_fullScreenButton);
        controlLayout->addWidget(m_colorButton);
        */



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



        if (!isPlayerAvailable()) {
            getFairWindApp()->warning(
                    "Service not available",
                    "The QMediaPlayer object does not have a valid service.\n Please check the media service plugins are installed."
                    );

            controls->setEnabled(false);
            ui->playlistView->setEnabled(false);
            ui->openButton->setEnabled(false);
            /*
            m_colorButton->setEnabled(false);
            m_fullScreenButton->setEnabled(false);
             */
        }

        metaDataChanged();
    }

    MainPage::~MainPage() {
        delete ui;
    }

    bool MainPage::isPlayerAvailable() const {
        return m_player->isAvailable();
    }

    void MainPage::open() {
        QWidget *widget = (QWidget *)this;

        QFileDialog fileDialog(widget);
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

// Check for ".m3u" playlists.
    static bool isPlaylist(const QUrl &url) {
        if (!url.isLocalFile())
            return false;
        const QFileInfo fileInfo(url.toLocalFile());
        return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
    }

    void MainPage::addToPlaylist(const QList<QUrl> &urls) {
        for (auto &url: urls) {
            if (isPlaylist(url))
                m_playlist->load(url);
            else
                m_playlist->addMedia(url);
        }
    }

    void MainPage::setCustomAudioRole(const QString &role) {
        m_player->setCustomAudioRole(role);
    }

    void MainPage::durationChanged(qint64 duration) {
        m_duration = duration / 1000;
        ui->slider->setMaximum(m_duration);
    }

    void MainPage::positionChanged(qint64 progress) {
        if (!ui->slider->isSliderDown())
            ui->slider->setValue(progress / 1000);

        updateDurationInfo(progress / 1000);
    }

    void MainPage::metaDataChanged() {
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

    void MainPage::previousClicked() {
        // Go to previous track if we are within the first 5 seconds of playback
        // Otherwise, seek to the beginning.
        if (m_player->position() <= 5000)
            m_playlist->previous();
        else
            m_player->setPosition(0);
    }

    void MainPage::jump(const QModelIndex &index) {
        if (index.isValid()) {
            m_playlist->setCurrentIndex(index.row());
            m_player->play();
        }
    }

    void MainPage::playlistPositionChanged(int currentItem) {
        clearHistogram();
        ui->playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
    }

    void MainPage::seek(int seconds)
    {
        m_player->setPosition(seconds * 1000);
    }

    void MainPage::statusChanged(QMediaPlayer::MediaStatus status) {
        QWidget *widget = (QWidget *)this;

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
                QApplication::alert(widget);
                break;
            case QMediaPlayer::InvalidMedia:
                displayErrorMessage();
                break;
        }
    }

    void MainPage::stateChanged(QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState)
            clearHistogram();
    }

    void MainPage::handleCursor(QMediaPlayer::MediaStatus status) {
        QWidget *widget = (QWidget *)this;
#ifndef QT_NO_CURSOR
        if (status == QMediaPlayer::LoadingMedia ||
            status == QMediaPlayer::BufferingMedia ||
            status == QMediaPlayer::StalledMedia)
            widget->setCursor(QCursor(Qt::BusyCursor));
        else
            widget->unsetCursor();
#endif
    }

    void MainPage::bufferingProgress(int progress) {
        if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
            setStatusInfo(tr("Stalled %1%").arg(progress));
        else
            setStatusInfo(tr("Buffering %1%").arg(progress));
    }

    void MainPage::videoAvailableChanged(bool available) {
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

    void MainPage::setTrackInfo(const QString &info) {
        QWidget *widget = (QWidget *)this;
        m_trackInfo = info;

        if (m_statusBar) {
            m_statusBar->showMessage(m_trackInfo);
            m_statusLabel->setText(m_statusInfo);
        } else {
            if (!m_statusInfo.isEmpty())
                widget->setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
            else
                widget->setWindowTitle(m_trackInfo);
        }
    }

    void MainPage::setStatusInfo(const QString &info) {
        QWidget *widget = (QWidget *)this;
        m_statusInfo = info;

        if (m_statusBar) {
            m_statusBar->showMessage(m_trackInfo);
            m_statusLabel->setText(m_statusInfo);
        } else {
            if (!m_statusInfo.isEmpty())
                widget->setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
            else
                widget->setWindowTitle(m_trackInfo);
        }
    }

    void MainPage::displayErrorMessage() {
        setStatusInfo(m_player->errorString());
    }

    void MainPage::updateDurationInfo(qint64 currentInfo) {
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

        ui->labelDuration->setText(tStr);
    }

    void MainPage::showColorDialog() {
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

    void MainPage::clearHistogram() {
        /*
        QMetaObject::invokeMethod(m_videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
        QMetaObject::invokeMethod(m_audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
         */
    }
} // fairwind::apps::entertainment
