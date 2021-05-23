//
// Created by Raffaele Montella on 03/05/21.
//

#include <FairWind.hpp>
#include "QGVItemSignalK.hpp"

QGVItemSignalK::QGVItemSignalK(const QString &context):QGVImage() {
    m_context=context;

    setFlags(QGV::ItemFlag::IgnoreScale);

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    signalKDocument->subscribe(
            m_context+".navigation.position",
            this,SLOT(QGVItemSignalK::update));

    signalKDocument->subscribe(
            m_context+".navigation.courseOverGroundTrue.value",
            this,SLOT(QGVItemSignalK::update));

    signalKDocument->subscribe(
            m_context+".navigation.speedOverGround.value",
            this,SLOT(QGVItemSignalK::update));

    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection,Q_ARG(QJsonObject,QJsonObject()));

}

QGVItemSignalK::~QGVItemSignalK() {

}

void QGVItemSignalK::update(const QJsonObject update) {
    //qDebug() << "QGVItemSignalK::update:" << update;
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    QGV::GeoPos geoPos = signalKDocument->getNavigationPosition(m_context);
    double courseOverGroundTrue=signalKDocument->getNavigationCourseOverGroundTrue(m_context);
    double speedOverGround=signalKDocument->getNavigationSpeedOverGround(m_context);

    QMatrix rot;


    QImage imageVessel = getImage();
    QSize size=imageVessel.size();
    QPoint anchor=QPoint(size.width()/2,size.height()/2);

    loadImage(imageVessel.transformed(rot.rotate(courseOverGroundTrue * 57.2958)));
    setGeometry(geoPos, size, anchor);

    //qDebug() << "QGVItemSignalK::update:" << m_context << " geoPos: " << geoPos;
}

QString QGVItemSignalK::getContext() const {
    return m_context;
}

