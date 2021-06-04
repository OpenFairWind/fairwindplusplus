//
// Created by Raffaele Montella on 03/06/21.
//

#include <FairWindSdk/FairWind.hpp>

#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <connections/SignalKWSClient.hpp>


QT_USE_NAMESPACE

//! [constructor]
fairwind::connections::SignalKWSClient::SignalKWSClient(QObject *parent) :
        QObject(parent)
{
    m_url="ws://localhost:3000/signalk/v1/stream";
    m_debug= false;
    m_active = false;

    connect(&m_webSocket, &QWebSocket::connected, this, &SignalKWSClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SignalKWSClient::closed);

}
//! [constructor]

fairwind::connections::SignalKWSClient::~SignalKWSClient() {

}

QImage fairwind::connections::SignalKWSClient::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::connections::SignalKWSClient::onSettings() {
    return nullptr;
}

void fairwind::connections::SignalKWSClient::onInit(QMap<QString, QVariant> params) {
    qDebug() << "SignalKWSClient::onInit(" << params << ")";

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

fairwind::connections::IFairWindConnection *fairwind::connections::SignalKWSClient::getNewInstance() {
    return static_cast<IFairWindConnection *>(new SignalKWSClient());
}

QString fairwind::connections::SignalKWSClient::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::connections::SignalKWSClient::setActive(bool active) {
    if (m_active && !active) {
        m_webSocket.close();
    } else if (!m_active && active) {
        m_webSocket.open(m_url);
    }

    m_active=active;
}

bool fairwind::connections::SignalKWSClient::isActive() const {
    return m_active;
}

//! [onConnected]
void fairwind::connections::SignalKWSClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &fairwind::connections::SignalKWSClient::onTextMessageReceived);

}
//! [onConnected]

//! [onTextMessageReceived]
void fairwind::connections::SignalKWSClient::onTextMessageReceived(QString message)
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
