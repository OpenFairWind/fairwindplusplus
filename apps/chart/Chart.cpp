//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>

#include "Chart.hpp"

QImage fairwind::apps::chart::Chart::getIcon() const {
    return QImage(":/resources/images/icons/chart_icon.png");
}


QWidget *fairwind::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    m_widget = new QWidget();
    auto config = getConfig();
    auto displayChart = new DisplayChart(m_widget);
    displayChart->onInit(config);
    return m_widget;
}



QString fairwind::apps::chart::Chart::getId() const {
    return FairWindAppBase::getId();
}

QString fairwind::apps::chart::Chart::getName() const {
    return FairWindAppBase::getName();
}

QString fairwind::apps::chart::Chart::getDesc() const {
    return FairWindAppBase::getDesc();
}

void fairwind::apps::chart::Chart::onInit(QJsonObject *metaData) {
    FairWindAppBase::init(metaData);
}

QWidget *fairwind::apps::chart::Chart::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::chart::Chart::getConfig() {
    return FairWindAppBase::getConfig();
}





