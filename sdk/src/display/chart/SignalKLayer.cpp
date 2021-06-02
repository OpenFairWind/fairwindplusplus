//
// Created by Raffaele Montella on 05/05/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QGVItemSignalK.hpp>
#include <QGVItemAton.hpp>
#include <QGVItemVessel.hpp>
#include <QGVItemShoreBasestations.hpp>
#include <QGVItemDefault.hpp>
#include "SignalKLayer.hpp"

SignalKLayer::SignalKLayer() {
    setName("Signal K Layer");
    setDescription("Generic Layer Holding Signal K elements");
    qDebug() << "SignalKLayer::SignalKLayer() " << getName() << " " << getDescription();
}

SignalKLayer::SignalKLayer(const SignalKLayer &other) {
    qDebug() << "SignalKLayer::SignalKLayer(const SignalKLayer &other)";
}

SignalKLayer::~SignalKLayer() {
    qDebug() << "SignalKLayer::~SignalKLayer()";
}


QImage SignalKLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *SignalKLayer::onLegenda() {
    return nullptr;
}

QWidget *SignalKLayer::onSettings() {
    return nullptr;
}

void SignalKLayer::onInit(QMap<QString, QVariant> params)  {
    qDebug() << "SignalKLayer::onInit(" << params << ")";

    if (params.contains("name")) {
        setName(params["name"].toString());
    }

    if (params.contains("description")) {
        setDescription(params["description"].toString());
    }

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    auto self = signalKDocument->getSelf();

    if (params.contains("fullPath")) {
        QString fullPath=params["fullPath"].toString();
        QJsonValue itemsValue = signalKDocument->subtree(fullPath);
        if (!itemsValue.isNull() && itemsValue.isObject()) {
            QJsonObject itemsObject = itemsValue.toObject();
            for (const auto& uuid: itemsObject.keys()) {
                QString context=fullPath+"."+uuid;
                QGVItemSignalK *itemSignalK = nullptr;
                if ( fullPath.endsWith("atons")) {
                    itemSignalK = new QGVItemAton(context);
                } else if ( fullPath.endsWith("shore.basestations")) {
                    itemSignalK = new QGVItemShoreBasestations(context);
                } else if ( fullPath.endsWith("vessels")) {
                    if (self.indexOf(uuid)<0) {
                        itemSignalK = new QGVItemVessel(context);
                    }
                } else {
                    itemSignalK = new QGVItemDefault(context);
                }
                if (itemSignalK) {
                    addItem(itemSignalK);
                }
            }
        }
    } else {
        addItem(new QGVItemVessel(self));
    }
}

fairwind::layers::IFairWindLayer *SignalKLayer::getNewInstance() {
    return static_cast<IFairWindLayer *>(new SignalKLayer());
}

QString SignalKLayer::getClassName() const {
    return this->metaObject()->className();
}

