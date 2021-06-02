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
#include "IFairWindApp.hpp"
#include "IFairWindLayer.hpp"
#include "SignalKDocument.hpp"
#include "App.hpp"
#include "IFairWindDisplay.hpp"

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL FairWind: public QObject {
        Q_OBJECT
    public:

        static FairWind *getInstance();

        void loadApps();
        apps::IFairWindApp *getAppByExtensionId(QString id);


        void setApplicationDirPath(QString qString);
        void loadConfig();

        SignalKDocument *getSignalKDocument();

        QMap<QString, App *> getApps();
        bool registerLayer(fairwind::layers::IFairWindLayer *dummy);
        layers::IFairWindLayer *instanceLayer(const QString& className);

        bool registerDisplay(fairwind::displays::IFairWindDisplay *dummy);
        displays::IFairWindDisplay *instanceDisplay(const QString& className);

        QJsonObject &getConfig();


    private:
        QJsonObject m_config;

        SignalKDocument m_signalkDocument;

        QMap<QString, fairwind::apps::IFairWindApp *> m_mapFairWindApps;

        QMap<QString, App *> m_mapApps;

        QString m_applicationDirPath;
        FairWind();
        inline static FairWind *m_instance = nullptr;

        QMap<QString, fairwind::layers::IFairWindLayer *> m_registeredLayers;
        QMap<QString, fairwind::displays::IFairWindDisplay *> m_registeredDisplays;
    };
}


#endif //FAIRWIND_FAIRWIND_HPP
