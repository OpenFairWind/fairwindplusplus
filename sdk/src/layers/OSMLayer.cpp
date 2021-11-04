//
// Created by Raffaele Montella on 21/05/21.
//

#include "FairWindSdk/layers/OSMLayer.hpp"

fairwind::layers::OSMLayer::OSMLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

fairwind::layers::OSMLayer::~OSMLayer() {}

QImage fairwind::layers::OSMLayer::getIcon() const {
    return QImage(":resources/images/icons/osm_icon.png");;
}

void fairwind::layers::OSMLayer::onInit(QMap<QString, QVariant> params) {}

fairwind::layers::ILayer *fairwind::layers::OSMLayer::getNewInstance() {
    return static_cast<ILayer *>(new OSMLayer());
}

QWidget *fairwind::layers::OSMLayer::onLegenda() {
    return nullptr;
}

QWidget *fairwind::layers::OSMLayer::onSettings() {
    return nullptr;
}

QString fairwind::layers::OSMLayer::getClassName() const {
    return this->metaObject()->className();
}