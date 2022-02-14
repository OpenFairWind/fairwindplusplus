//
// Created by Raffaele Montella on 12/04/21.
//

#include <QTimer>

#include <FairWindSdk/FairWind.hpp>
#include <QAbstractButton>
#include <FairWindSdk/FairWindApp.hpp>
#include <QGeoLocation>
#include <QGeoCoordinate>

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

    ui->toolButton_UL->setIcon(QPixmap::fromImage(QImage(":/resources/images/icons/fairwind_icon.png")));
    ui->toolButton_UL->setIconSize(QSize(32,32));

    ui->toolButton_UR->setIcon(QPixmap::fromImage(QImage(":/resources/images/icons/apps_icon.png")));
    ui->toolButton_UR->setIconSize(QSize(32,32));

    // emit a signal when the Apps tool button from the UI is clicked
    connect(ui->toolButton_UL, &QToolButton::released, this, &TopBar::toolbuttonUL_clicked);
    // emit a signal when the Settings tool button from the UI is clicked
    connect(ui->toolButton_UR, &QToolButton::released, this, &TopBar::toolbuttonUR_clicked);

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

    // Get the signalk document's string
    QString self = signalKDocument->getSelf();

    // Subscribe to signalk and make sure that navigation infos are updated accordingly
    signalKDocument->subscribe(self + ".navigation.position.value", this,
                               SLOT(TopBar::updateNavigationPosition));

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
 * settings_clicked
 * Method called when the user wants to view the settings screen
 */
void fairwind::ui::topbar::TopBar::toolbuttonUL_clicked() {
    // Emit the signal to tell the MainWindow to update the UI and show the settings screen
    emit clickedToolbuttonUL();
}

/*
 * apps_clicked
 * Method called when the user wants to view the apps screen
 */
void fairwind::ui::topbar::TopBar::toolbuttonUR_clicked() {
    // Emit the signal to tell the MainWindow to update the UI and show the apps screen
    emit clickedToolbuttonUR();
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

        QGeoCoordinate pos(latitude,longitude);
        ui->label_Position_value->setText(pos.toString(QGeoCoordinate::DegreesMinutesSecondsWithHemisphere));

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

void fairwind::ui::topbar::TopBar::setFairWindApp(AppItem *appItem) {
    mAppItem = appItem;
    if (mAppItem) {
        ui->toolButton_UR->setIcon(QPixmap::fromImage(mAppItem->getIcon()));
        ui->toolButton_UR->setIconSize(QSize(32, 32));
        ui->label_ApplicationName->setText(mAppItem->getName());
        ui->label_ApplicationName->setToolTip(mAppItem->getDesc());
    } else {
        ui->toolButton_UR->setIcon(QPixmap::fromImage(QImage(":resources/images/icons/apps_icon.png")));
        ui->toolButton_UR->setIconSize(QSize(32, 32));
        ui->label_ApplicationName->setText("");
        ui->label_ApplicationName->setToolTip("");
    }
}
