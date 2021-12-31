//
// Created by Raffaele Montella on 01/04/21.
//

#include "External.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QProcess>


QImage fairwind::apps::native::External::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::apps::native::External::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {
    if (args.contains("Command")) {
        QString command=args["Command"].toString();
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::apps::native::External::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::native::External::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::native::External::getDesc() const {
    return fairwind::AppBase::getDesc();
}

QString fairwind::apps::native::External::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::native::External::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::native::External::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::native::External::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::native::External::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QJsonObject fairwind::apps::native::External::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::native::External::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::native::External::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::native::External::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}

void fairwind::apps::native::External::setSettings(QJsonObject config) {
    AppBase::setSettings(config);
}

QJsonObject fairwind::apps::native::External::getSettings() {
    return AppBase::getSettings();
}