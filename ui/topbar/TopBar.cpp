//
// Created by Raffaele Montella on 12/04/21.
//

#include <QTimer>
#include <FairWindSdk/FairWind.hpp>
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
    connect(signalKDocument,&SignalKDocument::updatedNavigationCourseOverGroundTrue,this, &TopBar::updateNavigationCourseOverGroundTrue);
    connect(signalKDocument,&SignalKDocument::updatedNavigationSpeedOverGround,this, &TopBar::updateNavigationSpeedOverGround);

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

void TopBar::updateNavigationCourseOverGroundTrue() {

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QString path="vessels."+signalKDocument->getSelf()+".navigation.courseOverGroundTrue";

    QJsonValue positionValue = signalKDocument->subtree(path);
    if (positionValue.isObject()) {
        double courseOverGroundTrue = positionValue.toObject()["value"].toDouble()*57.2958;
        QString sCourseOverGroundTrue;
        sCourseOverGroundTrue = QString{"%1"}.arg(courseOverGroundTrue, 3, 'f', 0, '0');
        ui->label_COG->setText(sCourseOverGroundTrue);
    }
}

void TopBar::updateNavigationSpeedOverGround() {

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QString path="vessels."+signalKDocument->getSelf()+".navigation.speedOverGround";

    QJsonValue positionValue = signalKDocument->subtree(path);
    if (positionValue.isObject()) {
        double speedverGround = positionValue.toObject()["value"].toDouble()*1.94384;
        QString sSpeedOverGround;
        sSpeedOverGround = QString{"%1"}.arg(speedverGround, 3, 'f', 1, '0');
        ui->label_SOG->setText(sSpeedOverGround);
    }
}
