//
// Created by Raffaele Montella on 12/04/21.
//


#include <ui_BottomBar.h>
#include <FairWindSdk/FairWind.hpp>
#include "BottomBar.hpp"

BottomBar::BottomBar(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BottomBar) {
    ui->setupUi(parent);

    connect(ui->toolButton_Apps,&QToolButton::released,this,&BottomBar::apps_clicked);
    connect(ui->toolButton_Settings,&QToolButton::released,this,&BottomBar::settings_clicked);
}

void BottomBar::settings_clicked() {
    emit setSettings();
}

void BottomBar::apps_clicked() {
    setApps();
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument=fairWind->getSignalKDocument();
    signalKDocument->save("signalkmodel.json");
}

BottomBar::~BottomBar() {
    delete ui;
}
