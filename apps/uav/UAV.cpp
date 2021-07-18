//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "UAV.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::uav::UAV::getIcon() const {
    return QImage(":/resources/images/icons/uav_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::uav::UAV::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::UAV();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::uav::UAV::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::uav::UAV::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::uav::UAV::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::uav::UAV::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::uav::UAV::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::uav::UAV::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::uav::UAV::getMetaData() {
    return AppBase::getMetaData();
}
