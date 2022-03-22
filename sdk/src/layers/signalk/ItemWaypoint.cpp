//
// Created by Raffaele Montella on 14/03/22.
//

#include "FairWindSdk/layers/signalk/ItemWaypoint.hpp"

namespace fairwind::layers::signalk {

    ItemWaypoint::ItemWaypoint(QString &typeUuid) : ItemSignalK(typeUuid) {

    }

    QImage ItemWaypoint::getImage() const {
        return QImage(":/resources/images/symbols/symbol_marina.png");
    }

}