//
// Created by Ciro Giuseppe De Vita on 08/02/22.
//

#include <QJsonArray>
#include <QDir>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/SignalKDocument.hpp>
#include <QGeoCoordinate>
#include "ResultItem.hpp"
#include "ui_ResultItem.h"

namespace __namespace__ {
    ResultItem::ResultItem(QWidget *parent, QJsonObject feature) :
            QWidget(parent), ui(new Ui::ResultItem), mFeature(feature) {
        ui->setupUi(this);
    }

    ResultItem::~ResultItem() {
        delete ui;
    }
} // __namespace__