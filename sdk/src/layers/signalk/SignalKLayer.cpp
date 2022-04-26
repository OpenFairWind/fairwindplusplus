//
// Created by Raffaele Montella on 05/05/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/layers/signalk/ItemSignalK.hpp>
#include <FairWindSdk/layers/signalk/ItemAton.hpp>
#include <FairWindSdk/layers/signalk/ItemVessel.hpp>
#include <FairWindSdk/layers/signalk/ItemShoreBasestations.hpp>
#include <FairWindSdk/layers/signalk/ItemDefault.hpp>
#include "FairWindSdk/layers/signalk/SignalKLayer.hpp"

namespace fairwind::layers::signalk {
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
        return QImage(":resources/images/icons/layer_signalk_icon.png");
    }

    QWidget *SignalKLayer::onLegenda() {
        return nullptr;
    }

    QWidget *SignalKLayer::onSettings() {
        return nullptr;
    }

    void SignalKLayer::onInit(QMap<QString, QVariant> params) {
        qDebug() << "SignalKLayer::onInit(" << params << ")";

        // Set the layer's name from the parameters
        if (params.contains("name")) {
            setName(params["name"].toString());
        }

        // Set the layer's description from the parameters
        if (params.contains("description")) {
            setDescription(params["description"].toString());
        }

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the signalkdocument from the FairWind singleton itself
        auto signalKDocument = fairWind->getSignalKDocument();
        // Get the self key from the document
        auto self = signalKDocument->getSelf();

        // Check if a fullPath has been provided
        if (params.contains("fullPath")) {
            // Get the path
            QString fullPath = params["fullPath"].toString();
            // Get the items to display on the layer
            QJsonValue itemsValue = signalKDocument->subtree(fullPath);
            // Check if there is at least one valid item
            if (!itemsValue.isNull() && itemsValue.isObject()) {
                QJsonObject itemsObject = itemsValue.toObject();
                for (const auto &uuid: itemsObject.keys()) {
                    QString context = fullPath + "." + uuid;
                    ItemSignalK *itemSignalK = nullptr;
                    if (fullPath.endsWith("atons")) {
                        itemSignalK = new ItemAton(context);
                    } else if (fullPath.endsWith("shore.basestations")) {
                        itemSignalK = new ItemShoreBasestations(context);
                    } else if (fullPath.endsWith("vessels")) {
                        if (self.indexOf(uuid) < 0) {
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
            // Directly add the vessel to the layer
            addItem(new ItemVessel(self));
        }
    }

    ILayer *SignalKLayer::getNewInstance() {
        return static_cast<ILayer *>(new SignalKLayer());
    }

    QString SignalKLayer::getClassName() const {
        return this->metaObject()->className();
    }
}