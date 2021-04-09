//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>



QImage fairwind::apps::dashboard::Dashboard::getIcon() const {
    return QImage(":/resources/images/icons/dashboard_icon.png");
}

QWidget *fairwind::apps::dashboard::Dashboard::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    return nullptr;
}

QString fairwind::apps::dashboard::Dashboard::getId() const {
    return fairwind::FairWindAppBase::getId();
}

QString fairwind::apps::dashboard::Dashboard::getName() const {
    return fairwind::FairWindAppBase::getName();
}

QString fairwind::apps::dashboard::Dashboard::getDesc() const {
    return fairwind::FairWindAppBase::getDesc();
}

void fairwind::apps::dashboard::Dashboard::init(QJsonObject *metaData) {
    fairwind::FairWindAppBase::init(metaData);
}