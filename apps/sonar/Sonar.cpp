//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Sonar.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::sonar::Sonar::getIcon() const {
    return QImage(":/resources/images/icons/sonar_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::sonar::Sonar::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Sonar();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::sonar::Sonar::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::sonar::Sonar::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::sonar::Sonar::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::sonar::Sonar::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::sonar::Sonar::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::sonar::Sonar::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::sonar::Sonar::getMetaData() {
    return AppBase::getMetaData();
}
