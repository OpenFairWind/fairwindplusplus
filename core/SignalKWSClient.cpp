//
// Created by Raffaele Montella on 18/04/21.
//

#include "SignalKWSClient.hpp"
#include "FairWind.hpp"

#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QT_USE_NAMESPACE

//! [constructor]
SignalKWSClient::SignalKWSClient(const QUrl &url, bool debug, QObject *parent) :
        QObject(parent),
        m_url(url),
        m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &SignalKWSClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SignalKWSClient::closed);
    m_webSocket.open(QUrl(url));
}
//! [constructor]

//! [onConnected]
void SignalKWSClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &SignalKWSClient::onTextMessageReceived);

}
//! [onConnected]

//! [onTextMessageReceived]
void SignalKWSClient::onTextMessageReceived(QString message)
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