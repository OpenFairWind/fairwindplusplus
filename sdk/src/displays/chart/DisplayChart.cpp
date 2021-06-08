//
// Created by Raffaele Montella on 22/04/21.
//

#include "QGeoView/QGVWidget.h"
#include "QGeoView/QGVLayer.h"
#include <QGeoView/QGVImage.h>
#include "QGeoView/QGVLayerOSM.h"
#include "QGeoView/QGVLayerGoogle.h"
#include "QGeoView/QGVLayerBing.h"

#include <QGeoView/QGVGlobal.h>
#include <QGeoView/QGVWidgetCompass.h>
#include <QGeoView/QGVWidgetScale.h>
#include <QJsonArray>
#include <QGeoView/QGVWidgetZoom.h>
#include <QAction>
#include <QClipboard>
#include <QDir>
#include <QGeoView/QGVDrawItem.h>
#include <QGuiApplication>
#include <FairWindSdk/SignalKDocument.hpp>
#include <FairWind.hpp>
#include <FairWindSdk/layers/SignalKLayer.hpp>

#include "ui_DisplayChart.h"
#include <FairWindSdk/displays//DisplayChart.hpp>
#include "QGVItemVessel.hpp"
#include "QGVItemShoreBasestations.hpp"
#include "QGVItemAton.hpp"

fairwind::displays::DisplayChart::DisplayChart(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplayChart) {
    ui->setupUi(this);

    m_widgetMap = new QGVMap();
    ui->gridLayout->addWidget(m_widgetMap,0,0);

    //QMetaObject::invokeMethod(this, "mapSetup", Qt::QueuedConnection);
}


fairwind::displays::DisplayChart::~DisplayChart() {
    delete ui;
}

QImage fairwind::displays::DisplayChart::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplayChart::onSettings() {
    return nullptr;
}

fairwind::displays::IDisplay *fairwind::displays::DisplayChart::getNewInstance() {
    return static_cast<IDisplay *>(new DisplayChart());
}

void fairwind::displays::DisplayChart::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";


    QDir("cacheDir").removeRecursively();
    mCache = new QNetworkDiskCache(this);
    mCache->setCacheDirectory("cacheDir");
    mManager = new QNetworkAccessManager(this);
    mManager->setCache(mCache);
    QGV::setNetworkManager(mManager);


    m_widgetMap->addWidget(new QGVWidgetCompass());
    m_widgetMap->addWidget(new QGVWidgetZoom());
    m_widgetMap->addWidget(new QGVWidgetScale(Qt::Horizontal));
    m_widgetMap->addWidget(new QGVWidgetScale(Qt::Vertical));


    //auto target = m_widgetMap->getProjection()->boundaryGeoRect();
    //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).scaleTo(target));

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    auto self = signalKDocument->getSelf();

    if (params.contains("config")) {
        mConfig = params["config"].toJsonObject();
        if (mConfig.contains("Layers") && mConfig["Layers"].isArray()) {
            auto layerSettings = mConfig["Layers"].toArray();
            for (auto layerSetting:layerSettings) {
                if (layerSetting.isObject()) {
                    QJsonObject layerSettingObject = layerSetting.toObject();
                    if (layerSettingObject.contains("active") && layerSettingObject["active"].isBool() &&
                        layerSettingObject["active"].toBool()) {
                        if (layerSettingObject.contains("class") && layerSettingObject["class"].isString()) {
                            auto className = layerSettingObject["class"].toString();
                            fairwind::layers::ILayer *fairWindLayer = fairWind->instanceLayer(className);
                            if (fairWindLayer) {
                                QMap<QString, QVariant> params;
                                for (const auto &key:layerSettingObject.keys()) {
                                    params[key] = layerSettingObject[key].toVariant();
                                }
                                fairWindLayer->onInit(params);

                                auto *qgvLayer = dynamic_cast<QGVLayer *>(fairWindLayer);
                                if (qgvLayer) {
                                    m_widgetMap->addItem(qgvLayer);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    signalKDocument->subscribe(self+".navigation.position.value",this,SLOT(DisplayChart::updateNavigationPosition));

    QGV::GeoPos geoPos = signalKDocument->getNavigationPosition();
    m_widgetMap->cameraTo(QGVCameraActions(m_widgetMap).moveTo(geoPos));
}

void fairwind::displays::DisplayChart::updateNavigationPosition(const QJsonObject update) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
}

QString fairwind::displays::DisplayChart::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplayChart::smaller() { return isVisible(); }
bool fairwind::displays::DisplayChart::bigger() { return isVisible(); }
