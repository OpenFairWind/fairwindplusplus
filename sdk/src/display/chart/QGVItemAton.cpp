//
// Created by Raffaele Montella on 03/05/21.
//

#include "QGVItemAton.hpp"

QGVItemAton::QGVItemAton(QString &typeUuid): QGVItemSignalK(typeUuid) {

}

QImage QGVItemAton::getImage() const {
    return QImage(":/resources/images/ais_aton.png");
}