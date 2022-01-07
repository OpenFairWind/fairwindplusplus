//
// Created by Raffaele Montella on 05/04/21.
//

#ifndef FAIRWIND_CHART_HPP
#define FAIRWIND_CHART_HPP


#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui_Chart.h"

namespace fairwind::apps::chart {
    class Chart : public QObject, AppBase, IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~Chart() = default;

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


    public slots:


    private:

    };
}


#endif //FAIRWIND_CHART_HPP
