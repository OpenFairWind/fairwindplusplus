//
// Created by Raffaele Montella on 18/04/21.
//

#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "../include/SignalKDocument.hpp"

SignalKDocument::SignalKDocument() {
    insert("version","1.0.0");
    insert("self","urn:mrn:signalk:uuid:39deb5a7-747a-4f16-a6c9-6808de59f6ba");

}

SignalKDocument::~SignalKDocument() {

}

void SignalKDocument::update(QJsonObject &jsonObjectUpdate) {
    auto context = jsonObjectUpdate["context"].toString();
    auto updates = jsonObjectUpdate["updates"].toArray();
    for (auto updateItem: updates) {
        QJsonObject source=updateItem.toObject()["source"].toObject();
        QString timeStamp=updateItem.toObject()["timestamp"].toString();
        auto values=updateItem.toObject()["values"].toArray();
        for (auto valueItem: values) {
            QString path = context + "."+valueItem.toObject()["path"].toString();
            QJsonValue value = valueItem.toObject()["value"];
            insert(path+".value",value);
            insert(path+".source",source);
            insert(path+".timestamp",timeStamp);

        }
    }
    //qDebug() << m_jsonDocument.toJson();

}

void SignalKDocument::modifyJsonValue(QJsonObject& obj, const QString& path, const QJsonValue& newValue) {
    const int indexOfDot = path.indexOf('.');
    const QString propertyName = path.left(indexOfDot);
    const QString subPath = indexOfDot>0 ? path.mid(indexOfDot+1) : QString();

    QJsonValue subValue = obj[propertyName];

    if(subPath.isEmpty()) {
        subValue = newValue;
    }
    else {
        QJsonObject obj = subValue.toObject();
        modifyJsonValue(obj,subPath,newValue);
        subValue = obj;
    }

    obj[propertyName] = subValue;
}
void SignalKDocument::insert(const QString& path, const QJsonValue& newValue) {
    QJsonObject obj = m_jsonDocument.object();
    modifyJsonValue(obj,path,newValue);
    m_jsonDocument = QJsonDocument(obj);
    emit updated(path);
    if (path.indexOf("navigation.position")>=0) {
        emit updatedNavigationPosition();
    }
}

QString SignalKDocument::getSelf() {
    return m_jsonDocument.object()["self"].toString();
}

QString SignalKDocument::getVersion() {
    return m_jsonDocument.object()["version"].toString();
}

QJsonObject SignalKDocument::subtree(const QString& path) {
    QStringList parts=path.split(".");
    QJsonObject jsonObject=m_jsonDocument.object();
    for (auto part:parts) {
        if (jsonObject.contains(part)) {
            jsonObject=jsonObject[part].toObject();
        } else {
            return QJsonObject();
        }
    }

    return jsonObject;
}

void SignalKDocument::save(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(m_jsonDocument.toJson());
}

void SignalKDocument::load(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    m_jsonDocument.fromJson(jsonFile.readAll());
}
