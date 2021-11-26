//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Weather.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::weather::Weather::getIcon() const {
    return QImage(":/resources/images/icons/weather_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::weather::Weather::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Weather();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::weather::Weather::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::weather::Weather::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::weather::Weather::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::weather::Weather::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::weather::Weather::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::weather::Weather::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::weather::Weather::getLicense() const {
    return fairwind::AppBase::getLicense();
}

void fairwind::apps::weather::Weather::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::weather::Weather::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::weather::Weather::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::weather::Weather::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::weather::Weather::updateSettings(QString settingsID, QString newValue) {
    QDir appDataPath = QDir(getMetaData()["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile configsFile(appDataPath.absolutePath() + QDir::separator() + "config.json");
    configsFile.open(QFile::ReadWrite);

    QJsonDocument configsDocument = QJsonDocument().fromJson(configsFile.readAll());

    QJsonObject configs = configsDocument.object();

    QJsonValueRef ref = configs.find("Values").value();
    QJsonObject values = ref.toObject();

    values.insert(settingsID, newValue);

    ref = values;

    configsDocument.setObject(configs);

    if (configsFile.resize(0))
        configsFile.write(configsDocument.toJson());

    configsFile.close();
    setConfig(configs);
}

void fairwind::apps::weather::Weather::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}