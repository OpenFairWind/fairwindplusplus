//
// Created by Raffaele Montella on 12/04/21.
//

#include <QTimer>
#include <core/FairWind.hpp>
#include "TopBar.hpp"
#include "ui_TopBar.h"

TopBar::TopBar(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TopBar) {
    ui->setupUi(parent);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TopBar::updateTime);
    timer->start(1000);

    auto fairWind = fairwind::FairWind::getInstance();

    auto signalKDocument = fairWind->getSignalKDocument();

    connect(signalKDocument,&SignalKDocument::updatedNavigationPosition,this, &TopBar::updateNavigationPosition);
}

void TopBar::updateTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->label_Time->setText(text);

    QDateTime dateTime = QDateTime::currentDateTime();
    text = dateTime.toString("dd-MM-yyyy");
    ui->label_Date->setText(text);
}

TopBar::~TopBar() {
    delete ui;
}

void TopBar::updateNavigationPosition() {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QString path="vessels."+signalKDocument->getSelf()+".navigation.position.value";

    QJsonValue positionValue = signalKDocument->subtree(path);
    if (positionValue.isObject()) {
        double latitude = positionValue.toObject()["latitude"].toDouble();
        double longitude = positionValue.toObject()["longitude"].toDouble();
        QString sLatitude, sLongitude;
        sLatitude = QString{"%1"}.arg(latitude, 6, 'f', 4, '0');
        sLongitude = QString{"%1"}.arg(longitude, 7, 'f', 4, '0');
        ui->label_Lat->setText(sLatitude);
        ui->label_Lon->setText(sLongitude);
    }

}
