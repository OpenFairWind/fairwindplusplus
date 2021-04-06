//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_FAIRWIND_HPP
#define FAIRWIND_FAIRWIND_HPP

#include <QString>
#include <map>
#include <QJsonDocument>
#include "../include/IFairWindApp.hpp"
#include "../include/IFairWindPlugin.hpp"
#include "App.hpp"

namespace fairwind {
    class FairWind {
    public:
        static FairWind &getInstance();

        void loadExtensions();
        extensions::apps::IFairWindApp *getAppByExtensionId(QString id);
        extensions::plugins::IFairWindPlugin *getPluginByExtensionId(QString id);

        void setApplicationDirPath(QString qString);
        void loadConfig(QString configFile);

        QMap<QString, App *> getApps();

    private:
        QMap<QString, fairwind::extensions::apps::IFairWindApp *> m_mapFairWindApps;
        QMap<QString, fairwind::extensions::plugins::IFairWindPlugin *> m_mapFairWindPlugins;


        QMap<QString, App *> m_mapApps;

        QString m_applicationDirPath;
        FairWind();


    };
}


#endif //FAIRWIND_FAIRWIND_HPP
