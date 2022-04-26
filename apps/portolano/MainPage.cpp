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
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        // Set the initial latitude
        mOldPosition.setLatitude(0.0);

        // SEt the initial longitude
        mOldPosition.setLongitude(0.0);

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

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

                // Get the signalk document from the FairWind singleton itself
                auto signalKDocument = fairWind->getSignalKDocument();

                // Subscribe to signalk and make sure that navigation infos are updated accordingly
                signalKDocument->subscribe(positionSignalK, this,
                                           SLOT(MainPage::updateNavigationPosition));
            }
        }
        connect(ui->comboBox_Search, &QComboBox::editTextChanged,this, &MainPage::onEditTextChanged);
        connect(ui->checkBox_Range, &QCheckBox::stateChanged, this, &MainPage::onBoolChanged);
        connect(ui->doubleSpinBox_Range, &QDoubleSpinBox::textChanged, this, &MainPage::onNumberTextChanged);
        connect(ui->doubleSpinBox_Range, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                &MainPage::onNumberSelectChanged);
    }

    void MainPage::onAdded() {



        // Get app config
        auto config = getFairWindApp()->getConfig();

        // Set values from config
        ui->checkBox_Range->setChecked(config["userRange"].toBool());
        ui->doubleSpinBox_Range->setValue(config["range"].toDouble());
    }

    MainPage::~MainPage() {
        delete ui;
    }

    void MainPage::onNumberTextChanged(const QString &text) {
        qDebug() << "MainPage::onNumberTextChanged()";
        // Get app config
        auto config = getFairWindApp()->getConfig();
        config["range"] = text.toDouble();
        getFairWindApp()->setConfig(config);

        mOldPosition.setLatitude(0.0);
        mOldPosition.setLongitude(0.0);
    }

    void MainPage::onNumberSelectChanged(double value) {
        qDebug() << "MainPage::onNumberSelectChanged()";
        // Get app config
        auto config = getFairWindApp()->getConfig();
        config["range"] = value;
        getFairWindApp()->setConfig(config);

        mOldPosition.setLatitude(0.0);
        mOldPosition.setLongitude(0.0);
    }

    void MainPage::onBoolChanged(int state) {
        qDebug() << "MainPage::onBoolChanged: state: " << state;
        // Get app config
        auto config = getFairWindApp()->getConfig();
        config["userRange"] = static_cast<bool>(state);
        getFairWindApp()->setConfig(config);
    }

    void MainPage::insertIntoList(QSqlQuery query){
        ui->listWidget_Results->clear();

        QMap<double, QJsonObject> map;

        while (query.next()) {
            double lat = query.value(3).toDouble();
            double lon = query.value(2).toDouble();

            QGeoCoordinate currentPoint(lat, lon);

            QString strJsonFeature = query.value(4).toString();
            QJsonDocument doc = QJsonDocument::fromJson(strJsonFeature.toLatin1());

            double dist = getDistanceBetweenTwoPoints(currentPoint, mPosition);

            if (!ui->checkBox_Range->isChecked() || (ui->checkBox_Range->isChecked() && dist <= radius)){
                auto item = doc.object();
                if (item.contains("properties") && item["properties"].isObject()){
                    auto tmp = item["properties"].toObject();
                    tmp["dist"] = dist;
                    item["properties"] = tmp;
                }
                map[dist] = item;
            }
        }

        for (auto item: map) {
            // qDebug() << "MainPage::insertIntoList: item: " << item;
            auto widget = new ResultItem(ui->listWidget_Results, item);
            widget->setMinimumWidth(150);

            auto listWidgetItem = new QListWidgetItem();
            listWidgetItem->setSizeHint(widget->sizeHint());

            ui->listWidget_Results->addItem(listWidgetItem);
            ui->listWidget_Results->setItemWidget(listWidgetItem, widget);
        }
    }

    void MainPage::onEditTextChanged(const QString &text) {
        if (ui->checkBox_Range->isChecked()){
            // Get app config
            auto config = getFairWindApp()->getConfig();
            config["userRange"] = false;
            ui->checkBox_Range->setChecked(false);
            getFairWindApp()->setConfig(config);
        }

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
        if (ui->checkBox_Range->isChecked()){
            mPosition.setLatitude(update["updates"][0]["values"][0]["value"].toObject()["latitude"].toDouble());
            mPosition.setLongitude(update["updates"][0]["values"][0]["value"].toObject()["longitude"].toDouble());

            if (getDistanceBetweenTwoPoints(mOldPosition, mPosition) >= (ui->doubleSpinBox_Range->value()) * mNm2m /2){
                radius = ui->doubleSpinBox_Range->value() * mNm2m; // m
                double mult = 1.1;
                auto p1 = calculateDerivedPosition(mPosition, mult * radius, 0);
                auto p2 = calculateDerivedPosition(mPosition, mult *radius, 90);
                auto p3 = calculateDerivedPosition(mPosition, mult *radius, 180);
                auto p4 = calculateDerivedPosition(mPosition, mult *radius, 270);

                auto *fairWindApp = (Portolano *)getFairWindApp();
                auto db = fairWindApp->getDb();
                if (db->open()) {
                    QSqlQuery query(*db);
                    QString q = QString("SELECT * FROM ports WHERE lat > %1 AND lat < %2 AND lon < %3 AND lon > %4;")
                            .arg(p3.latitude()).arg(p1.latitude())
                            .arg(p2.longitude()).arg(p4.longitude());
                    query.prepare(q);
                    query.exec();

                    insertIntoList(query);
                }

                mOldPosition = mPosition;
            }
        }
    }

    // Private functions

    double MainPage::getDistanceBetweenTwoPoints(QGeoCoordinate p1, QGeoCoordinate p2){
        double R = 6378137; //m
        double dLat = degreeToRadians(p2.latitude() - p1.latitude());
        double dLon = degreeToRadians(p2.longitude() - p1.longitude());
        double lat1 = degreeToRadians(p1.latitude());
        double lat2 = degreeToRadians(p2.latitude());

        double a = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double d = R * c;

        return d;
    }

    bool MainPage::pointIsInCircle(QGeoCoordinate p1, QGeoCoordinate p2) {
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

    QGeoCoordinate MainPage::calculateDerivedPosition(QGeoCoordinate point, double radius, double bearing) {
        double EarthRadius = 6378137; // m

        double latA = degreeToRadians(point.latitude());
        double lonA = degreeToRadians(point.longitude());
        double trueCourse = degreeToRadians(bearing);

        double angularDistance = radius / EarthRadius;

        double lat = asin(sin(latA) * cos(angularDistance) + cos(latA) * sin(angularDistance) * cos(trueCourse));

        double dlon = atan2(sin(trueCourse) * sin(angularDistance) * cos(latA), cos(angularDistance) - sin(latA) * sin(lat));

        double lon = fmod((lonA + dlon + M_PI), (M_PI * 2)) - M_PI;

        lat = radiansToDegree(lat);
        lon = radiansToDegree(lon);

        QGeoCoordinate new_point(lat, lon);

        return new_point;
    }

    void MainPage::onResume() {
        // Get app config
        auto config = getFairWindApp()->getConfig();

        ui->checkBox_Range->setChecked(config["userRange"].toBool());
        ui->doubleSpinBox_Range->setValue(config["range"].toDouble());
    }
} // fairwind::appls::portolano
