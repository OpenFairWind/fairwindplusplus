//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/ILayout.hpp>

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
                            for (auto item:arrayDisplays) {
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
                                        for (const auto &key:objectItem.keys()) {
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
