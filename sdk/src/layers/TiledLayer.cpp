//
// Created by Raffaele Montella on 21/05/21.
//

#include <QWidget>
#include "FairWindSdk/layers/TiledLayer.hpp"

fairwind::layers::TiledLayer::TiledLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

fairwind::layers::TiledLayer::~TiledLayer() {
}

QImage fairwind::layers::TiledLayer::getIcon() const {
    return QImage(":resources/images/icons/layer_tiled_icon.png");;
}

void fairwind::layers::TiledLayer::onInit(QMap<QString, QVariant> params) {
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

fairwind::layers::ILayer *fairwind::layers::TiledLayer::getNewInstance() {
    return static_cast<ILayer *>(new TiledLayer());
}

QWidget *fairwind::layers::TiledLayer::onLegenda() {
    return nullptr;
}

QWidget *fairwind::layers::TiledLayer::onSettings() {
    return nullptr;
}

QString fairwind::layers::TiledLayer::getClassName() const {
    return this->metaObject()->className();
}
