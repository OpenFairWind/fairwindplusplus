//
// Created by Raffaele Montella on 14/03/22.
//

#include <FairWindSdk/layers/signalk/ItemRegion.hpp>

namespace fairwind::layers::signalk {
    ItemRegion::ItemRegion(QString &typeUuid) : ItemSignalK(typeUuid) {

    }

    QImage ItemRegion::getImage() const {
        return QImage(":/resources/images/note.png");
    }
}