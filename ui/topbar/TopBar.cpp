//
// Created by Raffaele Montella on 12/04/21.
//

#include <QTimer>

#include <FairWindSdk/FairWind.hpp>

#include "TopBar.hpp"
#include "ui_TopBar.h"

/*
 * TopBar
 * Public Constructor - This presents some useful infos at the top of the screen
 */
fairwind::ui::topbar::TopBar::TopBar(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TopBar) {
    // Setup the UI
    ui->setupUi(parent);

    // Create a new timer which will contain the current time
    QTimer *timer = new QTimer(this);
    // When the timer stops, update the time
    connect(timer, &QTimer::timeout, this, &TopBar::updateTime);
    // Start the timer
    timer->start(1000);

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the signalk document from the FairWind singleton itslef
    auto signalKDocument = fairWind->getSignalKDocument();

    /*
    connect(signalKDocument,&SignalKDocument::updated,this, &TopBar::onUpdate);
    connect(signalKDocument,&SignalKDocument::updatedNavigationPosition,this, &TopBar::updateNavigationPosition);
    connect(signalKDocument,&SignalKDocument::updatedNavigationCourseOverGroundTrue,this, &TopBar::updateNavigationCourseOverGroundTrue);
    connect(signalKDocument,&SignalKDocument::updatedNavigationSpeedOverGround,this, &TopBar::updateNavigationSpeedOverGround);
     */

    // Get the signalk document's string
    QString self = signalKDocument->getSelf();
    // Subscribe to signalk and make sure that navigation infos are updated accordingly
    signalKDocument->subscribe(self + ".navigation.position.value", this, SLOT(TopBar::updateNavigationPosition));
    signalKDocument->subscribe(self + ".navigation.courseOverGroundTrue.value", this,
                               SLOT(TopBar::updateNavigationCourseOverGroundTrue));
    signalKDocument->subscribe(self + ".navigation.speedOverGround.value", this,
                               SLOT(TopBar::updateNavigationSpeedOverGround));
}

/*
 * updateTime
 * Method called to update the current datetime
 */
void fairwind::ui::topbar::TopBar::updateTime() {
    // Get the current time
    QTime time = QTime::currentTime();
    // Get the current time in hh:mm format
    QString text = time.toString("hh:mm");

    if ((time.second() % 2) == 0)
        text[2] = ' ';
    // Set the time label from the UI to the formatted time
    ui->label_Time->setText(text);

    // Get the current date
    QDateTime dateTime = QDateTime::currentDateTime();
    // Get the current date in dd-MM-yyy format
    text = dateTime.toString("dd-MM-yyyy");
    // Set the date label from the UI to the formatted date
    ui->label_Date->setText(text);
}

/*
 * ~TopBar
 * TopBar's destructor
 */
fairwind::ui::topbar::TopBar::~TopBar() {
    delete ui;
}

/*
 * updateNavigationPosition
 * Method called in accordance to signalk to update the navigation position
 */
void fairwind::ui::topbar::TopBar::updateNavigationPosition(const QJsonObject update) {
    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the signalk document from the FairWind singleton itself
    auto signalKDocument = fairWind->getSignalKDocument();
    // Set the search path
    QString path = signalKDocument->getSelf() + ".navigation.position.value";

    // Get the postion value from the signalk document
    QJsonValue positionValue = signalKDocument->subtree(path);
    // Check if the value is valid
    if (positionValue.isObject()) {
        // Get latitude
        double latitude = positionValue.toObject()["latitude"].toDouble();
        // Get longitude
        double longitude = positionValue.toObject()["longitude"].toDouble();
        // Build formatted coordinates
        QString sLatitude, sLongitude;
        sLatitude = QString{"%1"}.arg(latitude, 6, 'f', 4, '0');
        sLongitude = QString{"%1"}.arg(longitude, 7, 'f', 4, '0');
        // Set the latitude label from the UI to the formatted latitude
        ui->label_Lat->setText(sLatitude);
        // Set the longitude label from the UI to the formatted longitude
        ui->label_Lon->setText(sLongitude);
    }
}

/*
 * updateNavigationCourseOverGroundTrue
 * Method called in accordance to signalk to update the navigation course over ground
 */
void fairwind::ui::topbar::TopBar::updateNavigationCourseOverGroundTrue(const QJsonObject update) {
    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the signalk document from the FairWind singleton itself
    auto signalKDocument = fairWind->getSignalKDocument();
    // Set the search path
    QString path = signalKDocument->getSelf() + ".navigation.courseOverGroundTrue";

    // Get the position value
    QJsonValue positionValue = signalKDocument->subtree(path);
    // Check if the value is valid
    if (positionValue.isObject()) {
        // Get the course value
        double courseOverGroundTrue = positionValue.toObject()["value"].toDouble() * 57.2958;
        // Build the formatted value
        QString sCourseOverGroundTrue;
        sCourseOverGroundTrue = QString{"%1"}.arg(courseOverGroundTrue, 3, 'f', 0, '0');
        // Set the course over ground label from the UI to the formatted value
        ui->label_COG->setText(sCourseOverGroundTrue);
    }
}

/*
 * updateNavigationSpeedOverGround
 * Method called in accordance to signalk to update the navigation speed over ground
 */
void fairwind::ui::topbar::TopBar::updateNavigationSpeedOverGround(const QJsonObject update) {
    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the signalk document from the FairWind singleton itself
    auto signalKDocument = fairWind->getSignalKDocument();
    // Set the search path
    QString path = signalKDocument->getSelf() + ".navigation.speedOverGround";

    // Get the position value
    QJsonValue positionValue = signalKDocument->subtree(path);
    // Check if the value is valid
    if (positionValue.isObject()) {
        // Get the speed value
        double speedverGround = positionValue.toObject()["value"].toDouble() * 1.94384;
        // Build the formatted value
        QString sSpeedOverGround;
        sSpeedOverGround = QString{"%1"}.arg(speedverGround, 3, 'f', 1, '0');
        // Set the speed over ground label from the UI to the formatted value
        ui->label_SOG->setText(sSpeedOverGround);
    }
}