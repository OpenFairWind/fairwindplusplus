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

namespace fairwind::apps {
/*
 * getId
 * Returns the app's id
 */
    QString FairWindApp::getId() const {
        return m_metaData["FairWind"]["App"]["Id"].toString();
    }


/*
 * getSettings
 * Returns the app's settings model
 */
    fairwind::ExtendedJsonSchema *FairWindApp::getSettings() {
        return m_settings;
    }


/*
 * getConfig
 * Returns the app's configuration
 */
    QJsonObject FairWindApp::getConfig() {

        // Get the application data path
        QDir appDataPath = QDir(m_metaData["dataRoot"].toString());

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

    void FairWindApp::setConfig(QJsonObject config) {
        // Get the application data path
        QDir appDataPath = QDir(m_metaData["dataRoot"].toString());

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

        // Notify the application the config changed
        onConfigChanged();
    }

/*
 * getMetaData
 * Returns the app's metadata
 */
    QJsonObject FairWindApp::getMetaData() {
        return m_metaData;
    }

/*
 * getName
 * Returns the app's name
 */
    QString FairWindApp::getName() const {
        QString name = "";

        // Check if app's arguments contain a name
        if (m_args.contains("Name")) {
            // Set the app's name
            name = m_args["Name"].toString();
        }

        // Check if the metadata contains the key FairWind
        if (name.isEmpty() && m_metaData.contains("FairWind") && m_metaData["FairWind"].isObject()) {

            // qDebug() << "m_metaData:" << m_metaData;

            // Get the FairWind object
            QJsonObject objectFairWind = m_metaData["FairWind"].toObject();

            // Check if the FairWind object contains the key App
            if (objectFairWind.contains("App") && objectFairWind["App"].isObject()) {

                // Get the App object
                QJsonObject objectApp = objectFairWind["App"].toObject();

                // Check if the App object contains the key Name
                if (objectApp.contains("Name") && objectApp["Name"].isString()) {

                    // Return the name
                    name = objectApp["Name"].toString();
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
    QString FairWindApp::getDesc() const {
        QString desc = "";
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
    QString FairWindApp::getVersion() const {
        if (m_metaData.contains("Version") && m_metaData["Version"].isString()) {
            return m_metaData["Version"].toString();
        }

        return "";
    }

/*
 * getVendor
 * Returns the app's vendor
 */
    QString FairWindApp::getVendor() const {
        if (m_metaData.contains("Vendor") && m_metaData["Vendor"].isString()) {
            return m_metaData["Vendor"].toString();
        }

        return "";
    }

/*
 * getCopyright
 * Returns the app's copyright
 */
    QString FairWindApp::getCopyright() const {
        if (m_metaData.contains("Copyright") && m_metaData["Copyright"].isString()) {
            return m_metaData["Copyright"].toString();
        }

        return "";
    }

/*
 * getLicense
 * Returns the app's license
 */
    QString FairWindApp::getLicense() const {
        if (m_metaData.contains("License") && m_metaData["License"].isString()) {
            return m_metaData["License"].toString();
        }

        return "";
    }

/*
 * onInit
 * Initialisation method
 */
    void FairWindApp::init(QJsonObject *metaData) {
        // Copy the metadata in a member object
        m_metaData = QJsonObject(*metaData);

        // Get the application data path
        QDir appDataPath = QDir(m_metaData["dataRoot"].toString());

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
                    m_settings = new ExtendedJsonSchema(objectApp["Settings"].toObject());

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

                            // Create a json document
                            QJsonDocument jsonDocument = m_settings->getDefaultConfig();

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


                        // Only for debug
                        QFile tmpFile(getId() + ".schema.json");
                        tmpFile.open(QFile::WriteOnly);
                        tmpFile.write(m_settings->toDocument().toJson());


                        if (m_settings->validate(configDoc)) {
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

    void FairWindApp::onCreate() {}

    void FairWindApp::onStart() {

        m_widget = new QWidget();
        auto gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setSpacing(0);

        auto stackedWidget = new QStackedWidget();
        stackedWidget->setObjectName("container");
        gridLayout->addWidget(stackedWidget, 0, 0);
        m_widget->setLayout(gridLayout);

    }

    void FairWindApp::onResume() {
        for (auto item: m_mapWidget) {
            item->onResume();
        }
    }

    void FairWindApp::onPause() {
        for (auto item: m_mapWidget) {
            item->onPause();
        }
    }

    void FairWindApp::onStop() {
        for (auto item: m_mapWidget) {
            item->onStop();
        }
    }

    void FairWindApp::onDestroy() {
        for (auto item: m_mapWidget) {
            item->onDestroy();
        }
    }

    void FairWindApp::onConfigChanged() {
        for (auto item: m_mapWidget) {
            item->onConfigChanged();
        }
    }

    QWidget *FairWindApp::getWidget() {
        return m_widget;
    }

    void FairWindApp::add(PageBase *page, const QString &route) {
        if (page) {
            auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");

            if (stackedWidget && !m_mapWidget.contains(route)) {
                page->onAdding();
                stackedWidget->addWidget(page);
                m_mapWidget.insert(route, page);
                page->setFairWindApp(this);
                page->onAdded();
            }
        }
    }

    void FairWindApp::show(PageBase *page) {
        auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");
        if (stackedWidget) {
            page->onShowing();
            stackedWidget->setCurrentWidget(page);
            page->onShown();
        }
    }

    void FairWindApp::show(const QString &route) {
        if (m_mapWidget.contains(route)) {
            show(m_mapWidget[route]);
        }
    }

    PageBase *FairWindApp::get(const QString &route) {
        if (m_mapWidget.contains(route)) {
            return m_mapWidget[route];
        }
        return nullptr;
    }

    FairWindApp::~FairWindApp() {
        //delete m_widget;
    }

    QImage FairWindApp::getIcon() const {
        QImage icon;

        // Check if app's arguments contain an icon
        if (m_args.contains("Icon")) {

            // Get the icon's path
            QString iconFilePath = m_args["Icon"].toString();

            // Set the icon file
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

    void FairWindApp::colophon() {
        auto colophonPage = new ui::Colophon(nullptr);
        add(colophonPage, "colophon");
        show("colophon");
    }

    void FairWindApp::warning(const QString &message, const QString &details) {
        auto warningPage = new ui::Warning(nullptr, message, details);
        add(warningPage, "warning");
        show("warning");
    }

    void FairWindApp::remove(const QString &route) {
        if (m_mapWidget.contains(route)) {
            remove(m_mapWidget[route]);
        }
    }

    void FairWindApp::remove(PageBase *page) {
        auto stackedWidget = m_widget->findChild<QStackedWidget *>("container");
        if (stackedWidget) {
            QString route = "";
            for (auto key: m_mapWidget.keys()) {
                if (m_mapWidget[key] == page) {
                    route = key;
                    break;
                }
            }
            page->onRemoving();
            m_mapWidget.remove(route);
            stackedWidget->removeWidget(page);
            page->onRemoved();
        }
    }

    QMap<QString, QVariant> FairWindApp::getArgs() {
        return m_args;
    }

    void FairWindApp::setArgs(QMap<QString, QVariant> args) {
        m_args = args;
    }

    QString FairWindApp::getRoute() {
        return m_route;
    }

    void FairWindApp::setRoute(QString route) {
        m_route = route;
    }

    QString FairWindApp::getDataPath() {
        return m_metaData["dataRoot"].toString() + QDir::separator() + "data";
    }

    QString FairWindApp::getCategory() {
        return m_metaData["Category"].toString();
    }
}

