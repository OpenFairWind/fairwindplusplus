//
// Created by Raffaele Montella on 01/03/22.
//

#ifndef FAIRWIND_SDK_SIGNALK_WAYPOINT_HPP
#define FAIRWIND_SDK_SIGNALK_WAYPOINT_HPP

#include <QObject>
#include <QGeoCoordinate>
#include <FairWindSDK/FairWindSDK.hpp>

namespace fairwind::signalk {

    class FAIRWINDSDK_LIB_DECL Waypoint : public QJsonObject {
    public:
        Waypoint(const QString &id, const QString &name, const QString &description, const QString &type,
                 const QGeoCoordinate &coordinate);

        QString id();

        QString name();

        QString description();

        QString type();

        QGeoCoordinate coordinate();

    private:

    };
}

#endif //FAIRWIND_SDK_SIGNALK_WAYPOINT_HPP
