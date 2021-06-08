//
// Created by Raffaele Montella on 03/04/21.
//

#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>
#include <QSettings>
#include <utility>
#include <QJsonArray>
#include <FairWindSdk/layers/SignalKLayer.hpp>
#include <FairWindSdk/layers/FairWindOSMLayer.hpp>
#include <FairWindSdk/layers/FairWindTiledLayer.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>
#include <FairWindSdk/displays/DisplayDoubleText.hpp>
#include <FairWindSdk/displays/DisplayGauge.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include <FairWindSdk/connections/SignalKWSClient.hpp>
#include <FairWindSdk/connections/SignalKAPIClient.hpp>
#include <FairWind.hpp>


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
    registerLayer( new layers::FairWindOSMLayer());
    registerLayer( new layers::FairWindTiledLayer());
    registerLayer(new layers::SignalKLayer());

    registerDisplay(new displays::DisplaySingleText());
    registerDisplay(new displays::DisplayDoubleText());
    registerDisplay(new displays::DisplayGauge());
    registerDisplay(new displays::DisplayChart());

    registerConnection(new connections::SignalKAPIClient());
    registerConnection(new connections::SignalKWSClient());
}

fairwind::apps::IFairWindApp *fairwind::FairWind::getAppByExtensionId(QString id) {
    return m_mapFairWindApps[id];
}

void fairwind::FairWind::setApplicationDirPath(QString applicationDirPath) {
    m_applicationDirPath=std::move(applicationDirPath);
}

void fairwind::FairWind::loadConfig() {
    QSettings settings("fairwind.ini", QSettings::NativeFormat);
    QString configFile = settings.value("configFile", "fairwind.json").toString();
    settings.setValue("configFile",configFile);

    QFile jsonFile(configFile);
    jsonFile.open(QFile::ReadOnly);
    QString jsonText=jsonFile.readAll();

    QJsonDocument jsonConfig = QJsonDocument::fromJson(jsonText.toUtf8());
    m_config=jsonConfig.object();
    if (m_config.contains("SignalK") && m_config["SignalK"].isObject()) {
        QJsonObject jsonSignalK=m_config["SignalK"].toObject();
        if (jsonSignalK.contains("self") && jsonSignalK["self"].isString()) {
            QString self = jsonSignalK["self"].toString();
            m_signalkDocument.setSelf(self);
        }
        if (jsonSignalK.contains("connections") && jsonSignalK["connections"].isArray()) {
            QJsonArray arrayConnections=jsonSignalK["connections"].toArray();
            for (auto item:arrayConnections) {
                if (item.isObject()) {
                    QJsonObject objectConnection=item.toObject();
                    if (objectConnection.contains("class") && objectConnection["class"].isString()) {
                        QString className=objectConnection["class"].toString();
                        connections::IFairWindConnection *fairWindConnection= instanceConnection(className);
                        if (fairWindConnection) {
                            QMap<QString, QVariant> params;
                            for(auto key:objectConnection.keys()) {
                                params[key]=objectConnection[key].toVariant();
                            }
                            fairWindConnection->onInit(params);
                        }
                    }
                }
            }
        }
    }
    if (m_config.contains("Extensions") && m_config["Extensions"].isObject()) {

        QJsonObject jsonExtensions=m_config["Extensions"].toObject();

        if (jsonExtensions.contains("Apps") && jsonExtensions["Apps"].isArray()) {

            QJsonArray jsonApps=jsonExtensions["Apps"].toArray();

            for (auto jsonApp:jsonApps) {

                QJsonObject jsonAppObject=jsonApp.toObject();

                if (jsonAppObject.find("Id")!=jsonAppObject.end()) {

                    QString appId=jsonAppObject["Id"].toString();
                    App *app= nullptr;

                    if (appId.startsWith(IID_FAIRWIND_APPS)) {

                        auto fairWindApp = getAppByExtensionId(appId);
                        if (fairWindApp) {
                            QMap<QString,QVariant> args;

                            if (jsonAppObject.contains("Args") && jsonAppObject["Args"].isObject()) {

                                QJsonObject jsonArgs = jsonAppObject["Args"].toObject();

                                for (const auto& key: jsonArgs.keys()) {
                                    args.insert(key, jsonArgs[key].toVariant());
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

bool fairwind::FairWind::registerLayer(fairwind::layers::IFairWindLayer *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredLayers.contains(className) == false) {
        qDebug() << "fairwind::FairWind::registerLayer:" << className;
        m_registeredLayers[className] = dummy;

    }
    return result;
}

fairwind::layers::IFairWindLayer *fairwind::FairWind::instanceLayer(const QString& className) {
    if (m_registeredLayers.contains(className)) {
        qDebug() << "fairwind::FairWind::instanceLayer:" << className;
        return m_registeredLayers[className]->getNewInstance();
    }
    return nullptr;
}

QJsonObject &fairwind::FairWind::getConfig() {
    return m_config;
}

fairwind::displays::IFairWindDisplay *fairwind::FairWind::instanceDisplay(const QString &className) {
    if (m_registeredDisplays.contains(className)) {
        return m_registeredDisplays[className]->getNewInstance();
    }
    return nullptr;
}

bool fairwind::FairWind::registerDisplay(fairwind::displays::IFairWindDisplay *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredDisplays.contains(className) == false) {
        m_registeredDisplays[className] = dummy;

    }
    return result;
}

fairwind::connections::IFairWindConnection *fairwind::FairWind::instanceConnection(const QString &className) {
    if (m_registeredConnections.contains(className)) {
        return m_registeredConnections[className]->getNewInstance();
    }
    return nullptr;
}

bool fairwind::FairWind::registerConnection(fairwind::connections::IFairWindConnection *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredConnections.contains(className) == false) {
        //qDebug() << "airwind::FairWind::registerConnection: " << className;
        m_registeredConnections[className] = dummy;

    }
    return result;
}



