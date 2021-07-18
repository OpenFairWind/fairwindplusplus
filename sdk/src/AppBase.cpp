//
// Created by Raffaele Montella on 08/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QJsonArray>
#include <FairWindSdk/AppBase.hpp>
#include <QDir>
#include <AppBase.hpp>

QString fairwind::AppBase::getId() const {
    // Return the application id
    return m_metaData["FairWind"]["App"]["Id"].toString();
}

QJsonObject fairwind::AppBase::getConfig() {
    return m_config;
}

QJsonObject fairwind::AppBase::getMetaData() {
    return m_metaData;
}

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

QString fairwind::AppBase::getDesc() const {
    if (m_metaData.contains("Description") && m_metaData["Description"].isString()) {
        return m_metaData["Description"].toString();
    }
    return "";
}

QString fairwind::AppBase::getVersion() const {
    if (m_metaData.contains("Version") && m_metaData["Version"].isString()) {
        return m_metaData["Version"].toString();
    }
    return "";
}

QString fairwind::AppBase::getVendor() const {
    if (m_metaData.contains("Vendor") && m_metaData["Vendor"].isString()) {
        return m_metaData["Vendor"].toString();
    }
    return "";
}

QString fairwind::AppBase::getCopyright() const {
    if (m_metaData.contains("Copyright") && m_metaData["Copyright"].isString()) {
        return m_metaData["Copyright"].toString();
    }
    return "";
}

QString fairwind::AppBase::getLicense() const {
    if (m_metaData.contains("License") && m_metaData["License"].isString()) {
        return m_metaData["License"].toString();
    }
    return "";
}


void fairwind::AppBase::onInit(QJsonObject *metaData) {

    // Copy the metadata in a member object
    m_metaData = QJsonObject(*metaData);

    // Get the application data path
    QDir appDataPath=QDir(m_metaData["dataRoot"].toString()+QDir::separator()+getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile appConfigFile(appDataPath.absolutePath()+QDir::separator()+"config.json");

    // Check if the file exists
    if (appConfigFile.exists()) {

        // Open the file in read only mode
        appConfigFile.open(QFile::ReadOnly);

        // Read the file
        QString jsonString = appConfigFile.readAll();

        // Initialize a json document
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

        // Set the config object
        m_config = jsonDocument.object();
    } else {

        // Check if metadata contains the FairWind key
        if (m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {

            // Get the fairwind object
            QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

            // Check if the fairwind object contains the App key
            if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

                // Get the app object
                QJsonObject objectApp = objectFairWind["App"].toObject();

                // Check if the app object has the Config key
                if (objectApp.contains("Config") && objectApp["Config"].isObject()) {

                    // Set the config object
                    m_config = objectApp["Config"].toObject();

                    // Open the config.json file in write mode
                    appConfigFile.open(QFile::WriteOnly);

                    // Create a json document
                    QJsonDocument jsonDocument;

                    // Initialize the json document with the config data
                    jsonDocument.setObject(m_config);

                    // Qrite the config file
                    appConfigFile.write(jsonDocument.toJson());
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
