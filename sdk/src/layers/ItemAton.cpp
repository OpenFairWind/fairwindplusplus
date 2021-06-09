//
// Created by Raffaele Montella on 03/05/21.
//

#include "FairWindSdk/layers/ItemAton.hpp"

ItemAton::ItemAton(QString &typeUuid): ItemSignalK(typeUuid) {

}

QImage ItemAton::getImage() const {
    return QImage(":/resources/images/ais_aton.png");
}