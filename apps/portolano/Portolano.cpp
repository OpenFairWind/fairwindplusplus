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
QWidget *fairwind::apps::portolano::Portolano::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

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

void fairwind::apps::portolano::Portolano::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::portolano::Portolano::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::portolano::Portolano::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::portolano::Portolano::getMetaData() {
    return AppBase::getMetaData();
}
