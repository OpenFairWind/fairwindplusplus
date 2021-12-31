//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Chandlery.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::chandlery::Chandlery::getIcon() const {
    return QImage(":/resources/images/icons/chandlery_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::chandlery::Chandlery::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Chandlery();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::chandlery::Chandlery::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::chandlery::Chandlery::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::chandlery::Chandlery::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::chandlery::Chandlery::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::chandlery::Chandlery::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::chandlery::Chandlery::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::chandlery::Chandlery::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::chandlery::Chandlery::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QJsonObject fairwind::apps::chandlery::Chandlery::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::chandlery::Chandlery::getMetaData() {
    return AppBase::getMetaData();
}


void fairwind::apps::chandlery::Chandlery::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::chandlery::Chandlery::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}

void fairwind::apps::chandlery::Chandlery::setSettings(QJsonObject config) {
    AppBase::setSettings(config);
}

QJsonObject fairwind::apps::chandlery::Chandlery::getSettings() {
    return AppBase::getSettings();
}