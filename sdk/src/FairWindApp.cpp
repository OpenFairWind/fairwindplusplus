//
// Created by Raffaele Montella on 08/04/21.
//

#include <QJsonArray>
#include <QDir>

#include <FairWindApp.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include <FairWindSdk/ui/Warning.hpp>
#include <QGridLayout>
#include <QStackedWidget>
#include <ui/Colophon.hpp>

/*
 * getId
 * Returns the app's id
 */
QString fairwind::apps::FairWindApp::getId() const {
    return m_metaData["FairWind"]["App"]["Id"].toString();
}


/*
 * getSettings
 * Returns the app's settings model
 */
QJsonObject fairwind::apps::FairWindApp::getSettings() {
    return m_settings;
}


/*
 * getConfig
 * Returns the app's configuration
 */
QJsonObject fairwind::apps::FairWindApp::getConfig() {

    // Get the application data path
    QDir appDataPath = QDir(m_metaData["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile appConfigFile(appDataPath.absolutePath() + QDir::separator() + "config.json");

    appConfigFile.open(QFile::ReadOnly);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(appConfigFile.readAll());

    QJsonObject result = jsonDocument.object();

    //qDebug() << "jsonObject: " << result;

    return result;
}

void fairwind::apps::FairWindApp::setConfig(QJsonObject config) {
    // Get the application data path
    QDir appDataPath = QDir(m_metaData["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile appConfigFile(appDataPath.absolutePath() + QDir::separator() + "config.json");

    // Open the config.json file in write mode
    appConfigFile.open(QFile::WriteOnly);

    // Create a json document
    QJsonDocument jsonDocument;

    // Initialize the json document with the config data
    jsonDocument.setObject(config);

    // Write the config file
    appConfigFile.write(jsonDocument.toJson());
}

/*
 * getMetaData
 * Returns the app's metadata
 */
QJsonObject fairwind::apps::FairWindApp::getMetaData() {
    return m_metaData;
}

/*
 * getName
 * Returns the app's name
 */
QString fairwind::apps::FairWindApp::getName() const {
    QString name = "";

    // Check if app's arguments contain a name
    if (m_args.contains("Name")) {
        // Set the app's name
        name = m_args["Name"].toString();
    }

    // Check if the metadata contains the key FairWind
    if (name.isEmpty() && m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {

        qDebug() << "m_metaData:" << m_metaData;

        // Get the FairWind object
        QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

        // Check if the FairWind object contains the key App
        if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

            // Get the App object
            QJsonObject objectApp = objectFairWind["App"].toObject();

            // Check if the App object contains the key Name
            if (objectApp.contains("Name") && objectApp["Name"].isString()) {

                // Return the name
                name=objectApp["Name"].toString();
            }
        }
    }

    // Return the name from metadata (QT5 plugin name)
    if (name.isEmpty()) {
        name = m_metaData["Name"].toString();
    }

    return name;
}

/*
 * getDesc
 * Returns the app's description
 */
QString fairwind::apps::FairWindApp::getDesc() const {
    QString desc="";
    // Check if app's arguments contain a description
    if (m_args.contains("Description")) {
        // Set the app's description
        desc = m_args["Description"].toString();
    }

    if (desc.isEmpty() && m_metaData.contains("Description") && m_metaData["Description"].isString()) {
        desc = m_metaData["Description"].toString();
    }

    return desc;
}

/*
 * getVersion
 * Returns the app's version
 */
QString fairwind::apps::FairWindApp::getVersion() const {
    if (m_metaData.contains("Version") && m_metaData["Version"].isString()) {
        return m_metaData["Version"].toString();
    }

    return "";
}

/*
 * getVendor
 * Returns the app's vendor
 */
QString fairwind::apps::FairWindApp::getVendor() const {
    if (m_metaData.contains("Vendor") && m_metaData["Vendor"].isString()) {
        return m_metaData["Vendor"].toString();
    }

    return "";
}

/*
 * getCopyright
 * Returns the app's copyright
 */
QString fairwind::apps::FairWindApp::getCopyright() const {
    if (m_metaData.contains("Copyright") && m_metaData["Copyright"].isString()) {
        return m_metaData["Copyright"].toString();
    }

    return "";
}

/*
 * getLicense
 * Returns the app's license
 */
QString fairwind::apps::FairWindApp::getLicense() const {
    if (m_metaData.contains("License") && m_metaData["License"].isString()) {
        return m_metaData["License"].toString();
    }

    return "";
}

/*
 * updateSettings
 * This method will update the app's settings inside its json config file
 * and will update the m_config variable accordingly
 */
void fairwind::apps::FairWindApp::updateSettings(QString settingsID, QString newValue) {
    // Get the path
    QDir appDataPath = QDir(getMetaData()["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile configsFile(appDataPath.absolutePath() + QDir::separator() + "config.json");
    configsFile.open(QFile::ReadWrite);

    // Get config
    QJsonObject configs = getConfig();

    // Find the 'Values' object inside the configs
    QJsonValueRef ref = configs.find(settingsID).value();
    QString values = ref.toString();

    // Update the settings value
    values = newValue;

    // Save the changes
    ref = values;

    auto configsDocument = new QJsonDocument;
    configsDocument->setObject(configs);

    // Wipe the config file and then fill it with the new content
    if (configsFile.resize(0))
        configsFile.write(configsDocument->toJson());

    // Close the file
    configsFile.close();
    // Set the config
    setConfig(configs);
}

/*
 * onInit
 * Initialisation method
 */
void fairwind::apps::FairWindApp::init(QJsonObject *metaData) {
    // Copy the metadata in a member object
    m_metaData = QJsonObject(*metaData);

    // Get the application data path
    QDir appDataPath = QDir(m_metaData["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile appConfigFile(appDataPath.absolutePath() + QDir::separator() + "config.json");

    // Check if metadata contains the FairWind key
    if (m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {
        // Get the fairwind object
        QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

        // Check if the fairwind object contains the App key
        if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {
            // Get the app object
            QJsonObject objectApp = objectFairWind["App"].toObject();

            // Check if the app object has the Settings key
            if (objectApp.contains("Settings") && objectApp["Settings"].isObject()) {
                // Set the config object
                m_settings = objectApp["Settings"].toObject();

                // Check if the app config file doesn't exist
                if (!appConfigFile.exists()) {
                    // Check if the app object has the Config key
                    if (objectApp.contains("Config") && objectApp["Config"].isObject()) {

                        // Set the config object
                        QJsonObject config = objectApp["Config"].toObject();

                        // Open the config.json file in write mode
                        appConfigFile.open(QFile::WriteOnly);

                        // Create a json document
                        QJsonDocument jsonDocument;

                        // Initialize the json document with the config data
                        jsonDocument.setObject(config);

                        // Write the config file
                        appConfigFile.write(jsonDocument.toJson());

                        // Close the config.json
                        appConfigFile.close();

                    } else {
                        // Create a config.json from Settings
                        ExtendedJsonSchema jsonExtendedSchema(m_settings);

                        // Create a json document
                        QJsonDocument jsonDocument = jsonExtendedSchema.getDefaultConfig();

                        // Open the config.json file in write mode
                        appConfigFile.open(QFile::WriteOnly);

                        // Write the config file
                        appConfigFile.write(jsonDocument.toJson());

                        // Close the config.json
                        appConfigFile.close();
                        
                    }
                }

                // Check if the app config file exists
                if (appConfigFile.exists()) {
                    // Open the config.json file in read mode
                    appConfigFile.open(QFile::ReadOnly);

                    // Read the configuration file
                    auto configDoc = QJsonDocument::fromJson(appConfigFile.readAll());

                    ExtendedJsonSchema jsonExtendedSchema(m_settings);


                    // Only for debug
                    QFile tmpFile(getId()+".schema.json");
                    tmpFile.open(QFile::WriteOnly);
                    tmpFile.write(jsonExtendedSchema.toDocument().toJson());


                    if (jsonExtendedSchema.validate(configDoc)) {
                        QString name = getName();
                        qDebug() << name << ": config fits the schema!\n";
                    }
                    appConfigFile.close();
                }
            }
        }
    }

    // Check if the data directory exists
    if (!appDataPath.exists("data")) {
        // Create the data directory
        appDataPath.mkdir("data");
    }

    // Check if the resources directory exists
    if (!appDataPath.exists("resources")) {
        // Create the resources directory
        appDataPath.mkpath("resources/images/icons");
    }
}

void fairwind::apps::FairWindApp::onCreate() {}

void fairwind::apps::FairWindApp::onStart() {

    m_widget = new QWidget();
    auto gridLayout = new QGridLayout();
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    auto stackedWidget = new QStackedWidget();
    stackedWidget->setObjectName("container");
    gridLayout->addWidget(stackedWidget,0,0);
    m_widget->setLayout(gridLayout);

}

void fairwind::apps::FairWindApp::onResume()  {}

void fairwind::apps::FairWindApp::onPause()  {}

void fairwind::apps::FairWindApp::onStop()  {}

void fairwind::apps::FairWindApp::onDestroy()  {}

QWidget *fairwind::apps::FairWindApp::getWidget() {
    return m_widget;
}

void fairwind::apps::FairWindApp::add(QWidget *page, const QString& route) {
    if (page) {
        auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");

        if (stackedWidget && !m_mapWidget.contains(route)) {
            stackedWidget->addWidget(page);
            m_mapWidget.insert(route, page);
        }
    }
}

void fairwind::apps::FairWindApp::show(QWidget *page) {
    auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");
    if (stackedWidget) {
        stackedWidget->setCurrentWidget(page);
    }
}

void fairwind::apps::FairWindApp::show(const QString& route) {
    if (m_mapWidget.contains(route)) {
        show(m_mapWidget[route]);
    }
}

fairwind::apps::FairWindApp::~FairWindApp() {
    //delete m_widget;
}

QImage fairwind::apps::FairWindApp::getIcon() const {
    QImage icon;

    // Check if app's arguments contain an icon
    if (m_args.contains("Icon")) {
        // Get the icon's path
        QString iconFilePath = m_args["Icon"].toString();
        QDir iconFile(iconFilePath);

        // Check if the directory containing the icon is relative
        if (iconFile.isRelative()) {
            // Build the full icon's path
            iconFilePath =
                    m_metaData["dataRoot"].toString() + QDir::separator() + getId() +
                    QDir::separator() + iconFilePath;

        }
        //qDebug() << "fairwind::App::App: iconFilePath: " << iconFilePath;
        // Set the app's icon
        icon = QImage(iconFilePath);
    }
    // Check if the metadata contains the key FairWind
    else if (m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {
        // Get the FairWind object
        QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

        // Check if the FairWind object contains the key App
        if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

            // Get the App object
            QJsonObject objectApp = objectFairWind["App"].toObject();

            // Check if the App object contains the key Name
            if (objectApp.contains("Icon") && objectApp["Icon"].isString()) {

                // Create the icon from the manifest
                icon = QImage(objectApp["Icon"].toString());
            }
        }
    }
    // Finally use the default icon
    else {
        icon = QImage(":/resources/images/icons/chandlery_icon.png");
    }

    return icon;
}

void fairwind::apps::FairWindApp::colophon() {
    auto colophonPage = new ui::Colophon(nullptr, this);
    add(colophonPage,"colophon");
    show("colophon");
}

void fairwind::apps::FairWindApp::warning(const QString& message, const QString& details) {
    auto warningPage = new ui::Warning(nullptr, this, message, details);
    add(warningPage,"warning");
    show("warning");
}

void fairwind::apps::FairWindApp::remove(const QString& route) {
    if (m_mapWidget.contains(route)) {
        remove(m_mapWidget[route]);
    }
}

void fairwind::apps::FairWindApp::remove(QWidget *page) {
    auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");
    if (stackedWidget) {
        QString route = "";
        for(auto key:m_mapWidget.keys()) {
            if (m_mapWidget[key]==page) {
                route = key;
                break;
            }
        }
        m_mapWidget.remove(route);
        stackedWidget->removeWidget(page);
    }
}

QMap<QString, QVariant> fairwind::apps::FairWindApp::getArgs() {
    return m_args;
}

void fairwind::apps::FairWindApp::setArgs(QMap<QString, QVariant> args) {
    m_args = args;
}

QString fairwind::apps::FairWindApp::getRoute() {
    return m_route;
}

void fairwind::apps::FairWindApp::setRoute(QString route) {
    m_route = route;
}


