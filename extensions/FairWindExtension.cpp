//
// Created by Raffaele Montella on 03/04/21.
//

#include "../include/FairWindExtension.hpp"

#include <utility>

QString fairwind::extensions::FairWindExtension::getId() const{
    if (m_metaData.find("Extension") == m_metaData.end()) {
        return "";
    }
    if (m_metaData["Extension"].toObject().find("Id") == m_metaData.end()) {
        return "";
    }

    return m_metaData["Extension"]["Id"].toString();
}

QString fairwind::extensions::FairWindExtension::getName() const{

    if (m_metaData["Extension"].toObject().find("Name") == m_metaData.end()) {
        if (m_metaData.find("Name") == m_metaData.end()) {
            return "";
        }
        return m_metaData["Name"].toString();
    }

    return m_metaData["Extension"]["Name"].toString();
}

QString fairwind::extensions::FairWindExtension::getDesc() const {
    if (m_metaData.find("Description") == m_metaData.end()) {
        return "";
    }
    return m_metaData["Description"].toString();
}

void fairwind::extensions::FairWindExtension::setMetaData(QJsonObject &metaData)  {
    qDebug() << "fairwind::extensions::FairWindExtension::setMetaData -->" << metaData;
    m_metaData = std::move(metaData);

}



