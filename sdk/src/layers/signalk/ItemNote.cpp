//
// Created by Raffaele Montella on 14/03/22.
//

#include <FairWindSdk/layers/signalk/ItemNote.hpp>

namespace fairwind::layers::signalk {
    ItemNote::ItemNote(QString &typeUuid) : ItemSignalK(typeUuid) {

    }

    QImage ItemNote::getImage() const {
        return QImage(":/resources/images/note.png");
    }
}