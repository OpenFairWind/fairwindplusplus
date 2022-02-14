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
#include <FairWindSdk/layers/GeoJsonLayer.hpp>
#include <FairWindSdk/layers/ESRILayer.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>
#include <FairWindSdk/displays/DisplayDoubleText.hpp>
#include <FairWindSdk/displays/DisplayGauge.hpp>
#include <FairWindSdk/displays/DisplayBarGauge.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include <FairWindSdk/displays/DisplaySimpleSwitch.hpp>
#include <FairWindSdk/displays/DisplayToggleSwitch.hpp>
#include <FairWindSdk/connections/SignalKWSClient.hpp>
#include <FairWindSdk/connections/SignalKAPIClient.hpp>
#include <FairWindSdk/layouts/GridLayout.hpp>
#include <FairWindSdk/layouts/VHGLayout.hpp>
#include <FairWind.hpp>
#include <displays/DisplayWindAngleGauge.hpp>
#include <ILayout.hpp>
#include <ISettingsTab.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include "settings/FairComboBox.hpp"
#include "settings/FairLineEdit.hpp"
#include "settings/FairCheckBox.hpp"
#include "settings/DisplaysBrowser.hpp"
#include "settings/LayersBrowser.hpp"

/*
 * FairWind
 * Private constructor - called by getInstance in order to ensure
 * the singleton design pattern
 */
fairwind::FairWind::FairWind() {
    qDebug() << "FairWind constructor";

    // Register the settings widgets inside the FairWind singleton
    registerSettings(new ui::settings::FairComboBox());
    registerSettings(new ui::settings::FairLineEdit());
    registerSettings(new ui::settings::FairCheckBox());
    registerSettings(new ui::settings::DisplaysBrowser());
    registerSettings(new ui::settings::LayersBrowser());

    // Register built-in chart layers
    registerLayer(new layers::OSMLayer());
    registerLayer(new layers::TiledLayer());
    registerLayer(new layers::SignalKLayer());
    registerLayer(new layers::GeoJsonLayer());
    registerLayer(new layers::ESRILayer());

    // Register built-in displays
    registerDisplay(new displays::DisplaySingleText());
    registerDisplay(new displays::DisplayDoubleText());
    registerDisplay(new displays::DisplayGauge());
    registerDisplay(new displays::DisplayBarGauge());
    registerDisplay(new displays::DisplayWindAngleGauge());
    registerDisplay(new displays::DisplayChart());
    registerDisplay(new displays::DisplaySimpleSwitch());
    registerDisplay(new displays::DisplayToggleSwitch());

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
fairwind::apps::IFairWindApp *fairwind::FairWind::getAppByExtensionId(const QString& id) {
    // Return the app pointer
    if (m_mapAppId2FairWindApp.contains(id)) {
        return m_mapAppId2FairWindApp[id];
    } else {
        return nullptr;
    }
}

/*
 * setApplicationDirPath
 * Set the application directory path
 */
void fairwind::FairWind::setApplicationDirPath(QString applicationDirPath) {
    // Set the path
    m_applicationDirPath = std::move(applicationDirPath);
}

/*
 * loadApps
 * Load the FairWind++ Apps as Qt5 Plugin
 */
void fairwind::FairWind::loadApps() {
    // Initialize the QT managed settings
    QSettings settings("fairwind.ini", QSettings::NativeFormat);

    // Get the name of the FairWind++ configuration file
    mSettingsFairWindAppId = settings.value("settingsFairWindAppId", "fairwind.apps.settings").toString();

    // Store the configuration in the settings
    settings.setValue("settingsFairWindAppId", mSettingsFairWindAppId);

    // Get the name of the FairWind++ configuration file
    mLauncherFairWindAppId = settings.value("launcherFairWindAppId", "fairwind.apps.launcherax10m").toString();

    // Store the configuration in the settings
    settings.setValue("launcherFairWindAppId", mLauncherFairWindAppId);

    // Is a virtual keyboard needed?
    bool useVirtualKeyboard = settings.value("useVirtualKeyboard", false).toBool();

    // Store the virtual keyboard in the settings
    settings.setValue("useVirtualKeyboard", useVirtualKeyboard);

    // Get the name of the FairWind++ apps directory
    QString appsDirRoot = settings.value("appsRoot", "").toString();

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
        appsDirRoot = appsDir.absolutePath();
    }

    // Store the name in the settings
    settings.setValue("appsRoot", appsDirRoot);

    // Set the apps directory
    m_appsRoot = QDir(appsDirRoot);


    // Get the name of the FairWind++ apps directory
    QString dataDirRoot = settings.value("dataRoot", "").toString();

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
        dataDirRoot = dataDir.absolutePath();
    }

    // Store the name in the settings
    settings.setValue("dataRoot", dataDirRoot);

    // Set the data directory
    m_dataRoot = QDir(dataDirRoot);


    // Get a list of files from the apps directory
    const auto entryList = m_appsRoot.entryList(QDir::Files);

    // For each file name in the list...
    for (const QString &fileName: entryList) {
        // Get the absolute path of the file name
        QString absoluteAppPath = m_appsRoot.absoluteFilePath(fileName);

        // Load the FairWind++ App as a QT5 plugin
        QPluginLoader loader(absoluteAppPath);

        // Create a plugin instance
        QObject *plugin = loader.instance();



        // Check if the instance has been created
        if (plugin) {
            // Get the interface id from the plugin metadata
            auto iid = loader.metaData().value("IID").toString();

            // Check if the plugin is a FairWind++ app
            if (iid == IID_FAIRWIND_APPS) {

                // Handle the plugin as FairWind++
                fairwind::apps::IFairWindApp *fairWindApp = qobject_cast<fairwind::apps::IFairWindApp *>(plugin);

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
                    if (!appId.isEmpty() && !m_mapAppId2FairWindApp.contains(appId)) {

                        // Set the apps root in the metadata object
                        metaData["appsRoot"] = m_appsRoot.absolutePath();

                        // Set the data root in the metadata object
                        metaData["dataRoot"] = m_dataRoot.absolutePath() + QDir::separator() + appId;

                        // Initialize the app with the plugin metadata
                        fairWindApp->init(&metaData);

                        // Store the FairWind++ app pointer in the m_mapAppId2FairWindApp dictionary
                        m_mapAppId2FairWindApp[fairWindApp->getId()] = fairWindApp;

                        qDebug() << "m_mapAppId2FairWindApp[" << fairWindApp->getId() << "]=" << fairWindApp->getName();

                        if (metaData.contains("Category") && metaData["Category"].isString()) {
                            QString category = metaData["Category"].toString();

                            if (category != "Apps") {
                                // Create a new app item
                                auto appItem = new AppItem(fairWindApp);

                                // Store the app pointer in a dictionary indexed with a hash
                                m_mapHash2AppItem[appItem->getHash()] = appItem;

                                // Store the app id -> hash
                                m_mapAppId2Hash[appId] = appItem->getHash();
                            }
                        }

                        // Starts the app lifecycle
                        fairWindApp->onCreate();
                    }
                } else {
                    // Unload the plugin
                    loader.unload();
                }
            }
        }
    }

    qDebug() << "fairwind::FairWind::loadApps :" << m_mapAppId2FairWindApp.keys();
}

/*
 * loadConfig
 * Load the configuration from the fairwind.ini file where it is stored the name of the actual fairwind.json file
 */
void fairwind::FairWind::loadConfig() {

    // Get the actual configuration
    QJsonObject configSettings = getConfig();

    // Check if the config object has a "SignalK" key
    if (configSettings.contains("SignalK") && configSettings["SignalK"].isObject()) {
        // Get the "SignalK" json object
        QJsonObject jsonSignalK = configSettings["SignalK"].toObject();

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
            QJsonArray arrayConnections = jsonSignalK["connections"].toArray();

            // For each item of the array...
            for (auto item: arrayConnections) {
                // Check if the item is an object
                if (item.isObject()) {
                    // Get the json object of the connection
                    QJsonObject objectConnection = item.toObject();

                    // Check if the json object contains the key "class"
                    if (objectConnection.contains("class") && objectConnection["class"].isString()) {
                        // Get the class name as a string
                        QString className = objectConnection["class"].toString();

                        // Get an instance of the connection class
                        connections::IConnection *fairWindConnection = instanceConnection(className);

                        // Check if the instance is valid
                        if (fairWindConnection) {
                            // Define a dictionary for the parameters
                            QMap <QString, QVariant> params;

                            // For each key in the object connection dictionary
                            for (const auto& key: objectConnection.keys()) {

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

    auto launcherFairWindApp = getAppByExtensionId(getLauncherFairWindAppId());
    if (launcherFairWindApp) {
        auto jsonExtensions = launcherFairWindApp->getConfig();


        // Check if the extensions json object contains the key "Apps"
        if (jsonExtensions.contains("Apps") && jsonExtensions["Apps"].isArray()) {

            // Get the apps json array
            QJsonArray jsonApps = jsonExtensions["Apps"].toArray();

            // For each item in the json array...
            for (auto jsonApp: jsonApps) {

                // Get the json app object
                QJsonObject jsonAppObject = jsonApp.toObject();

                // Check if the json app object contains the key "Id"
                if (jsonAppObject.contains("Id") && jsonAppObject["Id"].isString()) {

                    // Get the app id as a string
                    QString appId = jsonAppObject["Id"].toString();

                    // Check if the app as a route
                    int firstSlashPosition=appId.indexOf("/");

                    // Set the default route
                    QString route="";

                    if (firstSlashPosition>-1) {
                        route = appId.right(appId.length()-(firstSlashPosition+1));
                        appId = appId.left(firstSlashPosition);
                        qDebug() << "appId:" << appId << " route:" << route << "\n";
                    }

                    // Declare a pointer to an app and set it to the null pointer
                    AppItem *appItem = nullptr;

                    // Get the pointer to the app by the extension id
                    auto fairWindApp = getAppByExtensionId(appId);

                    // Check if the pointer is valid
                    if (fairWindApp) {

                        // Declare a dictionary for the arguments
                        QMap <QString, QVariant> args;

                        // Check if the app object contains the "Args" key
                        if (jsonAppObject.contains("Args") && jsonAppObject["Args"].isObject()) {

                            // Get the app json object
                            QJsonObject jsonArgs = jsonAppObject["Args"].toObject();

                            // For each key in the json object
                            for (const auto &key: jsonArgs.keys()) {

                                // Save the key/value in the dictionary
                                args[key] = jsonArgs[key].toVariant();
                            }
                        } else if (!route.isEmpty()) {
                            // Get the app config
                            QJsonObject jsonConfigObject=((fairwind::apps::FairWindApp *)fairWindApp)->getConfig();

                            // Check if the app config contains the "Routes" key
                            if (jsonConfigObject.contains("Routes") && jsonConfigObject["Routes"].isArray()) {
                                auto jsonRoutesArray = jsonConfigObject["Routes"].toArray();
                                for (auto jsonRoute: jsonRoutesArray) {
                                    auto jsonRouteObject = jsonRoute.toObject();
                                    if (jsonRouteObject.contains("Id") && jsonRouteObject["Id"].isString()) {
                                        auto routeId = jsonRouteObject["Id"].toString();
                                        if (route == routeId) {
                                            // Check if the app object contains the "Args" key
                                            if (jsonRouteObject.contains("Args") && jsonRouteObject["Args"].isObject()) {

                                                // Get the app json object
                                                QJsonObject jsonArgs = jsonRouteObject["Args"].toObject();

                                                // For each key in the json object
                                                for (const auto &key: jsonArgs.keys()) {

                                                    // Save the key/value in the dictionary
                                                    args[key] = jsonArgs[key].toVariant();
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        // Set the route
                        fairWindApp->setRoute(route);

                        // Set the args
                        fairWindApp->setArgs(args);

                        bool active = false;
                        int order = 1;

                        // Check if the json app object contains the key "Active"
                        if (jsonAppObject.contains("Active") && jsonAppObject["Active"].isBool()) {

                            // Get the app active attribute as a boolean
                            active = jsonAppObject["Active"].toBool();
                        }

                        // Check if the json app object contains the key "Order"
                        if (jsonAppObject.contains("Order") && jsonAppObject["Order"].isDouble()) {

                            // Get the app active attribute as a boolean
                            order = jsonAppObject["Order"].toInt();
                        }


                        // Create a new app item
                        appItem = new AppItem(fairWindApp, active, order);
                    }

                    // Check if the app has a valid pointer
                    if (appItem != nullptr) {

                        // Store the app pointer in a dictionary indexed with an hash
                        m_mapHash2AppItem[appItem->getHash()] = appItem;

                        // Store the app id -> hash
                        m_mapAppId2Hash[appId] = appItem->getHash();
                    }
                }
            }
        }
    }
}

/*
 * getInstance
 * Either returns the available instance or creates a new one
 */
fairwind::FairWind *fairwind::FairWind::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new FairWind();
    }
    return m_instance;
}

/*
 * getSignalKDocument
 * Returns the SignalK document
 */
SignalKDocument *fairwind::FairWind::getSignalKDocument() {
    return &m_signalkDocument;
}

/*
 * registerLayer
 * Registers a layer inside FairWind
 */
bool fairwind::FairWind::registerLayer(fairwind::layers::ILayer *dummy) {
    bool result = false;
    QString className = dummy->getClassName();
    if (!m_registeredLayers.contains(className)) {
        qDebug() << "fairwind::FairWind::registerLayer:" << className;
        m_registeredLayers[className] = dummy;

    }
    return result;
}

/*
 * instanceLayer
 * Returns one the registered layers that matches the provided classname, if any exists
 */
fairwind::layers::ILayer *fairwind::FairWind::instanceLayer(const QString &className) {
    if (m_registeredLayers.contains(className)) {
        qDebug() << "fairwind::FairWind::instanceLayer:" << className;
        return m_registeredLayers[className]->getNewInstance();
    }
    return nullptr;
}

/*
 * getConfig
 * Returns the configuration infos
 */
QJsonObject fairwind::FairWind::getConfig() {

    // Define the object
    QJsonObject config;

    // Get the Settings FairWindApp
    auto settingsFairWindApp = getAppByExtensionId(mSettingsFairWindAppId);

    // Check if the app is avaiable
    if (settingsFairWindApp) {

        // Get the configuration object
        config = settingsFairWindApp->getConfig();
    }

    // Return the config object
    return config;
}

/*
 * instanceDisplay
 * Returns one the registered displays that matches the provided classname, if any exists
 */
fairwind::displays::IDisplay *fairwind::FairWind::instanceDisplay(const QString &className) {
    if (m_registeredDisplays.contains(className)) {
        return m_registeredDisplays[className]->getNewInstance();
    }
    return nullptr;
}

/*
 * registerDisplay
 * Registers a new display inside FairWind
 */
bool fairwind::FairWind::registerDisplay(fairwind::displays::IDisplay *dummy) {
    bool result = false;
    QString className = dummy->getClassName();
    if (!m_registeredDisplays.contains(className)) {
        m_registeredDisplays[className] = dummy;

    }
    return result;
}

/*
 * instanceConnection
 * Returns one the registered connections that matches the provided classname, if any exists
 */
fairwind::connections::IConnection *fairwind::FairWind::instanceConnection(const QString &className) {
    if (m_registeredConnections.contains(className)) {
        return m_registeredConnections[className]->getNewInstance();
    }
    return nullptr;
}

/*
 * registerConnection
 * Registers a new connection inside FairWind
 */
bool fairwind::FairWind::registerConnection(fairwind::connections::IConnection *dummy) {
    bool result = false;
    QString className = dummy->getClassName();
    if (!m_registeredConnections.contains(className)) {
        //qDebug() << "fairwind::FairWind::registerConnection: " << className;
        m_registeredConnections[className] = dummy;

    }
    return result;
}

/*
 * instanceLayout
 * Returns one the registered layouts that matches the provided classname, if any exists
 */
fairwind::layouts::ILayout *fairwind::FairWind::instanceLayout(const QString &className) {
    if (m_registeredLayouts.contains(className)) {
        return m_registeredLayouts[className]->getNewInstance();
    }
    return nullptr;
}

/*
 * instanceSettings
 * Returns one the registered settings that matches the provided classname, if any exists
 */
fairwind::ui::settings::ISettingsTab *fairwind::FairWind::instanceSettingsTab(const QString &className) {
    if (m_registeredSettingsTab.contains(className)) {
        return m_registeredSettingsTab[className]->getNewInstance();
    }
    return nullptr;
}

fairwind::ui::settings::ISettings *fairwind::FairWind::instanceSettings(const QString& className) {
    if (m_registeredSettings.contains(className)) {
        return m_registeredSettings[className]->getNewInstance();
    }
    return nullptr;
}

/*
 * registerLayout
 * Registers a new layout inside FairWind
 */
bool fairwind::FairWind::registerLayout(fairwind::layouts::ILayout *dummy) {
    bool result = false;
    QString className = dummy->getClassName();
    if (m_registeredLayouts.contains(className) == false) {
        m_registeredLayouts[className] = dummy;
        result = true;
    }
    return result;
}

/*
 * registerSetting
 * Registers a new setting inside FairWind
 */
bool fairwind::FairWind::registerSettingsTab(fairwind::ui::settings::ISettingsTab *dummy) {
    bool result = false;
    QString className = dummy->getClassName();
    if (!m_registeredSettingsTab.contains(className)) {
        qDebug() << "fairwind::FairWind::registerSettingsTab: " << className;
        m_registeredSettingsTab[className] = dummy;
        m_listSettings.append(dummy);
        result = true;
    }
    return result;
}

bool fairwind::FairWind::registerSettings(fairwind::ui::settings::ISettings *dummy) {
    qDebug() << "1";
    bool result = false;
    QString className = dummy->getClassName();
    qDebug() << "2";
    if (!m_registeredSettings.contains(className)) {
        qDebug() << "fairwind::FairWind::registerSettings: " << className;
        m_registeredSettings[className] = dummy;
        result = true;
    }
    return result;
}

/*
 * getConnections
 * Returns all the registered connections
 */
QMap<QString, fairwind::connections::IConnection *> *fairwind::FairWind::getConnections() {
    return &m_registeredConnections;
}

/*
 * getLayouts
 * Returns alla the registered layouts
 */
QMap<QString, fairwind::layouts::ILayout *> *fairwind::FairWind::getLayouts() {
    return &m_registeredLayouts;
}

/*
 * getDisplays
 * Returns all the registered displays
 */
QMap<QString, fairwind::displays::IDisplay *> *fairwind::FairWind::getDisplays() {
    return &m_registeredDisplays;
}

/*
 * getLayers
 * Returns all th registered layers
 */
QMap<QString, fairwind::layers::ILayer *> *fairwind::FairWind::getLayers() {
    return &m_registeredLayers;
}

/*
 * getSettings
 * Returns all the registered settings
 */
QMap<QString, fairwind::ui::settings::ISettingsTab *> *fairwind::FairWind::getSettings() {
    return &m_registeredSettingsTab;
}

/*
 * getConnectionsList
 * Returns all the registered connections in form of list
 */
QList<fairwind::connections::IConnection *> *fairwind::FairWind::getConnectionsList() {
    return &m_listConnections;
}

/*
 * getSettingsList
 * Returns all the registered settings in form of list
 */
QList<fairwind::ui::settings::ISettingsTab *> *fairwind::FairWind::getSettingsList() {
    return &m_listSettings;
}

void fairwind::FairWind::setMainWindow(QMainWindow *mainWindow) {
    m_mainWindow = mainWindow;
}

QMainWindow * fairwind::FairWind::getMainWindow() {
    return m_mainWindow;
}

QString fairwind::FairWind::getSettingsFairWindAppId() {
    return mSettingsFairWindAppId;
}

QString fairwind::FairWind::getLauncherFairWindAppId() {
    return mLauncherFairWindAppId;
}

fairwind::AppItem *fairwind::FairWind::getAppItemByHash(QString hash) {
    return m_mapHash2AppItem[hash];
}

QString fairwind::FairWind::getAppHashById(QString appId) {
    return m_mapAppId2Hash[appId];
}

QList<QString> fairwind::FairWind::getExtensionsIds() {
    return m_mapAppId2FairWindApp.keys();
}

QList<QString> fairwind::FairWind::getExtensionsHashes() {
    return m_mapHash2AppItem.keys();
}


