//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <QLabel>
#include <FairWindSdk/DisplayGauge.hpp>

#include "Chart.hpp"


QImage fairwind::apps::chart::Chart::getIcon() const {
    return QImage(":/resources/images/icons/chart_icon.png");
}


QWidget *fairwind::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {



    m_widgetWebApp=new QWidget();
    ui=new Ui::Chart();
    ui->setupUi(m_widgetWebApp);

    auto config = getConfig();
    auto displayChart = new DisplayChart(ui->widgetCenter);
    displayChart->onInit(config);


    auto layoutLeft = new QVBoxLayout;

    auto layoutRight= new QVBoxLayout;

    //auto displayGauge1 = new DisplayGauge();
    //layoutLeft->addWidget(displayGauge1);

    /*
    auto l1 = new QLabel();
    l1->setText("AAA");
    layoutLeft->addWidget(l1);
    */

    auto displaySingle1 = new DisplaySingleText();
    //displaySingle1->setLabel("SOG");
    displaySingle1->subscribe("${self}.navigation.speedOverGround");
    layoutLeft->addWidget(displaySingle1);


    auto displaySingle2 = new DisplaySingleText();
    //displaySingle2->setLabel("COG");
    displaySingle2->subscribe("${self}.navigation.courseOverGroundTrue");
    layoutLeft->addWidget(displaySingle2);

    auto displaySingle3 = new DisplaySingleText();
    //displaySingle3->setLabel("Boat Speed");
    displaySingle3->subscribe("${self}.navigation.speedThroughWater");
    layoutLeft->addWidget(displaySingle3);


    auto displaySingle4 = new DisplaySingleText();
    //displaySingle4->setLabel("Heading T");
    displaySingle4->subscribe("${self}.navigation.headingTrue");
    layoutLeft->addWidget(displaySingle4);

    auto displaySingle5 = new DisplaySingleText();
    //displaySingle5->setLabel("AWS");
    displaySingle5->subscribe("${self}.environment.wind.speedApparent");
    layoutLeft->addWidget(displaySingle5);


    auto displaySingle6 = new DisplaySingleText();
    //displaySingle6->setLabel("AWA");
    displaySingle6->subscribe("${self}.environment.wind.angleApparent");
    layoutLeft->addWidget(displaySingle6);

    /*
    auto displayDouble = new DisplayDoubleText();
    displayDouble->setLabel("Double");
    displayDouble->setText1("-1.--");
    displayDouble->setText2("-2.--");
    layoutLeft->addWidget(displayDouble);
    */

    /*
    auto tb1 = new QToolButton();
    tb1->setText("Center");
    layoutRight->addWidget(tb1);
    */

    ui->widgetLeft->setLayout(layoutLeft);
    ui->widgetRight->setLayout(layoutRight);

    return m_widgetWebApp;
}



QString fairwind::apps::chart::Chart::getId() const {
    return FairWindAppBase::getId();
}

QString fairwind::apps::chart::Chart::getName() const {
    return FairWindAppBase::getName();
}

QString fairwind::apps::chart::Chart::getDesc() const {
    return FairWindAppBase::getDesc();
}

void fairwind::apps::chart::Chart::onInit(QJsonObject *metaData) {
    FairWindAppBase::init(metaData);
}

QWidget *fairwind::apps::chart::Chart::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::chart::Chart::getConfig() {
    return FairWindAppBase::getConfig();
}





