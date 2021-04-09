//
// Created by Raffaele Montella on 08/04/21.
//

#include "include/FairWindAppBase.hpp"

QString fairwind::FairWindAppBase::getId() const {
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

QString fairwind::FairWindAppBase::getName() const {
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

QString fairwind::FairWindAppBase::getDesc() const {
    if (m_metaData.find("Description") == m_metaData.end()) {
        return "";
    }
    return m_metaData["Description"].toString();
}


void fairwind::FairWindAppBase::init(QJsonObject *metaData) {
    m_metaData = QJsonObject(*metaData);
}
