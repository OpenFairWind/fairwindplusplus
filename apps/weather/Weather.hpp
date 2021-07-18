//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui_Weather.h"
#include "ui_Weather_Settings.h"

namespace fairwind::apps::weather {
    class Weather : public QObject, ::fairwind::AppBase, ::fairwind::apps::IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~Weather() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override ;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;

        QJsonObject getConfig() override;
        QJsonObject getMetaData() override;

    private:
        Ui::Weather *ui;
        Ui::weather_Settings *uiSettings;
        QWidget *m_widget= nullptr;
    };
}

#endif //WEATHER_HPP
