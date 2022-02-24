//
// Created by Raffaele Montella on 22/04/21.
//

#include <QGeoView/QGVWidget.h>
#include <QGeoView/QGVLayer.h>
#include <QGeoView/QGVLayerOSM.h>
#include <QGeoView/QGVLayerGoogle.h>
#include <QGeoView/QGVLayerBing.h>

#include <QGeoView/QGVImage.h>
#include <QGeoView/QGVGlobal.h>
#include <QGeoView/QGVWidgetMeasure.h>
#include <QGeoView/QGVWidgetCompass.h>
#include <QGeoView/QGVWidgetScale.h>
#include <QGeoView/QGVWidgetZoom.h>
#include <QGeoView/QGVDrawItem.h>

#include <QJsonArray>
#include <QAction>
#include <QClipboard>
#include <QDir>
#include <QGuiApplication>

#include <FairWindSdk/SignalKDocument.hpp>
#include <FairWind.hpp>
#include <FairWindSdk/layers/SignalKLayer.hpp>
#include <FairWindSdk/displays//DisplayChart.hpp>
#include <QNetworkAccessManager>

#include "FairWindSdk/layers/ItemVessel.hpp"
#include "FairWindSdk/layers/ItemShoreBasestations.hpp"
#include "FairWindSdk/layers/ItemAton.hpp"

#include "ui_DisplayChart.h"

/*
 * DisplayChart - Public Constructor
 */
fairwind::displays::DisplayChart::DisplayChart(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplayChart) {
    ui->setupUi(this);

    m_widgetMap = new QGVMap();
    ui->gridLayout->addWidget(m_widgetMap, 0, 0);

    //QMetaObject::invokeMethod(this, "mapSetup", Qt::QueuedConnection);
}

/*
 * ~DisplayChart - Destructor
 */
fairwind::displays::DisplayChart::~DisplayChart() {
    delete ui;
}

/*
 * getIcon
 * Returns the display's icon
 */
QImage fairwind::displays::DisplayChart::getIcon() const {
    return QImage(":resources/images/icons/display_chart_icon.png");
}

/*
 * onSettings
 * Returns the display's settings
 */
QWidget *fairwind::displays::DisplayChart::onSettings() {
    return nullptr;
}

/*
 * getNewInstance
 * Creates and returns a new IDisplay object
 */
fairwind::displays::IDisplay *fairwind::displays::DisplayChart::getNewInstance() {
    return static_cast<IDisplay *>(new DisplayChart());
}

/*
 * onInit
 * Initialization method
 */
void fairwind::displays::DisplayChart::onInit(QMap <QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    QDir("cacheDir").removeRecursively();
    mCache = new QNetworkDiskCache(this);
    mCache->setCacheDirectory("cacheDir");
    mManager = new QNetworkAccessManager(this);
    mManager->setCache(mCache);
    QGV::setNetworkManager(mManager);

    // Add different visual components to the display
    m_widgetMap->addWidget(new QGVWidgetCompass());
    m_widgetMap->addWidget(new QGVWidgetZoom());

    auto widgetScaleH = new QGVWidgetScale(Qt::Horizontal);
    widgetScaleH->setDistanceUnits(DistanceUnits::NauticalMiles);
    widgetScaleH->setUseMetersForSmallDistance(true);
    m_widgetMap->addWidget(widgetScaleH);

    auto widgetScaleV = new QGVWidgetScale(Qt::Vertical);
    widgetScaleV->setDistanceUnits(DistanceUnits::NauticalMiles);
    widgetScaleV->setUseMetersForSmallDistance(true);
    m_widgetMap->addWidget(widgetScaleV);

    auto widgetMeasure = new QGVWidgetMeasure();
    // Widget configuration
    const auto distanceLabelPrefix = QString("");
    const auto bearingLabelPrefix = QString("");
    const auto ballonValueSeparator = QString("-");
    const auto ballonBackground = QColor::fromRgb(0, 62, 126);
    const auto ballonText = Qt::white;
    const auto ballonTextPadding = 7;
    const auto lineColor = Qt::black;
    const auto lineWidth = 200;
    const auto iconPinMovement = QString(":/resources/pin-icon-highlight.png");
    const qreal pinMetersOffset{25000};
    const qreal leftPinAzimuthOffset{90};
    const qreal rightPinAzimuthOffset{270};

    const auto widgetBtnIcon = iconPinMovement;
    const auto widgetBtnSize = QSize(45, 45);

    const auto widgetBtnActiveColor = QColor::fromRgb(154, 211, 254);

    // How to change widget position on screen
    /* mWidgetMeasure->setAnchor(QPoint(30, 30), mWidgetMeasure->getWidgetAnchorEdges());
    mWidgetMeasure->setWidgetAnchorEdges({Qt::TopEdge, Qt::LeftEdge}); */

    // How to change widget btn icon/size
    // mWidgetMeasure->setWidgetBtnIcon(widgetBtnIcon);
    widgetMeasure->setWidgetBtnSize(widgetBtnSize);

    widgetMeasure->setPinStartingPointMetersOffset(pinMetersOffset);
    widgetMeasure->setLeftPinAzimuthOffset(leftPinAzimuthOffset);
    widgetMeasure->setRightPinAzimuthOffset(rightPinAzimuthOffset);

    widgetMeasure->setBtnExternalBorderColor(Qt::white);
    widgetMeasure->setBtnExternalRectColor(ballonBackground);
    widgetMeasure->setBtnInternalRectColor(Qt::white);
    widgetMeasure->setBtnActiveInternalRectColor(widgetBtnActiveColor);

    widgetMeasure->setDistanceLabelPrefix(distanceLabelPrefix);
    widgetMeasure->setBearingLabelPrefix(bearingLabelPrefix);
    widgetMeasure->setBallonValueSeparator(ballonValueSeparator);
    widgetMeasure->setBallonBackgroundColor(ballonBackground);
    widgetMeasure->setBallonTextColor(ballonText);
    widgetMeasure->setBallonTextPadding(ballonTextPadding);
    widgetMeasure->setLineColor(lineColor);
    widgetMeasure->setLineWidth(lineWidth);
    widgetMeasure->setIconPinMovement(iconPinMovement);
    widgetMeasure->setUnit(DistanceUnits::NauticalMiles);

    m_widgetMap->addWidget(widgetMeasure);

    //auto target = m_widgetMap->getProjection()->boundaryGeoRect();
    //m_widgetMapApp->cameraTo(QGVCameraActions(m_widgetMapApp).scaleTo(target));

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the SignalK document
    auto signalKDocument = fairWind->getSignalKDocument();
    // Get the self key from the SignalK document
    auto self = signalKDocument->getSelf();

    // Check if a configuration is provided
    if (params.contains("config")) {
        // Load new layers from the configuration and their details
        mConfig = params["config"].toJsonObject();
        if (mConfig.contains("Layers") && mConfig["Layers"].isArray()) {
            auto layerSettings = mConfig["Layers"].toArray();
            for (auto layerSetting: layerSettings) {
                if (layerSetting.isObject()) {
                    QJsonObject layerSettingObject = layerSetting.toObject();
                    if (layerSettingObject.contains("active") && layerSettingObject["active"].isBool() &&
                        layerSettingObject["active"].toBool()) {
                        if (layerSettingObject.contains("class") && layerSettingObject["class"].isString()) {
                            auto className = layerSettingObject["class"].toString();
                            fairwind::layers::ILayer *fairWindLayer = fairWind->instanceLayer(className);
                            if (fairWindLayer) {
                                QMap <QString, QVariant> params;
                                for (const auto &key: layerSettingObject.keys()) {
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

    // Subscribe to the navigation.position.value key to get the information from the SignalK server
    signalKDocument->subscribe(self + ".navigation.position.value", this, SLOT(DisplayChart::updateNavigationPosition));

    // Get the navigation position
    auto coordinate = signalKDocument->getNavigationPosition();
    // Move the camera to the new position in order to center the screen on the display
    m_widgetMap->cameraTo(QGVCameraActions(m_widgetMap).moveTo(QGV::GeoPos(coordinate.latitude(),coordinate.longitude()) ));
}

void fairwind::displays::DisplayChart::updateNavigationPosition(const QJsonObject update) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
}

/*
 * getClassName
 * Returns the display's class name
 */
QString fairwind::displays::DisplayChart::getClassName() const {
    return this->metaObject()->className();
}

/*
bool fairwind::displays::DisplayChart::smaller() { return isVisible(); }
bool fairwind::displays::DisplayChart::bigger() { return isVisible(); }
*/