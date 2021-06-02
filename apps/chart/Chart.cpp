//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <QLabel>
#include <FairWindSdk/IFairWindDisplay.hpp>

#include "Chart.hpp"


QImage fairwind::apps::chart::Chart::getIcon() const {
    return QImage(":/resources/images/icons/chart_icon.png");
}


QWidget *fairwind::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {



    m_widgetWebApp=new QWidget();
    ui=new Ui::Chart();
    ui->setupUi(m_widgetWebApp);

    auto fairwind=FairWind::getInstance();
    auto config = getConfig();

    auto displayChart = new DisplayChart();
    QMap<QString, QVariant> params;
    params["settings"]=config;
    displayChart->onInit(params);
    ui->horizontalLayout->addWidget(displayChart);

    QMap<QString, QLayout *> layouts;
    layouts["left"]=ui->verticalLayoutLeft;
    layouts["center"]=ui->horizontalLayout;
    layouts["right"]=ui->verticalLayoutRight;

    if (config.contains("displays") && config["displays"].isArray()) {
        QJsonArray arrayDisplays=config["displays"].toArray();
        for (auto item:arrayDisplays) {
            if (item.isObject()) {
                QJsonObject objectItem=item.toObject();
                if (objectItem.contains("active") && objectItem["active"].isBool() && objectItem["active"].toBool()) {

                    QMap<QString, QVariant> displayParams;
                    QString className="UI::DisplaySingleText";
                    QString layoutName="left";

                    if (objectItem.contains("class") && objectItem["class"].isString()) {
                        className=objectItem["class"].toString();
                    }

                    if (objectItem.contains("layout") && objectItem["layout"].isString()) {
                        layoutName=objectItem["layout"].toString();
                    }

                    if (objectItem.contains("label") && objectItem["label"].isString()) {
                        displayParams["label"]=objectItem["label"].toString();
                    }

                    if (objectItem.contains("fullPath") && objectItem["fullPath"].isString()) {
                        displayParams["fullPath"]=objectItem["fullPath"].toString();
                    }


                    displays::IFairWindDisplay *fairWindDisplay=fairwind->instanceDisplay(className);
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

    QMetaObject::invokeMethod(this, "resizeWidgets", Qt::QueuedConnection);

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

void fairwind::apps::chart::Chart::resizeWidgets() {
    QMap<QString, QLayout *> layouts;
    layouts["left"]=ui->verticalLayoutLeft;
    layouts["center"]=ui->horizontalLayout;
    layouts["right"]=ui->verticalLayoutRight;

    for (auto layoutName:layouts.keys()) {

        QLayout *layoutItem = layouts[layoutName];
        qDebug() << "layoutName:: " << layoutName;

        int nCount = layoutItem->count();
        int nVisible = 0;

        while (true) {
            nVisible = 0;
            for (int i = 0; i < nCount; ++i) {
                QWidget *widget = layoutItem->itemAt(i)->widget();
                if (widget) {
                    if (widget->isVisible()) {
                        nVisible++;
                    }
                }
            }
            if (nVisible == nCount) {
                break;
            }
            for (int i = 0; i < nCount; ++i) {
                auto *fairWindDisplay = reinterpret_cast<displays::IFairWindDisplay *>(layoutItem->itemAt(
                        i)->widget());
                if (fairWindDisplay) {
                    fairWindDisplay->smaller();
                }
            }
        }
    }
}





