//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Video.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::video::Video::getIcon() const {
    return QImage(":/resources/images/icons/video_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::video::Video::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Video();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::video::Video::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::video::Video::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::video::Video::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::video::Video::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::video::Video::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::video::Video::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::video::Video::getLicense() const {
    return fairwind::AppBase::getLicense();
}

void fairwind::apps::video::Video::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QJsonObject fairwind::apps::video::Video::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::video::Video::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::video::Video::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void fairwind::apps::video::Video::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}