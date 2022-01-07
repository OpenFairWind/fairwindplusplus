//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_APPBASE_HPP
#define FAIRWIND_APPBASE_HPP

#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL AppBase{
    public:
        ~AppBase() = default;

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
        virtual void onCreate(QJsonObject *metaData);

        // Called when the app is going to be in foreground
        virtual void onResume();

        // Called when the app is going to be in background
        virtual void onPause();

        // Called when the app is going to be stopped
        virtual void onStop();

        // Called when the app is going to be unloaded by the system
        virtual void onDestroy();

        // Get the config.json content
        virtual QJsonObject getConfig();

        // Set the config.json content
        virtual void setConfig(QJsonObject config);

        // Get the settings extended json schema fromthe metadata
        virtual QJsonObject getSettings();
        // virtual void setSettings(QJsonObject config);

        // Get the whole metadata object
        virtual QJsonObject getMetaData();


        virtual void updateSettings(QString settingsID, QString newValue);

    private:
        // The metatadata embedded with the app
        QJsonObject m_metaData;

        // The extended json schema for the settings system
        QJsonObject m_settings;
    };
}

#endif //FAIRWIND_APPBASE_HPP