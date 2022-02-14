//
// Created by Raffaele Montella on 11/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/ILayout.hpp>
#include <utility>
#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::dashboard {
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

    }

    void MainPage::onAdded() {
        auto fairwind=FairWind::getInstance();
        auto args = getFairWindApp()->getArgs();

        if (args.contains("Config")) {

            auto config = args["Config"].toJsonObject();
            qDebug() << "Config: " << config;

            if (config.contains("pages") && config["pages"].isArray()) {
                QJsonArray arrayPages = config["pages"].toArray();
                for (auto page: arrayPages) {
                    if (page.isObject()) {
                        QJsonObject objectPage = page.toObject();
                        if (objectPage.contains("name") && objectPage["name"].isString()) {
                            auto pageName = objectPage["name"].toString();

                            QString layoutClassName = "fairwind::layouts::GridLayout";
                            if (objectPage.contains("class") && objectPage["class"].isString()) {
                                layoutClassName = objectPage["class"].toString();
                            }

                            layouts::ILayout *layout = fairwind->instanceLayout(layoutClassName);
                            if (layout) {
                                QMap<QString, QVariant> layoutParams;
                                layout->onInit(layoutParams);
                                auto pageWidget = layout->getWidget();
                                ui->tabWidget->addTab(pageWidget, pageName);
                                if (objectPage.contains("displays") && objectPage["displays"].isArray()) {
                                    QJsonArray arrayDisplays = objectPage["displays"].toArray();
                                    for (auto item: arrayDisplays) {
                                        if (item.isObject()) {
                                            QJsonObject objectItem = item.toObject();
                                            if (objectItem.contains("active") && objectItem["active"].isBool() &&
                                                objectItem["active"].toBool()) {

                                                QString displayClassName = "UI::DisplaySingleText";
                                                if (objectItem.contains("class") && objectItem["class"].isString()) {
                                                    displayClassName = objectItem["class"].toString();
                                                }

                                                QString layoutName = "left";
                                                if (objectItem.contains("layout") && objectItem["layout"].isString()) {
                                                    layoutName = objectItem["layout"].toString();
                                                }

                                                QMap<QString, QVariant> displayParams;
                                                for (const auto &key: objectItem.keys()) {
                                                    displayParams[key] = objectItem[key].toVariant();
                                                }

                                                displays::IDisplay *fairWindDisplay = fairwind->instanceDisplay(
                                                        displayClassName);
                                                if (fairWindDisplay) {
                                                    fairWindDisplay->onInit(displayParams);

                                                    layout->addDisplay(layoutName, fairWindDisplay);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    MainPage::~MainPage() {
        delete ui;
    }
} // fairwind::apps::Dashboard
