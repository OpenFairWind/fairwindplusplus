//
// Created by __author__ on __date__.
//

#include <FairWindSdk/FairWind.hpp>
#include "__Appname__.hpp"

/*
 * Returns the application icon
 */
QImage __namespace__::__Appname__::getIcon() const {
    return QImage(":/resources/images/icons/__appname___icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *__namespace__::__Appname__::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::__Appname__();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    return m_widget;
}



QString __namespace__::__Appname__::getId() const {
    return AppBase::getId();
}

QString __namespace__::__Appname__::getName() const {
    return AppBase::getName();
}

QString __namespace__::__Appname__::getDesc() const {
    return AppBase::getDesc();
}

void __namespace__::__Appname__::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *__namespace__::__Appname__::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject __namespace__::__Appname__::getConfig() {
    return AppBase::getConfig();
}

QJsonObject __namespace__::__Appname__::getMetaData() {
    return AppBase::getMetaData();
}
