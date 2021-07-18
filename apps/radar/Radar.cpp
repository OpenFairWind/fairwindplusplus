//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Radar.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::radar::Radar::getIcon() const {
    return QImage(":/resources/images/icons/radar_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::radar::Radar::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Radar();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::radar::Radar::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::radar::Radar::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::radar::Radar::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::radar::Radar::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::radar::Radar::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::radar::Radar::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::radar::Radar::getMetaData() {
    return AppBase::getMetaData();
}
