//
// Created by Raffaele Montella on 22/04/21.
//

#include <FairWind.hpp>
#include "DisplayPosition.hpp"

DisplayPosition::DisplayPosition(QWidget *parent) :
        DisplayDoubleText(parent) {

    auto fairWind = fairwind::FairWind::getInstance();

    auto signalKDocument = fairWind->getSignalKDocument();

    connect(signalKDocument,&SignalKDocument::updatedNavigationPosition,this, &DisplayPosition::updatePosition);

}

DisplayPosition::~DisplayPosition() {

}

void DisplayPosition::updatePosition() {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QString path="vessels."+signalKDocument->getSelf()+".navigation.position.value";

    QJsonValue positionValue = signalKDocument->subtree(path);
    if (positionValue.isObject()) {
        double latitude = positionValue.toObject()["latitude"].toDouble();
        double longitude = positionValue.toObject()["longitude"].toDouble();
        QString sLatitude, sLongitude;
        sLatitude = QString{"%1"}.arg(latitude, 6, 'f', 4, '0');
        sLongitude = QString{"%1"}.arg(longitude, 7, 'f', 4, '0');
        setText1(sLatitude);
        setText2(sLongitude);
    }
}
