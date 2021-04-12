//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>

QString fairwind::apps::dashboard::Dashboard::getId() const {
    return fairwind::FairWindAppBase::getId();
}

QString fairwind::apps::dashboard::Dashboard::getName() const {
    return fairwind::FairWindAppBase::getName();
}

QString fairwind::apps::dashboard::Dashboard::getDesc() const {
    return fairwind::FairWindAppBase::getDesc();
}

QImage fairwind::apps::dashboard::Dashboard::getIcon() const {
    return QImage(":/resources/images/icons/dashboard_icon.png");
}

void fairwind::apps::dashboard::Dashboard::onInit(QJsonObject *metaData) {
    fairwind::FairWindAppBase::init(metaData);
}

QWidget *fairwind::apps::dashboard::Dashboard::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    QWidget *widget=new QWidget();
    ui=new Ui::Dashboard();

    ui->setupUi(widget);
    return widget;
}

QWidget *fairwind::apps::dashboard::Dashboard::onSettings(QTabWidget *tabWidgets) {
    QWidget *widget=new QWidget();
    uiSettings=new Ui::dashboard_Settings();

    uiSettings->setupUi(widget);
    return widget;
}

fairwind::apps::dashboard::Dashboard::~Dashboard() {
}
