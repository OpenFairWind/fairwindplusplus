//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Video.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::video::Video::getIcon() const {
    return QImage(":/resources/images/icons/video_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::video::Video::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Video();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::video::Video::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::video::Video::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::video::Video::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::video::Video::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::video::Video::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::video::Video::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::video::Video::getLicense() const {
    return fairwind::AppBase::getLicense();
}

void fairwind::apps::video::Video::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::video::Video::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::video::Video::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::video::Video::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::video::Video::updateSettings(QString settingsID, QString newValue) {
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

void fairwind::apps::video::Video::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}