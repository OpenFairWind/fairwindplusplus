//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include "../../../include/FairWindExtension.hpp"

#include <QDebug>



QImage fairwind::extensions::apps::dashboard::Dashboard::getIcon()  {
    return QImage(":/resources/images/icons/dashboard_icon.png");
}

QString fairwind::extensions::apps::dashboard::Dashboard::getId()  {
    return FairWindExtension::getId();
}

QString fairwind::extensions::apps::dashboard::Dashboard::getName()  {
    return FairWindExtension::getName();
}

QString fairwind::extensions::apps::dashboard::Dashboard::getDesc()  {
    return FairWindExtension::getDesc();
}

void fairwind::extensions::apps::dashboard::Dashboard::setMetaData(QJsonObject &metaData) {
    qDebug() << "fairwind::extensions::apps::dashboard::Dashboard::setMetaData -->" << metaData;
    FairWindExtension::setMetaData(metaData);
}

QWidget *fairwind::extensions::apps::dashboard::Dashboard::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    return nullptr;
}

QString fairwind::extensions::apps::dashboard::Dashboard::getUUID()  {
    return QString("19a2b772-9718-11eb-a8b3-0242ac130003");
}

