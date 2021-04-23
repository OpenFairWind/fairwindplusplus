//
// Created by Raffaele Montella on 22/04/21.
//

#include "QGeoView/QGVWidget.h"
#include "QGeoView/QGVLayer.h"
#include "QGeoView/QGVLayerOSM.h"
#include "QGeoView/QGVLayerGoogle.h"
#include "QGeoView/QGVLayerBing.h"

#include <QGeoView/QGVGlobal.h>
#include <QGeoView/QGVWidgetCompass.h>
#include <QGeoView/QGVWidgetScale.h>
#include <QGeoView/QGVWidgetZoom.h>
#include <QAction>
#include <QClipboard>
#include <QDir>
#include <QGeoView/QGVDrawItem.h>
#include <QGuiApplication>
#include <FairWindSdk/SignalKDocument.hpp>
#include <FairWind.hpp>

#include "ui_DisplayChart.h"
#include "DisplayChart.hpp"

DisplayChart::DisplayChart(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplayChart) {
    ui->setupUi(parent);

    m_widgetMap = new QGVMap();
    ui->gridLayout->addWidget(m_widgetMap,0,0);

    QMetaObject::invokeMethod(this, "mapSetup", Qt::QueuedConnection);
}


DisplayChart::~DisplayChart() {
    delete ui;
}

void DisplayChart::mapSetup() {
    QDir("cacheDir").removeRecursively();
    mCache = new QNetworkDiskCache(this);
    mCache->setCacheDirectory("cacheDir");
    mManager = new QNetworkAccessManager(this);
    mManager->setCache(mCache);
    QGV::setNetworkManager(mManager);


    /*
     * List of available widgets.
     */
    QList<QPair<QString, QGVWidget*>> widgets = {
            { "Compass", new QGVWidgetCompass() },
            { "ZoomButtons", new QGVWidgetZoom() },
            { "ScaleHorizontal", new QGVWidgetScale(Qt::Horizontal) },
            { "ScaleVertical", new QGVWidgetScale(Qt::Vertical) },
    };
    /*
     * Widgets will be owned by map.
     */
    for (auto pair : widgets) {
        auto name = pair.first;
        auto widget = pair.second;
        m_widgetMap->addWidget(widget);
    }

    const QString customURI = "http://c.tile.stamen.com/watercolor/${z}/${x}/${y}.jpg";
    const QList<QPair<QString, QGVLayer*>> layers = {
            { "OSM", new QGVLayerOSM() },
            { "GOOGLE_SATELLITE", new QGVLayerGoogle(QGV::TilesType::Satellite) },
            { "GOOGLE_HYBRID", new QGVLayerGoogle(QGV::TilesType::Hybrid) },
            { "GOOGLE_SCHEMA", new QGVLayerGoogle(QGV::TilesType::Schema) },
            { "BING_SATELLITE", new QGVLayerBing(QGV::TilesType::Satellite) },
            { "BING_HYBRID", new QGVLayerBing(QGV::TilesType::Hybrid) },
            { "BING_SCHEMA", new QGVLayerBing(QGV::TilesType::Schema) },
            { "CUSTOM_OSM", new QGVLayerOSM(customURI) },
    };
    /*
     * Layers will be owned by map.
     */
    for (auto pair : layers) {
        auto name = pair.first;
        auto layer = pair.second;
        layer->hide();
        m_widgetMap->addItem(layer);
    }
    layers[0].second->show();

    auto target = m_widgetMap->getProjection()->boundaryGeoRect();
    //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).scaleTo(target));

    //QGV::GeoPos geoPos(40.75, 14.28);
    //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).moveTo(geoPos));

    auto layer = new QGVLayer();
    layer->setName("Vessels");
    layer->setDescription("Demo for Vessels");
    m_widgetMap->addItem(layer);
    m_self = new QGVImage();
    m_self->setFlags(QGV::ItemFlag::IgnoreScale);
    layer->addItem(m_self);

    auto fairWind = fairwind::FairWind::getInstance();

    auto signalKDocument = fairWind->getSignalKDocument();

    connect(signalKDocument,&SignalKDocument::updatedNavigationPosition,this, &DisplayChart::updateNavigationPosition);


}

void DisplayChart::updateNavigationPosition() {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QString path="vessels."+signalKDocument->getSelf()+".navigation.position.value";

    QJsonValue positionValue = signalKDocument->subtree(path);
    if (positionValue.isObject()) {
        double latitude = positionValue.toObject()["latitude"].toDouble();
        double longitude = positionValue.toObject()["longitude"].toDouble();
        QGV::GeoPos geoPos(latitude, longitude);
        //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).moveTo(geoPos));
        QImage image(":/resources/images/ship_red.png");
        QMatrix rot;

        path="vessels."+signalKDocument->getSelf()+".navigation.courseOverGroundTrue";
        double courseOverGroundTrue = signalKDocument->subtree(path)["value"].toDouble()*57.2958;

        m_self->loadImage(image.transformed(rot.rotate(courseOverGroundTrue)));
        m_self->setGeometry(QGV::GeoPos(latitude,longitude),QSize(64,64),QPoint(32,32));
    }

}
