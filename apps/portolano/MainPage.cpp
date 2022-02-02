//
// Created by Raffaele Montella on 14/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <FairWindSdk/PageBase.hpp>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>
#include <cmath>

#include "MainPage.hpp"
#include "ui_MainPage.h"
#include "ResultItem.hpp"
#include "Portolano.hpp"

namespace fairwind::apps::portolano {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the signalk document from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get app config
        auto config = fairWindApp->getConfig();
        mConfig = config;

        ui->setupUi((QWidget *)this);

        // Set values from config
        ui->checkBox_Range->setChecked(config.value("userRange").toBool());
        ui->doubleSpinBox_Range->setValue(config.value("range").toDouble());

        // Get the signalk document's string
        QString self = signalKDocument->getSelf();
        // Subscribe to signalk and make sure that navigation infos are updated accordingly
        signalKDocument->subscribe(self + ".navigation.position.value", this, SLOT(fairwind::apps::portolano::updateNavigationPosition));

        connect(ui->comboBox_Search, &QComboBox::editTextChanged,this, &MainPage::onEditTextChanged);
        connect(ui->checkBox_Range, &QCheckBox::stateChanged, this, &MainPage::onBoolChanged);
        connect(ui->doubleSpinBox_Range, &QDoubleSpinBox::textChanged, this, &MainPage::onNumberTextChanged);
        connect(ui->doubleSpinBox_Range, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                &MainPage::onNumberSelectChanged);
    }

    MainPage::~MainPage() {
        delete ui;
    }

    void MainPage::onNumberTextChanged(const QString &text) {
        qDebug() << "MainPage::onNumberTextChanged()";
        mConfig["range"] = text.toDouble();
        getFairWindApp()->setConfig(mConfig);
    }

    void MainPage::onNumberSelectChanged(double value) {
        qDebug() << "MainPage::onNumberSelectChanged()";
        mConfig["range"] = value;
        getFairWindApp()->setConfig(mConfig);
    }

    void MainPage::onBoolChanged(int state) {
        qDebug() << "MainPage::onBoolChanged: state: " << state;
        mConfig["userRange"] = static_cast<bool>(state);
        getFairWindApp()->setConfig(mConfig);
    }

    void MainPage::insertIntoList(QSqlQuery query){
        ui->listWidget_Results->clear();
        while (query.next()) {
            double lat = query.value(3).toDouble();
            double lon = query.value(2).toDouble();

            QJsonObject currentPoint{
                    {"lat", lat},
                    {"lon", lon}
            };

            QString strJsonFeature = query.value(4).toString();
            QJsonDocument doc = QJsonDocument::fromJson(strJsonFeature.toLatin1());

            if (!mConfig.value("userRange").toBool() || (mConfig.value("userRange").toBool() && pointIsInCircle(currentPoint, mPosition))){
                auto widget = new ResultItem(ui->listWidget_Results, doc.object());
                widget->setMinimumWidth(150);

                auto listWidgetItem = new QListWidgetItem();
                listWidgetItem->setSizeHint(widget->sizeHint());

                ui->listWidget_Results->addItem(listWidgetItem);
                ui->listWidget_Results->setItemWidget(listWidgetItem, widget);
            }
        }
    }

    void MainPage::onEditTextChanged(const QString &text) {
        mConfig["userRange"] = false;
        ui->checkBox_Range->setChecked(mConfig.value("userRange").toBool());
        getFairWindApp()->setConfig(mConfig);

        auto *fairWindApp = (Portolano *)getFairWindApp();
        auto db = fairWindApp->getDb();
        if (db->open()) {

            QSqlQuery query(*db);
            QString q = QString("SELECT * FROM ports WHERE name LIKE \"%%1%\" LIMIT 10;").arg(text);
            query.prepare(q);
            query.exec();

            insertIntoList(query);
        }
    }

    void MainPage::updateNavigationPosition(const QJsonObject update) {
        if (mConfig.value("userRange").toBool()){
            qDebug() << "MainPage::updateNavigationPosition";

            mPosition = update["updates"][0]["values"][0]["value"].toObject();

            radius = mConfig.value("range").toDouble() * 1000; // m
            double mult = 1.1;
            auto p1 = calculateDerivedPosition(mPosition, mult * radius, 0);
            auto p2 = calculateDerivedPosition(mPosition, mult *radius, 90);
            auto p3 = calculateDerivedPosition(mPosition, mult *radius, 180);
            auto p4 = calculateDerivedPosition(mPosition, mult *radius, 270);

            auto *fairWindApp = (Portolano *)getFairWindApp();
            auto db = fairWindApp->getDb();
            if (db->open()) {
                QSqlQuery query(*db);
                QString q = QString("SELECT * FROM ports WHERE lat > %1 AND lat < %2 AND lon < %3 AND lon < %4;")
                        .arg(p3.value("lat").toDouble()).arg(p1.value("lat").toDouble())
                        .arg(p2.value("lon").toDouble()).arg(p4.value("lon").toDouble());
                query.prepare(q);
                query.exec();

                insertIntoList(query);
            }
        }
    }

    // Private functions

    double MainPage::getDistanceBetweenTwoPoints(QJsonObject p1, QJsonObject p2){
        double R = 6378137; //m
        double dLat = degreeToRadians(p2.value("lat").toDouble() - p1.value("lat").toDouble());
        double dLon = degreeToRadians(p2.value("lon").toDouble() - p1.value("lon").toDouble());
        double lat1 = degreeToRadians(p1.value("lat").toDouble());
        double lat2 = degreeToRadians(p2.value("lat").toDouble());

        double a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double d = R * c;

        return d;
    }

    bool MainPage::pointIsInCircle(QJsonObject p1, QJsonObject p2) {
        if (getDistanceBetweenTwoPoints(p1, p2) <= radius)
            return true;
        else
            return false;
    }

    double MainPage::degreeToRadians(double degrees){
        return degrees * M_PI / 180;
    }

    double MainPage::radiansToDegree(double radians){
        return (radians * (180 / M_PI));
    }

    QJsonObject MainPage::calculateDerivedPosition(QJsonObject point, double radius, double bearing) {
        double EarthRadius = 6378137; // m

        double latA = degreeToRadians(point["latitude"].toDouble());
        double lonA = degreeToRadians(point["longitude"].toDouble());
        double trueCourse = degreeToRadians(bearing);

        double angularDistance = radius / EarthRadius;

        double lat = asin(sin(latA) * cos(angularDistance) + cos(latA) * sin(angularDistance) * cos(trueCourse));

        double dlon = atan2(sin(trueCourse) * sin(angularDistance) * cos(latA), cos(angularDistance) - sin(latA) * sin(lat));

        double lon = fmod((lonA + dlon + M_PI), (M_PI * 2)) - M_PI;

        lat = radiansToDegree(lat);
        lon = radiansToDegree(lon);

        QJsonObject new_point{
            {"lat", lat},
            {"lon", lon}
        };

        return new_point;
    }
} // fairwind::appls::portolano
