//
// Created by Raffaele Montella on 08/04/21.
//

#include "include/FairWindExtension.hpp"

QString fairwind::extensions::FairWindExtension::getId() const {
    if (m_metaData.find("FairWind") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"].toObject().find("Extension") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"]["Extension"].toObject().find("Id") == m_metaData.end()) {
        return "";
    }

    return m_metaData["FairWind"]["Extension"]["Id"].toString();
}

QString fairwind::extensions::FairWindExtension::getName() const {
    if (m_metaData.find("FairWind") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["FairWind"]["Extension"].toObject().find("Name") == m_metaData.end()) {
        if (m_metaData.find("Name") == m_metaData.end()) {
            return "";
        }
        return m_metaData["FairWind"]["Extension"]["Name"].toString();
    }

    if (m_metaData.find("Name") == m_metaData.end()) {
        return "";
    }

    return m_metaData["Name"].toString();
}

QString fairwind::extensions::FairWindExtension::getDesc() const {
    if (m_metaData.find("Description") == m_metaData.end()) {
        return "";
    }
    return m_metaData["Description"].toString();
}


void fairwind::extensions::FairWindExtension::init(QJsonObject *metaData) {
    m_metaData = QJsonObject(*metaData);
}
