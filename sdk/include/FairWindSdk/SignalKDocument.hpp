//
// Created by Raffaele Montella on 18/04/21.
//

#ifndef FAIRWIND_SIGNALKDOCUMENT_HPP
#define FAIRWIND_SIGNALKDOCUMENT_HPP


#include <QJsonDocument>
#include <QGeoView/QGVGlobal.h>

#include "FairWindSDK.hpp"

class FAIRWINDSDK_LIB_DECL SignalKDocument: public QObject {
    Q_OBJECT

public:
    explicit SignalKDocument();
    ~SignalKDocument();

    void save(QString fileName);
    void load(QString fileName);

    void update(QJsonObject &jsonObjectUpdate);
    void insert(const QString& path, const QJsonValue& newValue);
    QJsonObject subtree(const QString& path);

    QString getSelf();
    void setSelf(QString self);
    QString getVersion();

    QGV::GeoPos getNavigationPosition(QString uuid);
    QGV::GeoPos getNavigationPosition();

    double getNavigationCourseOverGroundTrue(QString uuid);
    double getNavigationCourseOverGroundTrue();

signals:
    void updated(const QString path);
    void updatedNavigationPosition();
    void updatedNavigationCourseOverGroundTrue();
    void updatedNavigationSpeedOverGround();

private:
    QJsonDocument m_jsonDocument;

    void modifyJsonValue(QJsonObject& obj, const QString& path, const QJsonValue& newValue);

};


#endif //FAIRWIND_SIGNALKDOCUMENT_HPP
