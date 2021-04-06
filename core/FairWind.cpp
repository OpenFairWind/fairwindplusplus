//
// Created by Raffaele Montella on 03/04/21.
//

#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>
#include <QSettings>
#include <utility>
#include <QJsonArray>
#include "FairWind.hpp"

fairwind::FairWind &fairwind::FairWind::getInstance() {
    static fairwind::FairWind instance;
    return instance;
}

void fairwind::FairWind::loadExtensions() {
    auto appsDir = QDir(QCoreApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (appsDir.dirName().toLower() == "debug" || appsDir.dirName().toLower() == "release")
        appsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (appsDir.dirName() == "MacOS") {
        appsDir.cdUp();
        appsDir.cdUp();
        appsDir.cdUp();
    }
#endif
    appsDir.cd("extensions");

    const auto entryList = appsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        QString absoluteAppPath=appsDir.absoluteFilePath(fileName);
        QPluginLoader loader(absoluteAppPath);
        QObject *extension = loader.instance();
        if (extension) {
            auto iid=loader.metaData().value("IID").toString();

            if (iid == IID_FAIRWIND_APPS) {
                fairwind::extensions::apps::IFairWindApp *fairWindApp= qobject_cast<fairwind::extensions::apps::IFairWindApp *>(extension);
                if (fairWindApp) {
                    QJsonObject metaData = loader.metaData()["MetaData"].toObject();
                    qDebug() << metaData;
                    fairWindApp->setMetaData(metaData);
                    QString appId = fairWindApp->getId();
                    if (!appId.isEmpty()) {
                        m_mapFairWindApps.insert(appId, fairWindApp);
                        //m_mapFairWindApps[fairWindApp->getId()]=fairWindApp;
                        qDebug() << "app" << fairWindApp->getId();
                    }
                } else {
                    loader.unload();
                }
            } else if (iid == IID_FAIRWIND_PLUGINS) {
                fairwind::extensions::plugins::IFairWindPlugin *fairWindPlugin= qobject_cast<fairwind::extensions::plugins::IFairWindPlugin *>(extension);
                if (fairWindPlugin) {
                    QJsonObject metaData = loader.metaData()["MetaData"].toObject();
                    fairWindPlugin->setMetaData(metaData);
                    QString pluginId = fairWindPlugin->getId();
                    if (!pluginId.isEmpty()) {
                        m_mapFairWindPlugins.insert(fairWindPlugin->getId(), fairWindPlugin);
                        //m_mapFairWindPlugins[fairWindPlugin->getId()]=fairWindPlugin;
                        qDebug() << "plugin" << fairWindPlugin->getId();
                    }
                } else {
                    loader.unload();
                }
            }
        }
    }
    qDebug() << m_mapFairWindApps.keys() << " " << m_mapFairWindPlugins.keys();
}

fairwind::FairWind::FairWind() {
    qDebug() << "FairWind constructor";


}

fairwind::extensions::apps::IFairWindApp *fairwind::FairWind::getAppByExtensionId(QString id) {
    if (m_mapFairWindApps.find(id) == m_mapFairWindApps.end()) {
        return nullptr;
    }
    return m_mapFairWindApps[id];
}

fairwind::extensions::plugins::IFairWindPlugin *fairwind::FairWind::getPluginByExtensionId(QString id) {
    if (m_mapFairWindPlugins.find(id) == m_mapFairWindPlugins.end()) {
        return nullptr;
    }
    return m_mapFairWindPlugins[id];
}

void fairwind::FairWind::setApplicationDirPath(QString applicationDirPath) {
    m_applicationDirPath=std::move(applicationDirPath);
}

void fairwind::FairWind::loadConfig(QString configFile) {
    qDebug() << "Configuration: " << configFile;
    QFile jsonFile(configFile);
    jsonFile.open(QFile::ReadOnly);
    QString jsonText=jsonFile.readAll();

    QJsonDocument jsonConfig = QJsonDocument::fromJson(jsonText.toUtf8());
    QJsonObject jsonRoot=jsonConfig.object();
    if (jsonRoot.find("Extensions")!=jsonRoot.end()) {
        QJsonObject jsonExtensions=jsonRoot["Extensions"].toObject();
        if (jsonExtensions.find("Apps")!=jsonExtensions.end()) {
            QJsonArray jsonApps=jsonExtensions["Apps"].toArray();

            for (auto jsonApp:jsonApps) {
                App app(jsonApp.toObject());

                m_mapApps.insert(app.getHash(),&app);
            }

        }
    }
}

QMap<QString, fairwind::App *> fairwind::FairWind::getApps() {
    return m_mapApps;
}
