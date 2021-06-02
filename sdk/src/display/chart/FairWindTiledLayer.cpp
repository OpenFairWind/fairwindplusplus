//
// Created by Raffaele Montella on 21/05/21.
//

#include <QWidget>
#include "FairWindTiledLayer.hpp"

FairWindTiledLayer::FairWindTiledLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

FairWindTiledLayer::~FairWindTiledLayer() {
}

QImage FairWindTiledLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");;
}

void FairWindTiledLayer::onInit(QMap<QString, QVariant> params) {
    if (params.contains("name")) {
        setName(params["name"].toString());
    }

    if (params.contains("description")) {
        setDescription(params["description"].toString());
    }

    if (params.contains("url")) {
        setUrl(params["url"].toString());
    }
}

fairwind::layers::IFairWindLayer *FairWindTiledLayer::getNewInstance() {
    return static_cast<IFairWindLayer *>(new FairWindTiledLayer());
}

QWidget *FairWindTiledLayer::onLegenda() {
    return nullptr;
}

QWidget *FairWindTiledLayer::onSettings() {
    return nullptr;
}

QString FairWindTiledLayer::getClassName() const {
    return this->metaObject()->className();
}
