//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>

QString fairwind::apps::dashboard::Dashboard::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::dashboard::Dashboard::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::dashboard::Dashboard::getDesc() const {
    return fairwind::AppBase::getDesc();
}

QImage fairwind::apps::dashboard::Dashboard::getIcon() const {
    return QImage(":/resources/images/icons/dashboard_icon.png");
}

void fairwind::apps::dashboard::Dashboard::onInit(QJsonObject *metaData) {
    fairwind::AppBase::onInit(metaData);
}

QWidget *fairwind::apps::dashboard::Dashboard::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {
    QWidget *widget=new QWidget();
    ui=new Ui::Dashboard();

    ui->setupUi(widget);

    auto fairwind=FairWind::getInstance();
    auto config = getConfig();
    qDebug() << "fairwind::apps::dashboard::Dashboard::onGui :" << config;


    if (config.contains("pages") && config["pages"].isArray()) {
        QJsonArray arrayPages = config["pages"].toArray();
        for (auto page:arrayPages) {
            if (page.isObject()) {
                QJsonObject objectPage = page.toObject();
                if (objectPage.contains("name") && objectPage["name"].isString()) {
                    QString pageName=objectPage["name"].toString();
                    auto pageWidget = new QWidget();
                    auto horizontalLayout = new QHBoxLayout();
                    horizontalLayout->addStretch(1);
                    pageWidget->setLayout(horizontalLayout);
                    QMap<QString, QLayout *> layouts;
                    layouts["00"]=horizontalLayout;
                    layouts["01"]=horizontalLayout;
                    layouts["02"]=horizontalLayout;
                    layouts["03"]=horizontalLayout;
                    ui->tabWidget->addTab(pageWidget,pageName);
                    if (objectPage.contains("displays") && objectPage["displays"].isArray()) {
                        QJsonArray arrayDisplays = objectPage["displays"].toArray();
                        for (auto item:arrayDisplays) {
                            if (item.isObject()) {
                                QJsonObject objectItem = item.toObject();
                                if (objectItem.contains("active") && objectItem["active"].isBool() &&
                                    objectItem["active"].toBool()) {

                                    QString className = "UI::DisplaySingleText";
                                    if (objectItem.contains("class") && objectItem["class"].isString()) {
                                        className = objectItem["class"].toString();
                                    }

                                    QString layoutName = "left";
                                    if (objectItem.contains("layout") && objectItem["layout"].isString()) {
                                        layoutName = objectItem["layout"].toString();
                                    }
                                    if (layouts.contains(layoutName)) {

                                        QMap<QString, QVariant> displayParams;
                                        for (const auto& key:objectItem.keys()) {
                                            displayParams[key] = objectItem[key].toVariant();
                                        }

                                        displays::IDisplay *fairWindDisplay = fairwind->instanceDisplay(className);
                                        if (fairWindDisplay) {
                                            fairWindDisplay->onInit(displayParams);
                                        }

                                        auto widget = dynamic_cast<QWidget *>(fairWindDisplay);
                                        if (widget) {
                                            layouts[layoutName]->addWidget(widget);
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

QJsonObject fairwind::apps::dashboard::Dashboard::getConfig() {
    return AppBase::getConfig();
}
