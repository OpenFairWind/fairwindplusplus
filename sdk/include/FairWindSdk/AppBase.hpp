//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_APPBASE_HPP
#define FAIRWIND_APPBASE_HPP

#include <QJsonObject>
#include <QtJsonSchema/jsonschema.h>
#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL AppBase{
            public:
            ~AppBase() = default;

            virtual QString getId() const;
            virtual QString getName() const;
            virtual QString getDesc() const;
            virtual QString getVersion() const;
            virtual QString getVendor() const;
            virtual QString getCopyright() const;
            virtual QString getLicense() const;

            virtual void onInit(QJsonObject *metaData);

            virtual QJsonObject getConfig();
            virtual void setConfig(QJsonObject config);
            virtual QJsonObject getSettings();
            virtual void setSettings(QJsonObject config);
            virtual QJsonObject getMetaData();
            virtual void updateSettings(QString settingsID, QString newValue);

            private:
            QJsonObject m_metaData;
            //QJsonObject m_config;
            QJsonObject m_settings;
    };
}

#endif //FAIRWIND_APPBASE_HPP