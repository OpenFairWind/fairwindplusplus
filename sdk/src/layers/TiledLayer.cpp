//
// Created by Raffaele Montella on 21/05/21.
//

#include <QWidget>
#include "FairWindSdk/layers/TiledLayer.hpp"

fairwind::layers::FairWindTiledLayer::FairWindTiledLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

fairwind::layers::FairWindTiledLayer::~FairWindTiledLayer() {
}

QImage fairwind::layers::FairWindTiledLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");;
}

void fairwind::layers::FairWindTiledLayer::onInit(QMap<QString, QVariant> params) {
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

fairwind::layers::ILayer *fairwind::layers::FairWindTiledLayer::getNewInstance() {
    return static_cast<ILayer *>(new FairWindTiledLayer());
}

QWidget *fairwind::layers::FairWindTiledLayer::onLegenda() {
    return nullptr;
}

QWidget *fairwind::layers::FairWindTiledLayer::onSettings() {
    return nullptr;
}

QString fairwind::layers::FairWindTiledLayer::getClassName() const {
    return this->metaObject()->className();
}
