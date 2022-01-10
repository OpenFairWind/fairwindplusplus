//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef UAV_HPP
#define UAV_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui_UAV.h"

namespace fairwind::apps::uav {
    class UAV : public QObject, ::fairwind::AppBase, ::fairwind::apps::IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~UAV() = default;

        // App lifecycle
        void onCreate(QJsonObject *metaData) override;
        QWidget *onStart(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;
        QString getVersion() const override;
        QString getVendor() const override;
        QString getCopyright() const override;
        QString getLicense() const override;

        QImage getIcon() const override;

        void updateSettings(QString settingsID, QString newValue) override;

        QJsonObject getConfig() override;
        void setConfig(QJsonObject config) override;
        QJsonObject getSettings() override;

        QJsonObject getMetaData() override;

    private:
        Ui::UAV *ui;
        QWidget *m_widget= nullptr;
    };
}

#endif //UAV_HPP
