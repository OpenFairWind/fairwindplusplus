//
// Created by Raffaele Montella on 15/07/21.
//

#include <FairWindSdk/FairWind.hpp>
#include "Entertainment.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::entertainment::Entertainment::getIcon() const {
    return QImage(":/resources/images/icons/entertainment_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::entertainment::Entertainment::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::Entertainment();
    ui->setupUi(m_widget);

    auto fairwind=FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::entertainment::Entertainment::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::entertainment::Entertainment::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::entertainment::Entertainment::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::entertainment::Entertainment::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::entertainment::Entertainment::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::entertainment::Entertainment::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::entertainment::Entertainment::getMetaData() {
    return AppBase::getMetaData();
}