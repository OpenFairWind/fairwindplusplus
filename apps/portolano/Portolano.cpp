//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Portolano.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::portolano::Portolano::getIcon() const {
    return QImage(":/resources/images/icons/portolano_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::portolano::Portolano::onStart(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Portolano();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::portolano::Portolano::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::portolano::Portolano::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::portolano::Portolano::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::portolano::Portolano::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::portolano::Portolano::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::portolano::Portolano::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::portolano::Portolano::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::portolano::Portolano::onCreate(QJsonObject *metaData) {
    AppBase::onCreate(metaData);
}

void fairwind::apps::portolano::Portolano::onResume() {
    AppBase::onResume();
}

void fairwind::apps::portolano::Portolano::onPause() {
    AppBase::onPause();
}

void fairwind::apps::portolano::Portolano::onStop() {
    AppBase::onStop();
}

void fairwind::apps::portolano::Portolano::onDestroy() {
    AppBase::onDestroy();
}

QJsonObject fairwind::apps::portolano::Portolano::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::portolano::Portolano::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::portolano::Portolano::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::portolano::Portolano::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}

QJsonObject fairwind::apps::portolano::Portolano::getSettings() {
    return AppBase::getSettings();
}