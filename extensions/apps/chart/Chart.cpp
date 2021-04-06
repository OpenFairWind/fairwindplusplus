//
// Created by Raffaele Montella on 05/04/21.
//

#include "Chart.hpp"
#include "QGeoView/QGVWidget.h"

QImage fairwind::extensions::apps::chart::Chart::getIcon()  {
    return QImage(":/resources/images/icons/chart_icon.png");
}

QString fairwind::extensions::apps::chart::Chart::getId() {
    if (m_metaData.find("Extension") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["Extension"].toObject().find("Id") == m_metaData.end()) {
        return "";
    }

    return m_metaData["Extension"].toObject()["Id"].toString();
}

QString fairwind::extensions::apps::chart::Chart::getName() {

    if (m_metaData["Extension"].toObject().find("Name") == m_metaData.end()) {
        if (m_metaData.find("Name") == m_metaData.end()) {
            return "";
        }
        return m_metaData["Name"].toString();
    }

    return m_metaData["Extension"].toObject()["Name"].toString();
}

QString fairwind::extensions::apps::chart::Chart::getDesc()  {
    if (m_metaData.find("Description") == m_metaData.end()) {
        return "";
    }
    return m_metaData["Description"].toString();
}

void fairwind::extensions::apps::chart::Chart::setMetaData(QJsonObject &metaData) {
    qDebug() << "fairwind::extensions::FairWindExtension::setMetaData -->" << metaData;
    m_metaData = std::move(metaData);
}


QWidget *fairwind::extensions::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {

    m_widgetMapApp = new QGVWidget();

    return m_widgetMapApp;
}

QString fairwind::extensions::apps::chart::Chart::getUUID()  {
    return QString("0424ef46-9718-11eb-a8b3-0242ac130003");
}


