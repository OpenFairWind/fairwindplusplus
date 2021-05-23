//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_DASHBOARD_HPP
#define FAIRWIND_DASHBOARD_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindAppBase.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include "ui_Dashboard.h"
#include "ui_Dashboard_Settings.h"

namespace fairwind::apps::dashboard {
    class Dashboard : public QObject, FairWindAppBase, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Dashboard();

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;

        QJsonObject getConfig() override;

    private:
        Ui::Dashboard *ui;
        Ui::dashboard_Settings *uiSettings;
    };
}


#endif //FAIRWIND_DASHBOARD_HPP
