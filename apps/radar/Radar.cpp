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
QWidget *fairwind::apps::radar::Radar::onStart(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

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

QString fairwind::apps::radar::Radar::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::radar::Radar::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::radar::Radar::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::radar::Radar::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::radar::Radar::onCreate(QJsonObject *metaData) {
    AppBase::onCreate(metaData);
}

void fairwind::apps::radar::Radar::onResume() {
    AppBase::onResume();
}

void fairwind::apps::radar::Radar::onPause() {
    AppBase::onPause();
}

void fairwind::apps::radar::Radar::onStop() {
    AppBase::onStop();
}

void fairwind::apps::radar::Radar::onDestroy() {
    AppBase::onDestroy();
}

QJsonObject fairwind::apps::radar::Radar::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::radar::Radar::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::radar::Radar::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::radar::Radar::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}

QJsonObject fairwind::apps::radar::Radar::getSettings() {
    return AppBase::getSettings();
}