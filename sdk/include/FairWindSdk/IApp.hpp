//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_IAPP_HPP
#define FAIRWIND_IAPP_HPP

#include <QtPlugin>
#include <QString>
#include <QImage>
#include <QMainWindow>

#define IID_FAIRWIND_APPS "it.uniparthenope.fairwind.apps"

namespace fairwind::apps {
    /*
     * IApp
     * Interface to build FairWind apps
     */
    class IApp {
    public:
        // ~IApp
        virtual ~IApp() = default;

        // Initialisation method
        virtual void onInit(QJsonObject *metaData) = 0;

        // Returns the app's id
        virtual QString getId() const = 0;

        // Returns the app's name
        virtual QString getName() const = 0;

        // Returns the app's description
        virtual QString getDesc() const = 0;

        // Returns the app's version
        virtual QString getVersion() const = 0;

        // Returns the app's vendor
        virtual QString getVendor() const = 0;

        // Returns the app's copyright
        virtual QString getCopyright() const = 0;

        // Returns the app's license
        virtual QString getLicense() const = 0;

        // Returns the app's icon
        virtual QImage getIcon() const = 0;

        // Method called when the app is first launched by the user
        virtual QWidget *onGui(QMainWindow *mainWindow, QMap <QString, QVariant> args) = 0;

        // Method called to update the value of a settings
        virtual void updateSettings(QString settingsID, QString newValue) = 0;

        // Method to set the config file
        virtual void setConfig(QJsonObject config) = 0;

        // Returns the app's configuration
        virtual QJsonObject getConfig() = 0;

        // Returns the app's metadata
        virtual QJsonObject getMetaData() = 0;
    };
}

Q_DECLARE_INTERFACE(fairwind::apps::IApp,
IID_FAIRWIND_APPS)

#endif //FAIRWIND_IAPP_HPP