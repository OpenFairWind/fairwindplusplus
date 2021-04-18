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

void fairwind::FairWind::loadApps() {
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
    appsDir.cd("apps");

    const auto entryList = appsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        QString absoluteAppPath=appsDir.absoluteFilePath(fileName);
        QPluginLoader loader(absoluteAppPath);
        QObject *plugin = loader.instance();
        if (plugin) {
            auto iid=loader.metaData().value("IID").toString();

            if (iid == IID_FAIRWIND_APPS) {
                fairwind::apps::IFairWindApp *fairWindApp= qobject_cast<fairwind::apps::IFairWindApp *>(plugin);
                if (fairWindApp) {
                    QJsonObject metaData = loader.metaData()["MetaData"].toObject();
                    fairWindApp->onInit(&metaData);
                    QString appId = fairWindApp->getId();
                    if (!appId.isEmpty()) {
                        m_mapFairWindApps[fairWindApp->getId()]=fairWindApp;
                    }
                } else {
                    loader.unload();
                }
            }
        }
    }
    qDebug() << m_mapFairWindApps.keys();
}

fairwind::FairWind::FairWind() {
    qDebug() << "FairWind constructor";
}

fairwind::apps::IFairWindApp *fairwind::FairWind::getAppByExtensionId(QString id) {
    return m_mapFairWindApps[id];
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

                if (jsonAppObject.find("Id")!=jsonAppObject.end()) {

                    QString appId=jsonAppObject["Id"].toString();
                    App *app= nullptr;

                    if (appId.startsWith(IID_FAIRWIND_APPS)) {

                        auto fairWindApp = getAppByExtensionId(appId);
                        if (fairWindApp) {
                            QMap<QString,QString> args;

                            if (jsonAppObject.find("Args") != jsonAppObject.end()) {
                                QJsonObject jsonArgs = jsonAppObject["Args"].toObject();
                                for (QString key: jsonArgs.keys()) {
                                    args.insert(key, jsonArgs[key].toString());
                                }
                            }
                            app = new App(fairWindApp,args);
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

SignalKDocument *fairwind::FairWind::getSignalKDocument() {
    return &m_signalkDocument;
}
