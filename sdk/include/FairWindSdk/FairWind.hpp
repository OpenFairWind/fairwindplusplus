//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_FAIRWIND_HPP
#define FAIRWIND_FAIRWIND_HPP

#include <QString>
#include <map>
#include <QJsonDocument>
#include <QGeoView/QGVLayer.h>


#include "FairWindSDK.hpp"
#include "IApp.hpp"
#include "ILayer.hpp"
#include "SignalKDocument.hpp"
#include "App.hpp"
#include "IDisplay.hpp"
#include "IConnection.hpp"
#include "ILayout.hpp"

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL FairWind: public QObject {
        Q_OBJECT
    public:

        static FairWind *getInstance();

        void loadApps();
        apps::IApp *getAppByExtensionId(QString id);


        void setApplicationDirPath(QString qString);
        void loadConfig();

        SignalKDocument *getSignalKDocument();

        QMap<QString, App *> getApps();
        bool registerLayer(fairwind::layers::ILayer *dummy);
        layers::ILayer *instanceLayer(const QString& className);

        bool registerDisplay(fairwind::displays::IDisplay *dummy);
        displays::IDisplay *instanceDisplay(const QString& className);

        bool registerConnection(fairwind::connections::IConnection *dummy);
        connections::IConnection *instanceConnection(const QString& className);

        bool registerLayout(fairwind::layouts::ILayout *dummy);
        layouts::ILayout *instanceLayout(const QString& className);

        QJsonObject &getConfig();


    private:
        QJsonObject m_config;

        SignalKDocument m_signalkDocument;

        QMap<QString, fairwind::apps::IApp *> m_mapFairWindApps;

        QMap<QString, App *> m_mapApps;

        QString m_applicationDirPath;
        FairWind();
        inline static FairWind *m_instance = nullptr;

        QMap<QString, fairwind::layers::ILayer *> m_registeredLayers;
        QMap<QString, fairwind::displays::IDisplay *> m_registeredDisplays;
        QMap<QString, fairwind::connections::IConnection *> m_registeredConnections;
        QMap<QString, fairwind::layouts::ILayout *> m_registeredLayouts;
    };
}


#endif //FAIRWIND_FAIRWIND_HPP
