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

        // Set initial navigation position
        mPreviousNavigationPosition = QGeoCoordinate();

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the signalk document from the FairWind singleton itself
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
                signalKDocument->subscribe(positionSignalK, this, SLOT(fairwind::apps::portolano::MainPage::updateNavigationPosition));
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
        ui->checkBox_Range->setChecked(config["useRange"].toBool());
        ui->doubleSpinBox_Range->setValue(config["range"].toDouble()/mNm2m);
    }

    MainPage::~MainPage() {
        delete ui;
    }

    void MainPage::onNumberTextChanged(const QString &text) {
        qDebug() << "MainPage::onNumberTextChanged()";
        // Get app config
        auto config = getFairWindApp()->getConfig();
        auto value = text.toDouble() * mNm2m;
        config["range"] = value;
        getFairWindApp()->setConfig(config);
    }

    void MainPage::onNumberSelectChanged(double value) {
        qDebug() << "MainPage::onNumberSelectChanged()";
        // Get app config
        auto config = getFairWindApp()->getConfig();
        value = value * mNm2m;
        config["range"] = value;
        getFairWindApp()->setConfig(config);
    }

    void MainPage::onBoolChanged(int state) {
        qDebug() << "MainPage::onBoolChanged: state: " << state;

        bool useRange = false;
        if (state==1) {
            useRange= true;
        }

        // Get app config
        auto config = getFairWindApp()->getConfig();
        config["useRange"] = useRange;
        getFairWindApp()->setConfig(config);
        ui->listWidget_Results->clear();
        if (useRange) {
            double range = ui->doubleSpinBox_Range->value()/mNm2m;
            spatialQuery(range);
        }
    }

    void MainPage::insertIntoList(QSqlQuery query){
        // Get FairWind instance
        auto fairWind = FairWind::getInstance();

        // Get the Signal K document
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get navigationPosition
        auto navigationPosition = signalKDocument->getNavigationPosition();

        if (navigationPosition.isValid()) {

            double range = ui->doubleSpinBox_Range->value()/mNm2m;

            QMap<double, QJsonObject> map;

            while (query.next()) {
                double lat = query.value(3).toDouble();
                double lon = query.value(2).toDouble();

                QGeoCoordinate portWaypoint(lat, lon);

                if (portWaypoint.isValid()) {

                    double distanceTo = navigationPosition.distanceTo(portWaypoint);

                    if (!ui->checkBox_Range->isChecked() ||
                        (ui->checkBox_Range->isChecked() && distanceTo <= range)) {
                        QString strJsonFeature = query.value(4).toString();
                        QJsonDocument doc = QJsonDocument::fromJson(strJsonFeature.toLatin1());
                        map[distanceTo] = doc.object();
                    }
                }
            }

            if (map.size() > 0) {
                ui->listWidget_Results->clear();

                for (auto item: map) {
                    qDebug() << "MainPage::insertIntoList: item: " << item;
                    auto widget = new ResultItem(ui->listWidget_Results, item);
                    widget->setMinimumWidth(150);

                    auto listWidgetItem = new QListWidgetItem();
                    listWidgetItem->setSizeHint(widget->sizeHint());

                    ui->listWidget_Results->addItem(listWidgetItem);
                    ui->listWidget_Results->setItemWidget(listWidgetItem, widget);
                }
            }
        }
    }

    void MainPage::onEditTextChanged(const QString &text) {
        if (ui->checkBox_Range->isChecked()){
            // Get app config
            auto config = getFairWindApp()->getConfig();
            config["useRange"] = false;
            ui->checkBox_Range->setChecked(false);
            getFairWindApp()->setConfig(config);
        }

        auto *fairWindApp = (Portolano *)getFairWindApp();
        auto db = fairWindApp->getDb();
        if (db->open()) {

            QSqlQuery query(*db);
            query.prepare("SELECT * FROM ports WHERE name LIKE '%"+text+"%' LIMIT 10;");
            query.exec();

            qDebug() << "Text: [" << text << "] Query: " << query.executedQuery();

            insertIntoList(query);
            db->close();
        }
    }

    void MainPage::updateNavigationPosition(const QJsonObject &update) {
        // Get FairWind instance
        auto fairWind = FairWind::getInstance();

        // Get the Signal K document
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get the navigation position
        auto navigationPosition = signalKDocument->getNavigationPosition();

        // Check if the query is driven by range and positions are valid
        if (ui->checkBox_Range->isChecked() && navigationPosition.isValid() && mPreviousNavigationPosition.isValid()){

            // Get the distance range
            double range = ui->doubleSpinBox_Range->value()/mNm2m;

            // Calculate the distance from the previous navigation position
            double distanceFromPreviousNavigationPosition=mPreviousNavigationPosition.distanceTo(navigationPosition);

            qDebug() << "distanceFromPreviousNavigationPosition: " << distanceFromPreviousNavigationPosition << " count: " << ui->listWidget_Results->count();

            // Check if the position changed by the half of the range
            if (distanceFromPreviousNavigationPosition >= range/2){

                spatialQuery(range);
            }
        }
        qDebug() << "prev: " << mPreviousNavigationPosition.toString() << "curr: "  << navigationPosition.toString();
        mPreviousNavigationPosition = navigationPosition;
    }

    void MainPage::onResume() {
        // Get app config
        auto config = getFairWindApp()->getConfig();

        ui->checkBox_Range->setChecked(config["useRange"].toBool());
        ui->doubleSpinBox_Range->setValue(config["range"].toDouble()/mNm2m);
    }

    void MainPage::spatialQuery(double range) {
        // Get FairWind instance
        auto fairWind = FairWind::getInstance();

        // Get the Signal K document
        auto signalKDocument = fairWind->getSignalKDocument();

        // Get the navigation position
        auto navigationPosition = signalKDocument->getNavigationPosition();

        range = 1.1 * range;
        auto pN = navigationPosition.atDistanceAndAzimuth(range,0);
        auto pE = navigationPosition.atDistanceAndAzimuth(range,90);
        auto pS = navigationPosition.atDistanceAndAzimuth(range,180);
        auto pW = navigationPosition.atDistanceAndAzimuth(range,270);


        auto *fairWindApp = (Portolano *)getFairWindApp();
        auto db = fairWindApp->getDb();
        if (db->open()) {
            QSqlQuery query(*db);

            QString q = QString("SELECT * FROM ports WHERE (lat BETWEEN %1 AND %2) AND (lon BETWEEN %3 AND %4);")
                    .arg(pS.latitude()).arg(pN.latitude())
                    .arg(pW.longitude()).arg(pE.longitude());
            query.prepare(q);

            /*
            query.prepare("SELECT * FROM ports WHERE "
                "lon >= " + QString::number(pW.longitude()) + " AND " +
                "lon <= " + QString::number(pE.longitude()) + " AND " +
                "lat >= " + QString::number(pS.latitude()) + " AND " +
                "lat <= " + QString::number(pN.latitude()) + ";");
                */
            query.exec();
            qDebug() << "range (m):" << range << " Query: " << query.executedQuery();
            insertIntoList(query);
            db->close();
        }
    }

} // fairwind::appls::portolano
