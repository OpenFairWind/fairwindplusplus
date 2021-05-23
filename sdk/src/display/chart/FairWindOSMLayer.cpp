//
// Created by Raffaele Montella on 21/05/21.
//

#include "FairWindOSMLayer.hpp"

FairWindOSMLayer::FairWindOSMLayer(): QGVLayerOSM() {
    setName("Open Street Map");
    setDescription("The Open Street Map basemap.");
}

FairWindOSMLayer::~FairWindOSMLayer() {
}

QImage FairWindOSMLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");;
}

void FairWindOSMLayer::onInit(QMap<QString, QVariant> params) {

}

fairwind::layers::IFairWindLayer *FairWindOSMLayer::getNewInstance() {
    return static_cast<IFairWindLayer *>(new FairWindOSMLayer());
}

QWidget *FairWindOSMLayer::onLegenda() {
    return nullptr;
}

QWidget *FairWindOSMLayer::onSettings() {
    return nullptr;
}
