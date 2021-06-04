//
// Created by Raffaele Montella on 03/06/21.
//

#include "FairWindSdk/connections/ConnectionSignalKWSClient.hpp"
#include <FairWindSdk/FairWind.hpp>

#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

//! [constructor]
ConnectionSignalKWSClient::ConnectionSignalKWSClient(QObject *parent) :
        QObject(parent)
{
    m_url="ws://localhost:3000/signalk/v1/stream";
    m_debug= false;
    m_active = false;

    connect(&m_webSocket, &QWebSocket::connected, this, &ConnectionSignalKWSClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ConnectionSignalKWSClient::closed);

}
//! [constructor]

ConnectionSignalKWSClient::~ConnectionSignalKWSClient() {

}

QImage ConnectionSignalKWSClient::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *ConnectionSignalKWSClient::onSettings() {
    return nullptr;
}

void ConnectionSignalKWSClient::onInit(QMap<QString, QVariant> params) {
    qDebug() << "ConnectionSignalKWSClient::onInit(" << params << ")";

    if (params.contains("url")) {
        m_url=QUrl(params["url"].toString());
    }

    if (params.contains("active")) {
        m_active=params["active"].toBool();
    }

    if (params.contains("debug")) {
        m_debug=params["debug"].toBool();
    }

    if (m_active) {
        m_webSocket.open(QUrl(m_url));
    }
}

fairwind::connections::IFairWindConnection *ConnectionSignalKWSClient::getNewInstance() {
    return static_cast<IFairWindConnection *>(new ConnectionSignalKWSClient());
}

QString ConnectionSignalKWSClient::getClassName() const {
    return this->metaObject()->className();
}

void ConnectionSignalKWSClient::setActive(bool active) {
    if (m_active && !active) {
        m_webSocket.close();
    } else if (!m_active && active) {
        m_webSocket.open(m_url);
    }

    m_active=active;
}

bool ConnectionSignalKWSClient::isActive() const {
    return m_active;
}

//! [onConnected]
void ConnectionSignalKWSClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ConnectionSignalKWSClient::onTextMessageReceived);

}
//! [onConnected]

//! [onTextMessageReceived]
void ConnectionSignalKWSClient::onTextMessageReceived(QString message)
{
    QJsonObject jsonObjectUpdate;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8());

    // check validity of the document
    if(!jsonDocument.isNull())
    {
        if(jsonDocument.isObject())
        {
            jsonObjectUpdate = jsonDocument.object();
        }
    }

    //if (m_debug)
    //    qDebug() << "Update received:" << message;

    auto fairWind = fairwind::FairWind::getInstance();
    fairWind->getSignalKDocument()->update(jsonObjectUpdate);

}


//! [onTextMessageReceived]