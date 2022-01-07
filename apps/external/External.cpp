//
// Created by Raffaele Montella on 01/04/21.
//

#include "External.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QProcess>


QImage fairwind::apps::external::External::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::apps::external::External::onStart(QMainWindow *mainWindow, QMap<QString, QVariant> args) {
    if (args.contains("Command")) {
        QString command=args["Command"].toString();
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::apps::external::External::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::external::External::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::external::External::getDesc() const {
    return fairwind::AppBase::getDesc();
}

QString fairwind::apps::external::External::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::external::External::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::external::External::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::external::External::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::external::External::onCreate(QJsonObject *metaData) {
    AppBase::onCreate(metaData);
}

void fairwind::apps::external::External::onResume() {
    AppBase::onResume();
}

void fairwind::apps::external::External::onPause() {
    AppBase::onPause();
}

void fairwind::apps::external::External::onStop() {
    AppBase::onStop();
}

void fairwind::apps::external::External::onDestroy() {
    AppBase::onDestroy();
}

QJsonObject fairwind::apps::external::External::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::external::External::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::external::External::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::external::External::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}



QJsonObject fairwind::apps::external::External::getSettings() {
    return AppBase::getSettings();
}