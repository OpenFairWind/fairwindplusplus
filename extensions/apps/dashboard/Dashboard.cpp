//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>



QImage fairwind::extensions::apps::dashboard::Dashboard::getIcon() const {
    return QImage(":/resources/images/icons/dashboard_icon.png");
}

QWidget *fairwind::extensions::apps::dashboard::Dashboard::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    return nullptr;
}

QString fairwind::extensions::apps::dashboard::Dashboard::getId() const {
    return fairwind::extensions::FairWindExtension::getId();
}

QString fairwind::extensions::apps::dashboard::Dashboard::getName() const {
    return fairwind::extensions::FairWindExtension::getName();
}

QString fairwind::extensions::apps::dashboard::Dashboard::getDesc() const {
    return fairwind::extensions::FairWindExtension::getDesc();
}

void fairwind::extensions::apps::dashboard::Dashboard::init(QJsonObject *metaData) {
    FairWindExtension::init(metaData);
}