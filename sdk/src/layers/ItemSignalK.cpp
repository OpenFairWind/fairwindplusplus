//
// Created by Raffaele Montella on 03/05/21.
//

#include <FairWind.hpp>
#include "FairWindSdk/layers/ItemSignalK.hpp"

ItemSignalK::ItemSignalK(const QString &context):QGVImage() {
    m_context=context;

    // Set flag to ignore scale
    setFlags(QGV::ItemFlag::IgnoreScale);

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the signalkdocument from the FairWind singleton itself
    auto signalKDocument = fairWind->getSignalKDocument();

    // Subscribe to get new position infos and display them on the screen
    signalKDocument->subscribe(
            m_context+".navigation.position",
            this,SLOT(ItemSignalK::update));

    signalKDocument->subscribe(
            m_context+".navigation.courseOverGroundTrue.value",
            this,SLOT(ItemSignalK::update));

    signalKDocument->subscribe(
            m_context+".navigation.speedOverGround.value",
            this,SLOT(ItemSignalK::update));

    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection,Q_ARG(QJsonObject,QJsonObject()));

}

ItemSignalK::~ItemSignalK() {}

/*
 * update
 * Method called to update the signalkitem according to the infos received from the signalk server
 */
void ItemSignalK::update(const QJsonObject update) {
    //qDebug() << "QGVItemSignalK::update:" << update;
    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();
    // Get the signalkdocument from the FairWind singleton itself
    auto signalKDocument = fairWind->getSignalKDocument();
    // Get the navigation infos from the document
    auto coordnate = signalKDocument->getNavigationPosition(m_context);
    double courseOverGroundTrue=signalKDocument->getNavigationCourseOverGroundTrue(m_context);
    double speedOverGround=signalKDocument->getNavigationSpeedOverGround(m_context);

    QMatrix rot;

    // Get and display the correct item with the correct position and rotation
    QImage imageVessel = getImage();
    QSize size=imageVessel.size();
    QPoint anchor=QPoint(size.width()/2,size.height()/2);

    loadImage(imageVessel.transformed(rot.rotate(courseOverGroundTrue * 57.2958)));
    setGeometry(QGV::GeoPos(coordnate.latitude(),coordnate.longitude()), size, anchor);

    //qDebug() << "QGVItemSignalK::update:" << m_context << " geoPos: " << geoPos;
}

QString ItemSignalK::getContext() const {
    return m_context;
}

