//
// Created by Raffaele Montella on 08/04/21.
//

#include <QJsonArray>
#include <QDir>

#include <AppBase.hpp>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <util/ExtendedJsonSchema.hpp>

/*
 * getId
 * Returns the app's id
 */
QString fairwind::AppBase::getId() const {
    return m_metaData["FairWind"]["App"]["Id"].toString();
}


/*
 * getSettings
 * Returns the app's settings model
 */
QJsonObject fairwind::AppBase::getSettings() {
    return m_settings;
}

/*
void fairwind::AppBase::setSettings(QJsonObject settings) {
    m_settings = settings;
}
*/

/*
 * getConfig
 * Returns the app's configuration
 */
QJsonObject fairwind::AppBase::getConfig() {

    // Get the application data path
    QDir appDataPath = QDir(m_metaData["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile appConfigFile(appDataPath.absolutePath() + QDir::separator() + "config.json");

    appConfigFile.open(QFile::ReadOnly);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(appConfigFile.readAll());

    return jsonDocument.object();
}

void fairwind::AppBase::setConfig(QJsonObject config) {
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
QJsonObject fairwind::AppBase::getMetaData() {
    return m_metaData;
}

/*
 * getName
 * Returns the app's name
 */
QString fairwind::AppBase::getName() const {
    // Check if the metadata contains the key FairWind
    if (m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {
        // Get the FairWind object
        QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

        // Check if the FairWind object contains the key App
        if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

            // Get the App object
            QJsonObject objectApp = objectFairWind["App"].toObject();

            // Check if the App object contains the key Name
            if (objectApp.contains("Name") && objectApp["Name"].isString()) {

                // Return the name
                return objectApp["Name"].toString();
            }
        }
    }

    // Return the name from metadata (QT5 plugin name)
    return m_metaData["Name"].toString();
}

/*
 * getDesc
 * Returns the app's description
 */
QString fairwind::AppBase::getDesc() const {
    if (m_metaData.contains("Description") && m_metaData["Description"].isString()) {
        return m_metaData["Description"].toString();
    }

    return "";
}

/*
 * getVersion
 * Returns the app's version
 */
QString fairwind::AppBase::getVersion() const {
    if (m_metaData.contains("Version") && m_metaData["Version"].isString()) {
        return m_metaData["Version"].toString();
    }

    return "";
}

/*
 * getVendor
 * Returns the app's vendor
 */
QString fairwind::AppBase::getVendor() const {
    if (m_metaData.contains("Vendor") && m_metaData["Vendor"].isString()) {
        return m_metaData["Vendor"].toString();
    }

    return "";
}

/*
 * getCopyright
 * Returns the app's copyright
 */
QString fairwind::AppBase::getCopyright() const {
    if (m_metaData.contains("Copyright") && m_metaData["Copyright"].isString()) {
        return m_metaData["Copyright"].toString();
    }

    return "";
}

/*
 * getLicense
 * Returns the app's license
 */
QString fairwind::AppBase::getLicense() const {
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
void fairwind::AppBase::updateSettings(QString settingsID, QString newValue) {
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
void fairwind::AppBase::onCreate(QJsonObject *metaData) {
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
                        qDebug() << getName() << ": config fits the schema!\n";
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

void fairwind::AppBase::onResume() {}
void fairwind::AppBase::onPause() {}
void fairwind::AppBase::onStop() {}
void fairwind::AppBase::onDestroy() {}