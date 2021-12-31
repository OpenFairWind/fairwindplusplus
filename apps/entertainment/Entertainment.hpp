//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef FAIRWIND_ENTERTAINMENT_HPP
#define FAIRWIND_ENTERTAINMENT_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui_Entertainment.h"
#include "ui_Entertainment_Settings.h"
#include "PlaylistModel.hpp"
#include "HistogramWidget.hpp"

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QStatusBar;
class QVideoProbe;
class QVideoWidget;
class QAudioProbe;
QT_END_NAMESPACE

class PlaylistModel;
class HistogramWidget;

namespace fairwind::apps::entertainment {
    class Entertainment : public QObject, AppBase, IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~Entertainment() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;
        QString getVersion() const override;
        QString getVendor() const override;
        QString getCopyright() const override;
        QString getLicense() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        void updateSettings(QString settingsID, QString newValue) override;

        QJsonObject getConfig() override;
        void setConfig(QJsonObject config) override;
        QJsonObject getSettings() override;
        void setSettings(QJsonObject config) override;
        QJsonObject getMetaData() override;

        bool isPlayerAvailable() const;

        void addToPlaylist(const QList<QUrl> &urls);
        void setCustomAudioRole(const QString &role);

    signals:
        void fullScreenChanged(bool fullScreen);

    private slots:
        void open();
        void durationChanged(qint64 duration);
        void positionChanged(qint64 progress);
        void metaDataChanged();

        void previousClicked();

        void seek(int seconds);
        void jump(const QModelIndex &index);
        void playlistPositionChanged(int);

        void statusChanged(QMediaPlayer::MediaStatus status);
        void stateChanged(QMediaPlayer::State state);
        void bufferingProgress(int progress);
        void videoAvailableChanged(bool available);

        void displayErrorMessage();

        void showColorDialog();

    private:
        Ui::Entertainment *ui;
        Ui::entertainment_Settings *uiSettings;
        QWidget *m_widget= nullptr;

        void clearHistogram();
        void setTrackInfo(const QString &info);
        void setStatusInfo(const QString &info);
        void handleCursor(QMediaPlayer::MediaStatus status);
        void updateDurationInfo(qint64 currentInfo);

        QMediaPlayer *m_player = nullptr;
        QMediaPlaylist *m_playlist = nullptr;
        QVideoWidget *m_videoWidget = nullptr;
        QLabel *m_coverLabel = nullptr;
        QSlider *m_slider = nullptr;
        QLabel *m_labelDuration = nullptr;
        /*
        QPushButton *m_fullScreenButton = nullptr;
        QPushButton *m_colorButton = nullptr;
        QDialog *m_colorDialog = nullptr;
        */
        QLabel *m_statusLabel = nullptr;
        QStatusBar *m_statusBar = nullptr;

        /*
        QLabel *m_labelHistogram = nullptr;
        HistogramWidget *m_videoHistogram = nullptr;
        HistogramWidget *m_audioHistogram = nullptr;
        QVideoProbe *m_videoProbe = nullptr;
        QAudioProbe *m_audioProbe = nullptr;
        */

        PlaylistModel *m_playlistModel = nullptr;
        QAbstractItemView *m_playlistView = nullptr;
        QString m_trackInfo;
        QString m_statusInfo;
        qint64 m_duration;
    };
}

#endif //FAIRWIND_ENTERTAINMENT_HPP
