//
// Created by Raffaele Montella on 01/04/21.
//

#include <QImage>
#include <QPixmap>
#include "../include/FairWindApp.hpp"

QSharedPointer<QJsonDocument> fairwind::apps::FairWindApp::getSettings() {
    return QSharedPointer<QJsonDocument>(&settings);
}
