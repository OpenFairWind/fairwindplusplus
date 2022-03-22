//
// Created by Raffaele Montella on 12/04/21.
//

#include <QTimer>

#include <FairWindSdk/FairWind.hpp>
#include <QAbstractButton>
#include <FairWindSdk/FairWindApp.hpp>
#include <QGeoCoordinate>

#include "TopBar.hpp"
#include "ui_TopBar.h"

namespace fairwind::ui::topbar {
/*
 * TopBar
 * Public Constructor - This presents some useful infos at the top of the screen
 */
    TopBar::TopBar(QWidget *parent) :
            QWidget(parent),
            ui(new Ui::TopBar) {
        // Setup the UI
        ui->setupUi(parent);

        ui->toolButton_UL->setIcon(QPixmap::fromImage(QImage(":/resources/images/icons/fairwind_icon.png")));
        ui->toolButton_UL->setIconSize(QSize(32, 32));

        ui->toolButton_UR->setIcon(QPixmap::fromImage(QImage(":/resources/images/icons/apps_icon.png")));
        ui->toolButton_UR->setIconSize(QSize(32, 32));

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

        // Get the configuration object
        auto config = fairWind->getConfig();


        // Check if the configuration object has the key Options
        if (config.contains("Options") && config["Options"].isObject()) {

            // Get the Options object
            auto jsonObjectOptions = config["Options"].toObject();

            // Check if the Options object has tHe Position key and if it is a string
            if (jsonObjectOptions.contains("Position") && jsonObjectOptions["Position"].isString()) {

                // Get the position SignalK key
                auto positionSignalK = jsonObjectOptions["Position"].toString();

                // Subscribe to signalk and make sure that navigation infos are updated accordingly
                signalKDocument->subscribe(positionSignalK, this, SLOT(fairwind::ui::topbar::TopBar::updateNavigationPosition));
            }

            // Check if the Options object has tHe Heading key and if it is a string
            if (jsonObjectOptions.contains("Heading") && jsonObjectOptions["Heading"].isString()) {

                // Get the heading SignalK key
                auto headingSignalK = jsonObjectOptions["Heading"].toString();

                // Subscribe to signalk and make sure that navigation infos are updated accordingly
                signalKDocument->subscribe(headingSignalK, this,
                                           SLOT(fairwind::ui::topbar::TopBar::updateNavigationCourseOverGroundTrue));
            }

            // Check if the Options object has tHe Speed key and if it is a string
            if (jsonObjectOptions.contains("Speed") && jsonObjectOptions["Speed"].isString()) {

                // Get the speed SignalK key
                auto speedSignalK = jsonObjectOptions["Speed"].toString();

                // Subscribe to signalk and make sure that navigation infos are updated accordingly
                signalKDocument->subscribe(speedSignalK, this,
                                           SLOT(fairwind::ui::topbar::TopBar::updateNavigationSpeedOverGround));
            }
        }
    }

/*
 * updateTime
 * Method called to update the current datetime
 */
    void TopBar::updateTime() {
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
    void TopBar::toolbuttonUL_clicked() {
        // Emit the signal to tell the MainWindow to update the UI and show the settings screen
        emit clickedToolbuttonUL();
    }

/*
 * apps_clicked
 * Method called when the user wants to view the apps screen
 */
    void TopBar::toolbuttonUR_clicked() {
        // Emit the signal to tell the MainWindow to update the UI and show the apps screen
        emit clickedToolbuttonUR();
    }

/*
 * ~TopBar
 * TopBar's destructor
 */
    TopBar::~TopBar() {
        delete ui;
    }

/*
 * updateNavigationPosition
 * Method called in accordance to signalk to update the navigation position
 */
    void TopBar::updateNavigationPosition(const QJsonObject &update) {
        //qDebug() << "TopBar::updateNavigationPosition:" << update;

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the signalk document from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();

        // Show the coordinates
        ui->label_Position_value->setText(
                signalKDocument->getNavigationPosition().toString(
                        QGeoCoordinate::DegreesMinutesSecondsWithHemisphere
                        )
                        );

    }

/*
 * updateNavigationCourseOverGroundTrue
 * Method called in accordance to signalk to update the navigation course over ground
 */
    void TopBar::updateNavigationCourseOverGroundTrue(const QJsonObject &update) {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the signalk document from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get the Course over ground
        double courseOverGroundTrue = signalKDocument->getNavigationCourseOverGroundTrue() * 57.2958;

        // Build the formatted value
        QString sCourseOverGroundTrue = QString{"%1"}.arg(courseOverGroundTrue, 3, 'f', 0, '0');

        // Set the course over ground label from the UI to the formatted value
        ui->label_COG->setText(sCourseOverGroundTrue);

    }

/*
 * updateNavigationSpeedOverGround
 * Method called in accordance to signalk to update the navigation speed over ground
 */
    void TopBar::updateNavigationSpeedOverGround(const QJsonObject &update) {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the signalk document from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get the speed value
        double speedverGround = signalKDocument->getNavigationSpeedOverGround() * 1.94384;
        // Build the formatted value
        QString sSpeedOverGround = QString{"%1"}.arg(speedverGround, 3, 'f', 1, '0');

        // Set the speed over ground label from the UI to the formatted value
        ui->label_SOG->setText(sSpeedOverGround);

    }

    void TopBar::setFairWindApp(AppItem *appItem) {
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
}