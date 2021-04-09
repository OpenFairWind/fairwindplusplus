//
// Created by Raffaele Montella on 05/04/21.
//

#include "Chart.hpp"
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

QImage fairwind::apps::chart::Chart::getIcon() const {
    return QImage(":/resources/images/icons/chart_icon.png");
}


QWidget *fairwind::apps::chart::Chart::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    m_widgetMapApp = new QGVMap();

    auto actPosition = new QAction("Print position", this);
    m_widgetMapApp->addAction(actPosition);
    connect(actPosition, &QAction::triggered, actPosition, [this]() {
        auto cam = m_widgetMapApp->getCamera();
        auto rect = cam.getProjection()->projToGeo(cam.projRect());
        auto pos = cam.getProjection()->projToGeo(cam.projRect().center());
        qInfo() << "current geo-rect" << rect;
        qInfo() << "current geo-center" << pos;
    });

    auto actSelectView = new QAction("Select all (view)", this);
    m_widgetMapApp->addAction(actSelectView);
    connect(actSelectView, &QAction::triggered, actSelectView, [this]() {
        m_widgetMapApp->unselectAll();
        auto selection = m_widgetMapApp->search(m_widgetMapApp->getCamera().projRect());
        for (auto item : selection) {
            item->select();
        }
    });

    auto actUnselect = new QAction("Unselect all", this);
    m_widgetMapApp->addAction(actUnselect);
    connect(actUnselect, &QAction::triggered, actUnselect, [this]() { m_widgetMapApp->unselectAll(); });

    auto actFront = new QAction("Bring to front (selected)", this);
    m_widgetMapApp->addAction(actFront);
    connect(actFront, &QAction::triggered, actFront, [this]() {
        for (QGVItem* item : m_widgetMapApp->getSelections()) {
            item->bringToFront();
        }
    });

    auto actBack = new QAction("Send to back (selected)", this);
    m_widgetMapApp->addAction(actBack);
    connect(actBack, &QAction::triggered, actBack, [this]() {
        for (QGVItem* item : m_widgetMapApp->getSelections()) {
            item->sendToBack();
        }
    });

    auto actOpacityPlus = new QAction("+25% opacity (selected)", this);
    m_widgetMapApp->addAction(actOpacityPlus);
    connect(actOpacityPlus, &QAction::triggered, actOpacityPlus, [this]() {
        for (QGVItem* item : m_widgetMapApp->getSelections()) {
            item->setOpacity(item->getOpacity() + 0.25);
        }
    });

    auto actOpacityMinus = new QAction("-25% opacity (selected)", this);
    m_widgetMapApp->addAction(actOpacityMinus);
    connect(actOpacityMinus, &QAction::triggered, actOpacityMinus, [this]() {
        for (QGVItem* item : m_widgetMapApp->getSelections()) {
            item->setOpacity(item->getOpacity() - 0.25);
        }
    });

    auto actImage = new QAction("Copy as image", this);
    m_widgetMapApp->addAction(actImage);
    connect(actImage, &QAction::triggered, actPosition, [this]() {
        QGuiApplication::clipboard()->setImage(m_widgetMapApp->grabMapView(true).toImage());
    });


    //QMetaObject::invokeMethod(this, "mapSetup", Qt::QueuedConnection);
    mapSetup();
    return m_widgetMapApp;
}

void fairwind::apps::chart::Chart::mapSetup() {
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
        m_widgetMapApp->addWidget(widget);
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
        m_widgetMapApp->addItem(layer);
    }
    layers[0].second->show();

    auto target = m_widgetMapApp->getProjection()->boundaryGeoRect();
    //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).scaleTo(target));
    QGV::GeoPos geoPos(40.75, 14.28);
    m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).moveTo(geoPos));

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

void fairwind::apps::chart::Chart::init(QJsonObject *metaData) {
    FairWindAppBase::init(metaData);
}



