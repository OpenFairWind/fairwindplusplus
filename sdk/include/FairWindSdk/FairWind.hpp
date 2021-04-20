//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_FAIRWIND_HPP
#define FAIRWIND_FAIRWIND_HPP

#include <QString>
#include <map>
#include <QJsonDocument>



#include "FairWindSDK.hpp"
#include "IFairWindApp.hpp"
#include "SignalKDocument.hpp"
#include "App.hpp"

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL FairWind: public QObject {
        Q_OBJECT
    public:

        static FairWind *getInstance();

        void loadApps();
        apps::IFairWindApp *getAppByExtensionId(QString id);


        void setApplicationDirPath(QString qString);
        void loadConfig(const QString& configFile);

        SignalKDocument *getSignalKDocument();

        QMap<QString, App *> getApps();

    private:
        SignalKDocument m_signalkDocument;

        QMap<QString, fairwind::apps::IFairWindApp *> m_mapFairWindApps;

        QMap<QString, App *> m_mapApps;

        QString m_applicationDirPath;
        FairWind();
        inline static FairWind *m_instance = nullptr;

    };
}


#endif //FAIRWIND_FAIRWIND_HPP
