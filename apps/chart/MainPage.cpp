//
// Created by Raffaele Montella on 11/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <QJsonObject>
#include <QJsonArray>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::chart {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        auto fairwind=FairWind::getInstance();
        
        auto config = ((FairWindApp *)fairWindApp)->getConfig();
        auto displayChart = new fairwind::displays::DisplayChart();
        QMap<QString, QVariant> params;
        params["config"]=config;
        displayChart->onInit(params);
        ui->horizontalLayout->addWidget(displayChart);

        QMap<QString, QLayout *> layouts;
        layouts["left"]=ui->verticalLayoutLeft;
        layouts["center"]=ui->horizontalLayout;
        layouts["right"]=ui->verticalLayoutRight;

        if (config.contains("Displays") && config["Displays"].isArray()) {
            QJsonArray arrayDisplays=config["Displays"].toArray();
            for (auto item:arrayDisplays) {
                if (item.isObject()) {
                    QJsonObject objectItem=item.toObject();
                    if (objectItem.contains("active") && objectItem["active"].isBool() && objectItem["active"].toBool()) {

                        QString className="UI::DisplaySingleText";
                        if (objectItem.contains("class") && objectItem["class"].isString()) {
                            className=objectItem["class"].toString();
                        }

                        QString layoutName="left";
                        if (objectItem.contains("layout") && objectItem["layout"].isString()) {
                            layoutName=objectItem["layout"].toString();
                        }

                        QMap<QString, QVariant> displayParams;
                        for (auto key:objectItem.keys()) {
                            displayParams[key]=objectItem[key].toVariant();
                        }

                        displays::IDisplay *fairWindDisplay=fairwind->instanceDisplay(className);
                        if (fairWindDisplay) {
                            fairWindDisplay->onInit(displayParams);
                        }

                        auto *widget = dynamic_cast<QWidget *>(fairWindDisplay);
                        if (widget) {
                            layouts[layoutName]->addWidget(widget);
                        }
                    }
                }
            }
        }

        ui->verticalLayoutLeft->addStretch(1);
        ui->verticalLayoutRight->addStretch(1);
    }

    MainPage::~MainPage() {
        delete ui;
    }
} // fairwind::apps::chart
