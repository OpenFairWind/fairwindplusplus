//
// Created by Raffaele Montella on 05/05/21.
//

#include <QImage>
#include "QGVItemDefault.hpp"

QGVItemDefault::QGVItemDefault(QString &typeUuid): QGVItemSignalK(typeUuid) {

}

QImage QGVItemDefault::getImage() const {
    return QImage(":/resources/images/default.png");
}


