//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_FAIRWINDAPP_HPP
#define FAIRWIND_FAIRWINDAPP_HPP

#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>



namespace fairwind::apps {

    class PageBase;

    class FAIRWINDSDK_LIB_DECL FairWindApp: public QObject{
    Q_OBJECT

    public:
        ~FairWindApp();

        // Get the app icon
        virtual QImage getIcon() const;

        // Get the app id as reverse FQDN
        virtual QString getId() const;

        // Get the app human readable name
        virtual QString getName() const;

        // Get the app description
        virtual QString getDesc() const;

        // Get the app version
        virtual QString getVersion() const;

        // Get the app vendor
        virtual QString getVendor() const;

        // Get the app copyright info
        virtual QString getCopyright() const;

        // Get the app license
        virtual QString getLicense() const;

        // Called by the app loader when the app is loaded
        virtual void onCreate();

        // Method called when the app is first launched by the user (only one time in the lifecycle)
        virtual void onStart();

        // Called when the app is going to be in foreground
        virtual void onResume();

        // Called when the app is going to be in background
        virtual void onPause();

        // Called when the app is going to be stopped
        virtual void onStop();

        // Called when the app is going to be unloaded by the system
        virtual void onDestroy();

        // Called when config is set
        virtual void onConfigChanged();

        // Called when the app runs the first time ever
        virtual void onInstall() = 0;

        // Called when the app runs its last time
        virtual void onUninstall() = 0;

        // Get the config.json content
        virtual QJsonObject getConfig();

        // Set the config.json content
        virtual void setConfig(QJsonObject config);

        // Get the settings extended json schema fromthe metadata
        virtual ExtendedJsonSchema *getSettings();
        // virtual void setSettings(QJsonObject config);

        // Get the whole metadata object
        virtual QJsonObject getMetaData();

        virtual QString getDataPath();

        virtual QString getCategory();

        QWidget *getWidget();
        void add(PageBase *page, const QString& route = "/");
        void show(const QString& route = "/");
        void show(PageBase *page);
        void remove(const QString& route);
        void remove(PageBase *page);
        PageBase *get(const QString& route = "/");

        QString getRoute();
        QMap<QString, QVariant> getArgs();

        void warning(const QString& message, const QString& details);

        void colophon();

        // ToDo: make this method private and accessible only by the FairWind class.
        void init(QJsonObject *metaData);

        // ToDo: make this method private and accessible only by MainWindow class
        void setArgs(QMap<QString, QVariant> args);

        // ToDo: make this method private and accessible only by MainWindow class
        void setRoute(QString route);

    private:
        QWidget *m_widget;
        QMap<QString,PageBase *> m_mapWidget;

        // The metadata embedded with the app
        QJsonObject m_metaData;

        // The extended json schema for the settings system
        ExtendedJsonSchema *m_settings;

        // The route
        QString m_route;

        // The args passed by a route
        QMap<QString, QVariant> m_args;

    };
}

#endif //FAIRWIND_FAIRWINDAPP_HPP