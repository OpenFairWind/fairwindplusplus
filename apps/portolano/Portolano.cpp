//
// Created by __author__ on 16/07/2021.
//

#include <sqlite3.h>

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QJsonArray>

#include <FairWindSdk/signalk/Document.hpp>
#include <FairWindSdk/signalk/Waypoint.hpp>

#include "Portolano.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::portolano {
    void Portolano::onCreate() {
        FairWindApp::onCreate();

        auto databaseFileName =  getDataPath()+QDir::separator()+"ports.sqlite";
        mDb =  QSqlDatabase::addDatabase("QSQLITE");
        mDb.setDatabaseName(databaseFileName);
        if (mDb.open()) {
            QSqlQuery query(mDb);
            query.exec("PRAGMA case_sensitive_like = false;");
            mDb.close();
        }
    }
    /*
     * Called by the FairWind framework when the app is invoked for the first time
     */
    void Portolano::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }

    void Portolano::onResume() {
        FairWindApp::onResume();
    }

    void Portolano::onPause() {
        FairWindApp::onPause();
    }

    void Portolano::onStop() {
        FairWindApp::onStop();
    }

    void Portolano::onDestroy() {
        if (mDb.isOpen()) {
            mDb.close();
        }
        FairWindApp::onDestroy();
    }

    void Portolano::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool Portolano::onInstall() {
        bool result = false;
        FairWindApp::onInstall();

        auto fairwind = FairWind::getInstance();
        auto signalKDocument = fairwind->getSignalKDocument();

        auto geoJsonFileName = getDataPath()+QDir::separator()+"ports.json";

        auto databaseFileName =  getDataPath()+QDir::separator()+"ports.sqlite";
        auto db =  QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(databaseFileName);

        if (db.open()) {

            QSqlQuery query(db);
            query.exec("PRAGMA case_sensitive_like = false;");

            auto filePorts = QFile(geoJsonFileName);
            if (!filePorts.exists()) {
                auto filePortsFromResources = QFile(":/resources/data/ports.json");
                filePortsFromResources.open(QFile::ReadOnly);
                filePorts.open(QFile::WriteOnly);
                filePorts.write(filePortsFromResources.readAll());
                filePorts.flush();
                filePorts.close();
                filePortsFromResources.close();

                query.exec("DROP TABLE IF EXISTS ports;");
                query.exec(
                        "CREATE TABLE ports (id INTEGER NOT NULL PRIMARY KEY, name TEXT NOT NULL, lon DOUBLE NOT NULL, lat DOUBLE NOT NULL,feature TEXT NOT NULL);");


                auto filePortsFromData = QFile(geoJsonFileName);
                filePortsFromData.open(QFile::ReadOnly);

                auto jsonDocument = QJsonDocument::fromJson(filePortsFromData.readAll());
                QJsonObject jsonObjectPorts = jsonDocument.object();
                if (jsonObjectPorts.contains("features") && jsonObjectPorts["features"].isArray()) {
                    auto jsonArrayFeatures = jsonObjectPorts["features"].toArray();
                    for (auto jsonFeature: jsonArrayFeatures) {
                        if (jsonFeature.isObject()) {
                            auto jsonObjectFeature = jsonFeature.toObject();

                            if (jsonObjectFeature.contains("type") && jsonObjectFeature["type"].isString() &&
                                jsonObjectFeature["type"].toString() == "Feature") {
                                if (jsonObjectFeature.contains("properties") &&
                                    jsonObjectFeature["properties"].isObject()) {
                                    auto jsonObjectProperties = jsonObjectFeature["properties"].toObject();

                                    if (jsonObjectFeature.contains("geometry") &&
                                        jsonObjectFeature["geometry"].isObject()) {
                                        auto jsonObjectGeometry = jsonObjectFeature["geometry"].toObject();

                                        if (jsonObjectGeometry.contains("type") &&
                                            jsonObjectGeometry["type"].isString()) {
                                            auto type = jsonObjectGeometry["type"].toString();

                                            if (type == "Point") {

                                                if (jsonObjectGeometry.contains("coordinates") &&
                                                    jsonObjectGeometry["coordinates"].isArray()) {
                                                    auto jsonArrayCoordinates = jsonObjectGeometry["coordinates"].toArray();


                                                    double lon = jsonArrayCoordinates[0].toDouble();
                                                    double lat = jsonArrayCoordinates[1].toDouble();

                                                    if (jsonObjectProperties.contains("id") &&
                                                        jsonObjectProperties["id"].isDouble()) {

                                                        int id = jsonObjectProperties["id"].toInt();

                                                        if (jsonObjectProperties.contains("name") &&
                                                            jsonObjectProperties["name"].isString()) {
                                                            auto name = jsonObjectProperties["name"].toString();

                                                            QString description="";
                                                            if (jsonObjectProperties.contains("description") &&
                                                                jsonObjectProperties["description"].isString()) {
                                                                description = jsonObjectProperties["description"].toString();
                                                            }

                                                            QJsonDocument doc(jsonObjectFeature);
                                                            QString strJsonFeature(doc.toJson(QJsonDocument::Compact));

                                                            QString q = QString(
                                                                    "INSERT INTO ports(id, name, lon, lat, feature) VALUES (%1, '%2', %3, %4, '%5');")
                                                                    .arg(id)
                                                                    .arg(name)
                                                                    .arg(lon)
                                                                    .arg(lat)
                                                                    .arg(strJsonFeature);
                                                            qDebug() << "q:" << q;
                                                            query.prepare(q);
                                                            if (!query.exec()) {
                                                                qDebug() << "Query failed: " << query.lastError();
                                                                qDebug() << "            : " << query.lastQuery();
                                                            }

                                                            signalk::Waypoint waypoint("WPT_"+QString::number(id),name,description,"harbour", QGeoCoordinate(lat,lon, 0));
                                                            signalKDocument->set("resources.waypoints",waypoint);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    result = true;
                }
            }
        }

        return result;
    }

    bool Portolano::onUninstall() {
        bool result = false;

        FairWindApp::onUninstall();

        return result;
    }

    QSqlDatabase *Portolano::getDb() {
        return &mDb;
    }

}
