//
// Created by Raffaele Montella on 03/05/21.
//

#include "FairWindSdk/layers/signalk/ItemShoreBasestations.hpp"

namespace fairwind::layers::signalk {
    ItemShoreBasestations::ItemShoreBasestations(QString &typeUuid) : ItemSignalK(typeUuid) {

    }

    QImage ItemShoreBasestations::getImage() const {
        return QImage(":/resources/images/ais_shore.png");
    }
}