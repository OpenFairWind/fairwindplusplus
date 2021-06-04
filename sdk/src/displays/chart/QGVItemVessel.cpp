//
// Created by Raffaele Montella on 03/05/21.
//

#include <FairWind.hpp>
#include "QGVItemVessel.hpp"

QGVItemVessel::QGVItemVessel(QString &typeUuid): QGVItemSignalK(typeUuid) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    if (getContext()==signalKDocument->getSelf()) {
        setFlags(QGV::ItemFlag::IgnoreScale);
    }
}

QImage QGVItemVessel::getImage() const {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    if (getContext()==signalKDocument->getSelf()) {
        return QImage(":/resources/images/ship_red.png");
    }

    QString mmsi=signalKDocument->getMmsi(getContext());
    if (mmsi==signalKDocument->getMmsi()) {
        return QImage(":/resources/images/ais_self.png");
    }
    QString state=signalKDocument->getNavigationState(getContext());
    return QImage(":/resources/images/ais_active.png");
}

