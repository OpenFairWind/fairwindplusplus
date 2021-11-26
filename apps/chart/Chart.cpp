//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <QLabel>
#include <QFile>
#include <FairWindSdk/IDisplay.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include "Chart.hpp"


/*
 * Returns the application icon
 */
QImage fairwind::apps::chart::Chart::getIcon() const {
    return QImage(":/resources/images/icons/chart_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *fairwind::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    auto widget = new QWidget();
    auto ui = new Ui::Chart();
    ui->setupUi(widget);

    auto fairwind=FairWind::getInstance();
    auto config = getConfig();

    auto displayChart = new fairwind::displays::DisplayChart();
    QMap<QString, QVariant> params;
    params["config"]=config;
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
    //QMetaObject::invokeMethod(this, "resizeWidgets", Qt::QueuedConnection);

    //return m_widgetWebApp;
    return widget;
}



QString fairwind::apps::chart::Chart::getId() const {
    return AppBase::getId();
}

QString fairwind::apps::chart::Chart::getName() const {
    return AppBase::getName();
}

QString fairwind::apps::chart::Chart::getDesc() const {
    return AppBase::getDesc();
}

QString fairwind::apps::chart::Chart::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::chart::Chart::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::chart::Chart::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::chart::Chart::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void fairwind::apps::chart::Chart::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::chart::Chart::onSettings(QTabWidget *tabWidget) {
    return nullptr;
}

QJsonObject fairwind::apps::chart::Chart::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::chart::Chart::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::chart::Chart::updateSettings(QString settingsID, QString newValue) {
    QDir appDataPath = QDir(getMetaData()["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile configsFile(appDataPath.absolutePath() + QDir::separator() + "config.json");
    configsFile.open(QFile::ReadWrite);

    QJsonDocument configsDocument = QJsonDocument().fromJson(configsFile.readAll());

    QJsonObject configs = configsDocument.object();

    QJsonValueRef ref = configs.find("Values").value();
    QJsonObject values = ref.toObject();

    values.insert(settingsID, newValue);

    ref = values;

    configsDocument.setObject(configs);

    if (configsFile.resize(0))
        configsFile.write(configsDocument.toJson());

    configsFile.close();
    setConfig(configs);
}

void fairwind::apps::chart::Chart::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}
