//
// Created by Raffaele Montella on 05/05/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/layers/ItemSignalK.hpp>
#include <FairWindSdk/layers/ItemAton.hpp>
#include <FairWindSdk/layers/ItemVessel.hpp>
#include <FairWindSdk/layers/ItemShoreBasestations.hpp>
#include <FairWindSdk/layers/ItemDefault.hpp>
#include "FairWindSdk/layers/SignalKLayer.hpp"

fairwind::layers::SignalKLayer::SignalKLayer() {
    setName("Signal K Layer");
    setDescription("Generic Layer Holding Signal K elements");
    qDebug() << "SignalKLayer::SignalKLayer() " << getName() << " " << getDescription();
}

fairwind::layers::SignalKLayer::SignalKLayer(const SignalKLayer &other) {
    qDebug() << "SignalKLayer::SignalKLayer(const SignalKLayer &other)";
}

fairwind::layers::SignalKLayer::~SignalKLayer() {
    qDebug() << "SignalKLayer::~SignalKLayer()";
}


QImage fairwind::layers::SignalKLayer::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::layers::SignalKLayer::onLegenda() {
    return nullptr;
}

QWidget *fairwind::layers::SignalKLayer::onSettings() {
    return nullptr;
}

void fairwind::layers::SignalKLayer::onInit(QMap<QString, QVariant> params)  {
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
                ItemSignalK *itemSignalK = nullptr;
                if ( fullPath.endsWith("atons")) {
                    itemSignalK = new ItemAton(context);
                } else if ( fullPath.endsWith("shore.basestations")) {
                    itemSignalK = new ItemShoreBasestations(context);
                } else if ( fullPath.endsWith("vessels")) {
                    if (self.indexOf(uuid)<0) {
                        itemSignalK = new ItemVessel(context);
                    }
                } else {
                    itemSignalK = new ItemDefault(context);
                }
                if (itemSignalK) {
                    addItem(itemSignalK);
                }
            }
        }
    } else {
        addItem(new ItemVessel(self));
    }
}

fairwind::layers::ILayer *fairwind::layers::SignalKLayer::getNewInstance() {
    return static_cast<ILayer *>(new fairwind::layers::SignalKLayer());
}

QString fairwind::layers::SignalKLayer::getClassName() const {
    return this->metaObject()->className();
}

