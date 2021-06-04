//
// Created by Raffaele Montella on 03/05/21.
//

#include "QGVItemShoreBasestations.hpp"

QGVItemShoreBasestations::QGVItemShoreBasestations(QString &typeUuid): QGVItemSignalK(typeUuid) {

}

QImage QGVItemShoreBasestations::getImage() const {
    return QImage(":/resources/images/ais_shore.png");
}