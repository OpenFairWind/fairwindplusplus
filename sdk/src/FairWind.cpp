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
#include <FairWindSdk/layers/OSMLayer.hpp>
#include <FairWindSdk/layers/TiledLayer.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>
#include <FairWindSdk/displays/DisplayDoubleText.hpp>
#include <FairWindSdk/displays/DisplayGauge.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include <FairWindSdk/connections/SignalKWSClient.hpp>
#include <FairWindSdk/connections/SignalKAPIClient.hpp>
#include <FairWindSdk/layouts/GridLayout.hpp>
#include <FairWindSdk/layouts/VHGLayout.hpp>
#include <FairWind.hpp>
#include <displays/DisplayWindAngleGauge.hpp>
#include <ILayout.hpp>


/*
 * FairWind
 * Private constructor - called by getInstance in order to ensure
 * the singleton design pattern
 */
fairwind::FairWind::FairWind() {
    qDebug() << "FairWind constructor";

    // Register built-in chart layers
    registerLayer( new layers::FairWindOSMLayer());
    registerLayer( new layers::FairWindTiledLayer());
    registerLayer(new layers::SignalKLayer());

    // Register built-in displays
    registerDisplay(new displays::DisplaySingleText());
    registerDisplay(new displays::DisplayDoubleText());
    registerDisplay(new displays::DisplayGauge());
    registerDisplay(new displays::DisplayWindAngleGauge());
    registerDisplay(new displays::DisplayChart());

    // Register built-in connections
    registerConnection(new connections::SignalKAPIClient());
    registerConnection(new connections::SignalKWSClient());

    // Register built-in display layouts
    registerLayout(new layouts::GridLayout());
    registerLayout(new layouts::VHGLayout());


}

/*
 * getAppByExtensionId
 * Return the pointer to a FairWind++ app given the id
 */
fairwind::apps::IApp *fairwind::FairWind::getAppByExtensionId(QString id) {
    // Return the app pointer
    return m_mapFairWindApps[id];
}

/*
 * setApplicationDirPath
 * Set the application directory path
 */
void fairwind::FairWind::setApplicationDirPath(QString applicationDirPath) {
    // Set the path
    m_applicationDirPath=std::move(applicationDirPath);
}

/*
 * loadApps
 * Load thea FairWind++ Apps as QT5 Plugin
 */
void fairwind::FairWind::loadApps() {

    // Initialize the QT managed settings
    QSettings settings("fairwind.ini", QSettings::NativeFormat);

    // Get the name of the FairWind++ apps directory
    QString appsDirRoot = settings.value("appsRoot","").toString();

    // Check if no value has been specified
    if (appsDirRoot.isEmpty()) {

        // Get the FairWind++ installation directory
        auto appsDir = QDir(QCoreApplication::applicationDirPath());

        // Navigate to the FairWind++ root
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
        // Create the apps directory
        appsDir.mkdir("apps");

        // Change dir to the apps directory
        appsDir.cd("apps");

        // Get the absolute apps path
        appsDirRoot=appsDir.absolutePath();
    }

    // Store the name in the settings
    settings.setValue("appsRoot",appsDirRoot);

    // Set the apps directory
    m_appsRoot = QDir(appsDirRoot);


    // Get the name of the FairWind++ apps directory
    QString dataDirRoot = settings.value("dataRoot","").toString();

    // Check if no value has been specified
    if (dataDirRoot.isEmpty()) {

        // Get the FairWind++ installation directory
        auto dataDir = QDir(QCoreApplication::applicationDirPath());

        // Navigate to the FairWind++ root
#if defined(Q_OS_WIN)
        if (dataDir.dirName().toLower() == "debug" || dataDir.dirName().toLower() == "release")
        dataDir.cdUp();
#elif defined(Q_OS_MAC)
        if (dataDir.dirName() == "MacOS") {
            dataDir.cdUp();
            dataDir.cdUp();
            dataDir.cdUp();
        }
#endif
        // Create the data directory
        dataDir.mkdir("data");

        // Change dir to the apps directory
        dataDir.cd("data");

        // Get the absolute data path
        dataDirRoot=dataDir.absolutePath();
    }

    // Store the name in the settings
    settings.setValue("dataRoot",dataDirRoot);

    // Set the data directory
    m_dataRoot = QDir(dataDirRoot);


    // Get a list of files from the apps directory
    const auto entryList = m_appsRoot.entryList(QDir::Files);

    // For each file name in the list...
    for (const QString &fileName : entryList) {

        // Get the absolute path of the file name
        QString absoluteAppPath=m_appsRoot.absoluteFilePath(fileName);

        // Load the FairWind++ App as a QT5 plugin
        QPluginLoader loader(absoluteAppPath);

        // Create a plugin instance
        QObject *plugin = loader.instance();

        // Check if the instance has been created
        if (plugin) {

            // Get the interface id from the plugin metadata
            auto iid=loader.metaData().value("IID").toString();

            // Check if the plugin is a FairWind++ app
            if (iid == IID_FAIRWIND_APPS) {

                // Handle the plugin as FairWind++
                fairwind::apps::IApp *fairWindApp= qobject_cast<fairwind::apps::IApp *>(plugin);

                // Check if it is possible handling the plugin as a FairWind++ app
                if (fairWindApp) {

                    // Get the plugin metadata
                    QJsonObject metaData = loader.metaData()["MetaData"].toObject();

                    // Get the FairWind++ app id
                    QString appId = "";

                    // Check if metadata contains the FairWInd key
                    if (metaData.contains("FairWind") && metaData["FairWind"].isObject()) {

                        // Get the FairWind object
                        QJsonObject objectFairWind = metaData["FairWind"].toObject();

                        // Check if FairWind object contains the App key
                        if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

                            // Get the App object
                            QJsonObject objectApp = objectFairWind["App"].toObject();

                            // Check if App object contains the Id key
                            if (objectApp.contains("Id") && objectApp["Id"].isString()) {

                                // Get the application id
                                appId = objectApp["Id"].toString();
                            }
                        }
                    }

                    // Check if the id is not empty and not already present
                    if (!appId.isEmpty() && !m_mapFairWindApps.contains(appId) ) {

                        // Set the apps root in the metadata object
                        metaData["appsRoot"]=m_appsRoot.absolutePath();

                        // Set the data root in the metadata object
                        metaData["dataRoot"]=m_dataRoot.absolutePath();

                        // Initialize the app with the plugin metadata
                        fairWindApp->onInit(&metaData);

                        // Store the FairWind++ app pointer in the m_mapFairWindApps dictionary
                        m_mapFairWindApps[fairWindApp->getId()]=fairWindApp;
                    }
                } else {
                    // Unload the plugin
                    loader.unload();
                }
            }
        }
    }
    qDebug() << "fairwind::FairWind::loadApps :" << m_mapFairWindApps.keys();
}

/*
 * loadConfig
 * Load the configuration from the fairwind.ini file where it is stored the name of the actual fairwind.json file
 */
void fairwind::FairWind::loadConfig() {

    // Initialize the QT managed settings
    QSettings settings("fairwind.ini", QSettings::NativeFormat);

    // Get the name of the FairWind++ configuration file
    QString configFile = settings.value("configFile", "fairwind.json").toString();

    // Store the name in the settings
    settings.setValue("configFile",configFile);

    // Create a QFile object to manage the configuration file
    QFile jsonFile(configFile);

    // Open the configuration file in read only mode
    jsonFile.open(QFile::ReadOnly);

    // Read all the text
    QString jsonText=jsonFile.readAll();

    // Create a QJsonDocument from the text file
    QJsonDocument jsonConfig = QJsonDocument::fromJson(jsonText.toUtf8());

    // Set the config object
    m_config=jsonConfig.object();

    // Check if the config object has a "SignalK" key
    if (m_config.contains("SignalK") && m_config["SignalK"].isObject()) {

        // Get the "SignalK" json object
        QJsonObject jsonSignalK=m_config["SignalK"].toObject();

        // Check if the "SignalK" json object has the "self" key
        if (jsonSignalK.contains("self") && jsonSignalK["self"].isString()) {

            // Get the value of the "self" key
            QString self = jsonSignalK["self"].toString();

            // Set the self key in the Signal K document
            m_signalkDocument.setSelf(self);
        }

        // Check if the "SignalK" json object has the "connections" key
        if (jsonSignalK.contains("connections") && jsonSignalK["connections"].isArray()) {

            // Get the connections array
            QJsonArray arrayConnections=jsonSignalK["connections"].toArray();

            // For each item of the array...
            for (auto item:arrayConnections) {

                // Check if the item is an object
                if (item.isObject()) {
                    // Get the json object of the connection
                    QJsonObject objectConnection=item.toObject();

                    // Check if the json object contains the key "class"
                    if (objectConnection.contains("class") && objectConnection["class"].isString()) {

                        // Get the class name as a string
                        QString className=objectConnection["class"].toString();

                        // Get an instance of the connection class
                        connections::IConnection *fairWindConnection= instanceConnection(className);

                        // Check if the instance is valid
                        if (fairWindConnection) {

                            // Define a dictionary for the parameters
                            QMap<QString, QVariant> params;

                            // For each key in the object connection dictionary
                            for (auto key:objectConnection.keys()) {

                                // Save the key/value in the dictionary
                                params[key] = objectConnection[key].toVariant();
                            }


                            // Invoke the onInit method passing the parameters
                            fairWindConnection->onInit(params);

                            m_listConnections.append(fairWindConnection);
                        }
                    }
                }
            }
        }
    }

    // Check if the config file has the key "Extensions"
    if (m_config.contains("Extensions") && m_config["Extensions"].isObject()) {

        // Get the extensions json object
        QJsonObject jsonExtensions=m_config["Extensions"].toObject();

        // Check if the extensions json object contains the key "Apps"
        if (jsonExtensions.contains("Apps") && jsonExtensions["Apps"].isArray()) {

            // Get the apps json array
            QJsonArray jsonApps=jsonExtensions["Apps"].toArray();

            // For each item in the json array...
            for (auto jsonApp:jsonApps) {

                // Get the json app object
                QJsonObject jsonAppObject=jsonApp.toObject();

                // Check if the json app object contains the key "Id"
                if (jsonAppObject.contains("Id") && jsonAppObject["Id"].isString()) {

                    // Get the app id as a string
                    QString appId=jsonAppObject["Id"].toString();

                    // Declare a pointer to an app and set it to the null pointer
                    App *app= nullptr;

                    // Get the pointer to the app by the extension id
                    auto fairWindApp = getAppByExtensionId(appId);

                    // Check if the pointer is valid
                    if (fairWindApp) {

                        // Declare a dictionary for the arguments
                        QMap<QString,QVariant> args;

                        // Check if the app object contains the "Args" key
                        if (jsonAppObject.contains("Args") && jsonAppObject["Args"].isObject()) {

                            // Get the app json object
                            QJsonObject jsonArgs = jsonAppObject["Args"].toObject();

                            // For each key in the json object
                            for (const auto& key: jsonArgs.keys()) {

                                // Save the key/value in the dictionary
                                args[key]=jsonArgs[key].toVariant();
                            }
                        }

                        // Create a new app item
                        app = new App(fairWindApp,args);
                    }

                    // Check if the app has a valid pointer
                    if (app!= nullptr) {

                        // Store the app pointer in a dictionary indexed with an hash
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

bool fairwind::FairWind::registerLayer(fairwind::layers::ILayer *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredLayers.contains(className) == false) {
        qDebug() << "fairwind::FairWind::registerLayer:" << className;
        m_registeredLayers[className] = dummy;

    }
    return result;
}

fairwind::layers::ILayer *fairwind::FairWind::instanceLayer(const QString& className) {
    if (m_registeredLayers.contains(className)) {
        qDebug() << "fairwind::FairWind::instanceLayer:" << className;
        return m_registeredLayers[className]->getNewInstance();
    }
    return nullptr;
}

QJsonObject &fairwind::FairWind::getConfig() {
    return m_config;
}

fairwind::displays::IDisplay *fairwind::FairWind::instanceDisplay(const QString &className) {
    if (m_registeredDisplays.contains(className)) {
        return m_registeredDisplays[className]->getNewInstance();
    }
    return nullptr;
}

bool fairwind::FairWind::registerDisplay(fairwind::displays::IDisplay *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredDisplays.contains(className) == false) {
        m_registeredDisplays[className] = dummy;

    }
    return result;
}

fairwind::connections::IConnection *fairwind::FairWind::instanceConnection(const QString &className) {
    if (m_registeredConnections.contains(className)) {
        return m_registeredConnections[className]->getNewInstance();
    }
    return nullptr;
}

bool fairwind::FairWind::registerConnection(fairwind::connections::IConnection *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredConnections.contains(className) == false) {
        //qDebug() << "fairwind::FairWind::registerConnection: " << className;
        m_registeredConnections[className] = dummy;

    }
    return result;
}

fairwind::layouts::ILayout *fairwind::FairWind::instanceLayout(const QString &className) {
    if (m_registeredLayouts.contains(className)) {
        return m_registeredLayouts[className]->getNewInstance();
    }
    return nullptr;
}

bool fairwind::FairWind::registerLayout(fairwind::layouts::ILayout *dummy) {
    bool result= false;
    QString className=dummy->getClassName();
    if (m_registeredLayouts.contains(className) == false) {
        //qDebug() << "fairwind::FairWind::registerConnection: " << className;
        m_registeredLayouts[className] = dummy;

    }
    return result;
}

QMap<QString, fairwind::connections::IConnection *> *fairwind::FairWind::getConnections() {
    return &m_registeredConnections;
}

QMap<QString, fairwind::layouts::ILayout *> *fairwind::FairWind::getLayouts() {
    return &m_registeredLayouts;
}

QMap<QString, fairwind::displays::IDisplay *> *fairwind::FairWind::getDisplays() {
    return &m_registeredDisplays;
}

QMap<QString, fairwind::layers::ILayer *> *fairwind::FairWind::getLayers() {
    return &m_registeredLayers;
}

QList<fairwind::connections::IConnection *> *fairwind::FairWind::getConnectionsList() {
    return &m_listConnections;
}


