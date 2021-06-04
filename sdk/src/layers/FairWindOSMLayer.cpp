//
// Created by Raffaele Montella on 21/05/21.
//

#include "FairWindSdk/layers/FairWindOSMLayer.hpp"

fairwind::layers::FairWindOSMLayer::FairWindOSMLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

fairwind::layers::FairWindOSMLayer::~FairWindOSMLayer() {
}

QImage fairwind::layers::FairWindOSMLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");;
}

void fairwind::layers::FairWindOSMLayer::onInit(QMap<QString, QVariant> params) {

}

fairwind::layers::IFairWindLayer *fairwind::layers::FairWindOSMLayer::getNewInstance() {
    return static_cast<IFairWindLayer *>(new FairWindOSMLayer());
}

QWidget *fairwind::layers::FairWindOSMLayer::onLegenda() {
    return nullptr;
}

QWidget *fairwind::layers::FairWindOSMLayer::onSettings() {
    return nullptr;
}

QString fairwind::layers::FairWindOSMLayer::getClassName() const {
    return this->metaObject()->className();
}
