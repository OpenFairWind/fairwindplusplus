//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "IMSF.hpp"

/*
 * Returns the application icon
 */
QImage fairwind::apps::imsf::IMSF::getIcon() const {
    return QImage(":/resources/images/icons/imsf_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::imsf::IMSF::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::IMSF();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString fairwind::apps::imsf::IMSF::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::imsf::IMSF::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::imsf::IMSF::getDesc() const {
    return AppBase::getDesc();
}

void fairwind::apps::imsf::IMSF::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::imsf::IMSF::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::imsf::IMSF::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::imsf::IMSF::getMetaData() {
    return AppBase::getMetaData();
}
