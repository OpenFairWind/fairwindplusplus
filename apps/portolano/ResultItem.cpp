//
// Created by Raffaele Montella on 31/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResultItem.h" resolved

#include <QJsonArray>
#include <QDir>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/SignalKDocument.hpp>
#include <QGeoCoordinate>
#include "ResultItem.hpp"
#include "ui_ResultItem.h"

namespace fairwind::apps::portolano {
    ResultItem::ResultItem(QWidget *parent, QJsonObject feature) :
            QWidget(parent), ui(new Ui::ResultItem), mFeature(feature) {
        ui->setupUi(this);

        // qDebug() << "fairwind::apps::portolano: " << feature;

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the signalk document from the FairWind singleton itslef
        auto signalKDocument = fairWind->getSignalKDocument();

        if (mFeature.contains("geometry") &&
                mFeature["geometry"].isObject()) {
            auto jsonObjectGeometry = mFeature["geometry"].toObject();

            if (jsonObjectGeometry.contains("type") &&
                jsonObjectGeometry["type"].isString()) {
                auto type = jsonObjectGeometry["type"].toString();

                if (type == "Point") {

                    if (jsonObjectGeometry.contains("coordinates") &&
                        jsonObjectGeometry["coordinates"].isArray()) {
                        auto jsonArrayCoordinates = jsonObjectGeometry["coordinates"].toArray();


                        double lon = jsonArrayCoordinates[0].toDouble();
                        double lat = jsonArrayCoordinates[1].toDouble();
                        mPosition = QGeoCoordinate(lat,lon);
                        ui->label_Position->setText(mPosition.toString(QGeoCoordinate::DegreesMinutesSecondsWithHemisphere));
                    }
                }
            }
        }
        if (mFeature.contains("properties") && mFeature["properties"].isObject()) {
            auto jsonObjectProperties = mFeature["properties"].toObject();

            if (jsonObjectProperties.contains("mapId") && jsonObjectProperties["mapId"].isString()) {
                auto mapId = jsonObjectProperties["mapId"].toString();
                QStringList list = mapId.split("_");
                QString iconPath = ":/resources/images/ports/"+list[0]+QDir::separator()+mapId+".jpg";
                QFile iconFile(iconPath);
                if(!iconFile.exists()){
                    ui->label_Icon->setPixmap(QPixmap::fromImage(QImage(":/resources/images/ports/no_icon.png")));
                }else{
                    // qDebug() << "iconPath: " << iconPath;
                    ui->label_Icon->setPixmap(QPixmap::fromImage(QImage(iconPath)));
                }
                iconFile.close();
            }

            if (jsonObjectProperties.contains("name") && jsonObjectProperties["name"].isString()) {
                auto name = jsonObjectProperties["name"].toString();
                ui->label_Name->setText(name);
            }
            if (jsonObjectProperties.contains("description") && jsonObjectProperties["description"].isString()) {
                auto description = jsonObjectProperties["description"].toString();
                ui->textEdit_Description->setText(description);
            }

            if (jsonObjectProperties.contains("contacts")) {

                if (jsonObjectProperties["contacts"].isString()) {
                    auto contact = jsonObjectProperties["contacts"].toString();
                    ui->listWidget_Contacts->addItem(contact);

                } else if (jsonObjectProperties["contacts"].isArray()) {
                    auto contacts = jsonObjectProperties["contacts"].toArray();
                    for (auto contact: contacts) {
                        if (contact.isString()) {
                            ui->listWidget_Contacts->addItem(contact.toString());
                        }
                    }
                }
            }

            if (jsonObjectProperties.contains("seaFloor") && jsonObjectProperties["seaFloor"].isObject()) {
                auto jsonObjectSeaFloor = jsonObjectProperties["seaFloor"].toObject();
                if (jsonObjectSeaFloor.contains("minDepth") && jsonObjectSeaFloor["minDepth"].isDouble()) {
                    ui->label_Seafloor_Min_value->setText(QString::number(jsonObjectSeaFloor["minDepth"].toDouble()));
                } else {
                    ui->label_Seafloor_Min_value->setVisible(false);
                    ui->label_Seafloor_Min->setVisible(false);
                }

                if (jsonObjectSeaFloor.contains("maxDepth") && jsonObjectSeaFloor["maxDepth"].isDouble()) {
                    ui->label_Seafloor_Max_value->setText(QString::number(jsonObjectSeaFloor["maxDepth"].toDouble()));
                } else {
                    ui->label_Seafloor_Max_value->setVisible(false);
                    ui->label_Seafloor_Max->setVisible(false);
                }


                if (jsonObjectSeaFloor.contains("type") && jsonObjectSeaFloor["type"].isArray()) {
                    auto jsonArraySeaFloorType = jsonObjectSeaFloor["type"].toArray();
                    for (auto item:jsonArraySeaFloorType) {
                        if (item.isString()) {
                            auto seafloorType = item.toString();
                            QString seaFloorIconName = ":/resources/images/icons/seafloor/";
                            if (seafloorType == "sand") {
                                seaFloorIconName+="sand_icon.png";
                            } else if (seafloorType == "mud") {
                                seaFloorIconName+="mud_icon.png";
                            } else if (seafloorType == "rock") {
                                seaFloorIconName+="rocks_icon.png";
                            } else if (seafloorType == "algae") {
                                seaFloorIconName+="algae_icon.png";
                            } else if (seafloorType == "coral") {
                                seaFloorIconName+="corals_icon.png";
                            } if (seafloorType == "good") {
                                seaFloorIconName+="good_icon.png";
                            } if (seafloorType == "bad") {
                                seaFloorIconName+="bad_icon.png";
                            }

                            auto seaFloorTypeButton = new QToolButton();
                            seaFloorTypeButton->setIcon(QIcon(QPixmap::fromImage(QImage(seaFloorIconName))));
                            seaFloorTypeButton->setIconSize(QSize(32,32));
                            seaFloorTypeButton->setToolTip(seafloorType);
                            ui->horizontalLayout_Seafloor->addWidget(seaFloorTypeButton);
                        }
                    }
                }

            } else {
                ui->groupBox_Seafloor->setVisible(false);
            }

            // Get the signalk document's string
            QString self = signalKDocument->getSelf();

            // Subscribe to signalk and make sure that navigation infos are updated accordingly
            signalKDocument->subscribe(self + ".navigation.position.value", this, SLOT(ResultItem::updateNavigationPosition));
            signalKDocument->subscribe(self + ".navigation.speedOverGround.value", this,
                                       SLOT(TopBar::updateNavigationSpeedOverGround));
        }
    }

    ResultItem::~ResultItem() {
        delete ui;
    }

/*
 * updateNavigationCourseOverGroundTrue
 * Method called in accordance to signalk to update the navigation course over ground
 */
    void ResultItem::updateNavigationPosition(const QJsonObject update) {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the signalk document from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();

        // Set the search path
        QString path = signalKDocument->getSelf() + ".navigation.position.value";

        // Get the position value
        QJsonValue positionValue = signalKDocument->subtree(path);

        // Check if the value is valid
        if (positionValue.isObject()) {

            // Get latitude
            double latitude = positionValue.toObject()["latitude"].toDouble();

            // Get longitude
            double longitude = positionValue.toObject()["longitude"].toDouble();

            QGeoCoordinate vesselPosition = QGeoCoordinate(latitude,longitude);

            if (vesselPosition.isValid() && mPosition.isValid()) {

                ui->label_DTG_value->setText(
                    QString{"%1"}.arg(vesselPosition.distanceTo(mPosition)/1852, 3, 'f', 1, '0')
                );

                ui->label_BTG_value->setText(
                        QString{"%1"}.arg(vesselPosition.azimuthTo(mPosition), 3, 'f', 0, '0')
                        );
            } else {
                ui->label_DTG_value->setText("n/a");
                ui->label_BTG_value->setText("n/a");
            }

        }
    }

    /*
 * updateNavigationSpeedOverGround
 * Method called in accordance to signalk to update the navigation speed over ground
 */
    void ResultItem::updateNavigationSpeedOverGround(const QJsonObject update) {
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

            double distanceTo = ui->label_DTG_value->text().toDouble();
            double timeTo = 3600*distanceTo/speedverGround;

            int hours = timeTo / 3600;
            int minutes = (timeTo-hours)/60;
            int seconds = ((timeTo-hours)/60.0 - minutes)/60;
            auto ttg = QTime(hours,minutes,seconds);

            auto eta = QDateTime::currentDateTime();
            eta = eta.addSecs(timeTo);

            ui->label_TTG_value->setText(ttg.toString());
            ui->label_ETA_value->setText(eta.toString());
        }
    }
} // fairwind::apps::portolano
