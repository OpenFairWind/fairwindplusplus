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

/*
fairwind::FairWind &fairwind::FairWind::getInstance() {
    static fairwind::FairWind instance;
    return instance;
}
 */

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
                    fairWindApp->init(&metaData);
                    QString appId = fairWindApp->getId();
                    if (!appId.isEmpty()) {
                        m_mapFairWindApps[fairWindApp->getId()]=fairWindApp;
                    }
                } else {
                    loader.unload();
                }
            } else if (iid == IID_FAIRWIND_PLUGINS) {
                fairwind::extensions::plugins::IFairWindPlugin *fairWindPlugin= qobject_cast<fairwind::extensions::plugins::IFairWindPlugin *>(extension);
                if (fairWindPlugin) {
                    QJsonObject metaData = loader.metaData()["MetaData"].toObject();
                    fairWindPlugin->init(metaData);
                    QString pluginId = fairWindPlugin->getId();
                    if (!pluginId.isEmpty()) {
                        m_mapFairWindPlugins[fairWindPlugin->getId()]=fairWindPlugin;
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
    return m_mapFairWindApps[id];
}

fairwind::extensions::plugins::IFairWindPlugin *fairwind::FairWind::getPluginByExtensionId(QString id) {
    return m_mapFairWindPlugins[id];
}

void fairwind::FairWind::setApplicationDirPath(QString applicationDirPath) {
    m_applicationDirPath=std::move(applicationDirPath);
}

void fairwind::FairWind::loadConfig(const QString& configFile) {
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

                QJsonObject jsonAppObject=jsonApp.toObject();

                if (jsonAppObject.find("Extension")!=jsonAppObject.end()) {

                    QString extension=jsonAppObject["Extension"].toString();
                    App *app= nullptr;

                    if (extension.startsWith(IID_FAIRWIND_APPS)) {

                        auto fairWindApp = getAppByExtensionId(extension);
                        if (fairWindApp) {
                            app=new App(fairWindApp);
                        }
                    } else if (extension.startsWith(IID_FAIRWIND_PLUGINS)) {
                        auto fairWindPlugin = getPluginByExtensionId(extension);
                        if (fairWindPlugin) {
                            QMap<QString,QString> args;

                            if (jsonAppObject.find("Args") != jsonAppObject.end()) {
                                QJsonObject jsonArgs = jsonAppObject["Args"].toObject();
                                for (QString key: jsonArgs.keys()) {
                                    args.insert(key, jsonArgs[key].toString());
                                }
                            }
                            app = new App(fairWindPlugin,args);
                        }
                    }

                    if (app!= nullptr) {
                        m_mapApps[app->getHash()]=app;
                    }
                }
            }
        }
    }
}

QMap<QString, fairwind::App *> fairwind::FairWind::getApps() {
    return m_mapApps;
}

fairwind::FairWind *fairwind::FairWind::getInstance() {
    if (m_instance== nullptr) {
        m_instance = new FairWind();
    }
    return m_instance;
}
