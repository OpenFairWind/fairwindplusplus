//
// Created by Raffaele Montella on 05/05/21.
//

#include <QImage>
#include "FairWindSdk/layers/ItemDefault.hpp"

ItemDefault::ItemDefault(QString &typeUuid): ItemSignalK(typeUuid) {

}

QImage ItemDefault::getImage() const {
    return QImage(":/resources/images/default.png");
}


