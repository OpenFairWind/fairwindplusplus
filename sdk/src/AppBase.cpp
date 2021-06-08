//
// Created by Raffaele Montella on 08/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QJsonArray>
#include "include/FairWindSdk/AppBase.hpp"

QString fairwind::AppBase::getId() const {
    if (m_metaData.find("FairWind") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"].toObject().find("App") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"]["App"].toObject().find("Id") == m_metaData.end()) {
        return "";
    }

    return m_metaData["FairWind"]["App"]["Id"].toString();
}

QJsonObject fairwind::AppBase::getConfig() {
    QJsonObject result;
    auto fairWind=fairwind::FairWind::getInstance();
    if (fairWind) {
        auto config = fairWind->getConfig();
        if (config.contains("Extensions") && config["Extensions"].isObject()) {
            auto extensions = config["Extensions"].toObject();
            if (extensions.contains("Apps") && extensions["Apps"].isArray()) {
                QJsonArray apps=extensions["Apps"].toArray();
                for (auto app:apps) {
                    if (app.isObject()) {
                        auto appExtensionSection=app.toObject();
                        if (appExtensionSection.contains("Id") && appExtensionSection["Id"].isString() && appExtensionSection["Id"].toString() == getId()) {
                            if (appExtensionSection.contains("Config") && appExtensionSection["Config"].isObject()) {
                                result=appExtensionSection["Config"].toObject();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

QString fairwind::AppBase::getName() const {
    if (m_metaData.find("FairWind") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"]["App"].toObject().find("Name") == m_metaData.end()) {
        if (m_metaData.find("Name") == m_metaData.end()) {
            return "";
        }
        return m_metaData["FairWind"]["App"]["Name"].toString();
    }

    if (m_metaData.find("Name") == m_metaData.end()) {
        return "";
    }

    return m_metaData["Name"].toString();
}

QString fairwind::AppBase::getDesc() const {
    if (m_metaData.find("Description") == m_metaData.end()) {
        return "";
    }
    return m_metaData["Description"].toString();
}


void fairwind::AppBase::onInit(QJsonObject *metaData) {
    m_metaData = QJsonObject(*metaData);
}
