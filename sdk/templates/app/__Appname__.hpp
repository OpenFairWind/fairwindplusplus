//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef __APPNAME___HPP
#define __APPNAME___HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui___Appname__.h"
#include "ui___Appname___Settings.h"

namespace __namespace__ {
    class __Appname__ : public QObject, ::fairwind::AppBase, ::fairwind::apps::IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~__Appname__() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;
        QString getVersion() const override;
        QString getVenor() const override;
        QString getCopyright() const override;
        QString getLicense() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;

        QJsonObject getConfig() override;
        QJsonObject getMetaData() override;

    private:
        Ui::__Appname__ *ui;
        Ui::__appname___Settings *uiSettings;
        QWidget *m_widget= nullptr;
    };
}

#endif //__APPNAME___HPP
