//
// Created by Raffaele Montella on 16/07/21.
//

#include "PlayerControls.hpp"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>

#include "ui_PlayerControls.h"

namespace fairwind::apps::entertainment {
    PlayerControls::PlayerControls(QWidget *parent):
        QWidget(parent), ui(new Ui::PlayerControls) {

        ui->setupUi(this);

        ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        ui->stopButton->setEnabled(false);
        ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
        ui->prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
        ui->muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

        ui->volumeSlider->setRange(0, 100);

        ui->rateBox->addItem("0.5x", QVariant(0.5));
        ui->rateBox->addItem("1.0x", QVariant(1.0));
        ui->rateBox->addItem("2.0x", QVariant(2.0));
        ui->rateBox->setCurrentIndex(1);

        connect(ui->playButton, &QAbstractButton::clicked, this, &PlayerControls::playClicked);
        connect(ui->stopButton, &QAbstractButton::clicked, this, &PlayerControls::stop);
        connect(ui->nextButton, &QAbstractButton::clicked, this, &PlayerControls::next);
        connect(ui->prevButton, &QAbstractButton::clicked, this, &PlayerControls::previous);
        connect(ui->muteButton, &QAbstractButton::clicked, this, &PlayerControls::muteClicked);
        connect(ui->volumeSlider, &QSlider::valueChanged, this, &PlayerControls::onVolumeSliderValueChanged);
        connect(ui->rateBox, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);
    }

    QMediaPlayer::State PlayerControls::state() const {
        return m_playerState;
    }

    void fairwind::apps::entertainment::PlayerControls::setState(QMediaPlayer::State state) {
        if (state != m_playerState) {
            m_playerState = state;

            switch (state) {
                case QMediaPlayer::StoppedState:
                    ui->stopButton->setEnabled(false);
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                    break;
                case QMediaPlayer::PlayingState:
                    ui->stopButton->setEnabled(true);
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                    break;
                case QMediaPlayer::PausedState:
                    ui->stopButton->setEnabled(true);
                    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                    break;
            }
        }
    }

    int fairwind::apps::entertainment::PlayerControls::volume() const {
        qreal linearVolume = QAudio::convertVolume(ui->volumeSlider->value() / qreal(100),
                                                   QAudio::LogarithmicVolumeScale,
                                                   QAudio::LinearVolumeScale);

        return qRound(linearVolume * 100);
    }

    void fairwind::apps::entertainment::PlayerControls::setVolume(int volume) {
        qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100),
                                                        QAudio::LinearVolumeScale,
                                                        QAudio::LogarithmicVolumeScale);

        ui->volumeSlider->setValue(qRound(logarithmicVolume * 100));
    }

    bool fairwind::apps::entertainment::PlayerControls::isMuted() const {
        return m_playerMuted;
    }

    void fairwind::apps::entertainment::PlayerControls::setMuted(bool muted) {
        if (muted != m_playerMuted) {
            m_playerMuted = muted;

            ui->muteButton->setIcon(style()->standardIcon(muted
                                                        ? QStyle::SP_MediaVolumeMuted
                                                        : QStyle::SP_MediaVolume));
        }
    }

    void fairwind::apps::entertainment::PlayerControls::playClicked() {
        switch (m_playerState) {
            case QMediaPlayer::StoppedState:
            case QMediaPlayer::PausedState:
                emit play();
                break;
            case QMediaPlayer::PlayingState:
                emit pause();
                break;
        }
    }

    void fairwind::apps::entertainment::PlayerControls::muteClicked() {
        emit changeMuting(!m_playerMuted);
    }

    qreal fairwind::apps::entertainment::PlayerControls::playbackRate() const {
        return ui->rateBox->itemData(ui->rateBox->currentIndex()).toDouble();
    }

    void fairwind::apps::entertainment::PlayerControls::setPlaybackRate(float rate) {
        for (int i = 0; i < ui->rateBox->count(); ++i) {
            if (qFuzzyCompare(rate, float(ui->rateBox->itemData(i).toDouble()))) {
                ui->rateBox->setCurrentIndex(i);
                return;
            }
        }

        ui->rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
        ui->rateBox->setCurrentIndex(ui->rateBox->count() - 1);
    }

    void fairwind::apps::entertainment::PlayerControls::updateRate() {
        emit changeRate(playbackRate());
    }

    void fairwind::apps::entertainment::PlayerControls::onVolumeSliderValueChanged() {
        emit changeVolume(volume());
    }
}