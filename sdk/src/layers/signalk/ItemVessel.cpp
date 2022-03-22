//
// Created by Raffaele Montella on 03/05/21.
//

#include <FairWind.hpp>
#include "FairWindSdk/layers/signalk/ItemVessel.hpp"

namespace fairwind::layers::signalk {
/*
 * ItemVessel - Public Constructor
 */
    ItemVessel::ItemVessel(QString &typeUuid) : ItemSignalK(typeUuid) {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the signalkdocument from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();
        if (getContext() == signalKDocument->getSelf()) {
            // Set the flag to ignore scale
            setFlags(QGV::ItemFlag::IgnoreScale);
        }
    }

    QImage ItemVessel::getImage() const {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the signalkdocument rom the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();
        if (getContext() == signalKDocument->getSelf()) {
            return QImage(":/resources/images/ship_red.png");
        }

        QString mmsi = signalKDocument->getMmsi(getContext());
        if (mmsi == signalKDocument->getMmsi()) {
            return QImage(":/resources/images/ais_self.png");
        }
        QString state = signalKDocument->getNavigationState(getContext());
        return QImage(":/resources/images/ais_active.png");
    }
}