//
// Created by Raffaele Montella on 01/04/21.
//

#include "Native.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QProcess>


QImage fairwind::apps::native::Native::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::apps::native::Native::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {
    if (args.contains("Command")) {
        QString command=args["Command"].toString();
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::apps::native::Native::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::native::Native::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::native::Native::getDesc() const {
    return fairwind::AppBase::getDesc();
}

QString fairwind::apps::native::Native::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::native::Native::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::native::Native::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::native::Native::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::native::Native::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::native::Native::onSettings(QTabWidget *tabWidgets) {
    return nullptr;
}

QJsonObject fairwind::apps::native::Native::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::native::Native::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::native::Native::updateSettings(QString settingsID, QString newValue) {
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

void fairwind::apps::native::Native::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}