//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Weather.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::weather::Weather::getIcon() const {
    return QImage(":/resources/images/icons/weather_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::weather::Weather::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Weather();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::weather::Weather::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::weather::Weather::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::weather::Weather::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::weather::Weather::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::weather::Weather::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::weather::Weather::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::weather::Weather::getMetaData() {
    return AppBase::getMetaData();
}
