//
// Created by Raffaele Montella on 03/06/21.
//

#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include <FairWindSdk/FairWind.hpp>
#include <connections/SignalKWSClient.hpp>

QT_USE_NAMESPACE

//! [constructor]
fairwind::connections::SignalKWSClient::SignalKWSClient(QObject *parent) :
        QObject(parent) {
    m_url = "ws://localhost:3000/signalk/v1/stream";
    m_debug = false;
    m_active = false;

    connect(&m_webSocket, &QWebSocket::connected, this, &SignalKWSClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SignalKWSClient::closed);

}
//! [constructor]

fairwind::connections::SignalKWSClient::~SignalKWSClient() {}

/*
 * getIcon
 * Returns the client's icon
 */
QImage fairwind::connections::SignalKWSClient::getIcon() const {
    return QImage(":/resources/images/icons/signalk_icon.png");
}

/*
 * onSettings
 * Returns the client's settings
 */
QWidget *fairwind::connections::SignalKWSClient::onSettings() {
    return m_settings;
}

/*
 * onInit
 * Initialization method
 */
void fairwind::connections::SignalKWSClient::onInit(QMap <QString, QVariant> params) {
    qDebug() << "SignalKWSClient::onInit(" << params << ")";

    if (params.contains("url")) {
        m_url = QUrl(params["url"].toString());
    }

    if (params.contains("label")) {
        m_label = params["label"].toString();
    }

    if (params.contains("active")) {
        m_active = params["active"].toBool();
    }

    if (params.contains("debug")) {
        m_debug = params["debug"].toBool();
    }

    if (m_active) {
        m_webSocket.open(QUrl(m_url));
    }
}

/*
 * getNewInstance
 * Creates and returns a new instance of the client
 */
fairwind::connections::IConnection *fairwind::connections::SignalKWSClient::getNewInstance() {
    return static_cast<IConnection *>(new SignalKWSClient());
}

/*
 * getClassName
 * Returns the client's class name
 */
QString fairwind::connections::SignalKWSClient::getClassName() const {
    return this->metaObject()->className();
}

/*
 * setActive
 * Sets the client's active state: if active, it will open the websocket, if not, it will close the websocket
 */
void fairwind::connections::SignalKWSClient::setActive(bool active) {
    if (m_active && !active) {
        m_webSocket.close();
    } else if (!m_active && active) {
        m_webSocket.open(m_url);
    }

    m_active = active;
}

/*
 * isActive
 * Returns the client's active state
 */
bool fairwind::connections::SignalKWSClient::isActive() const {
    return m_active;
}

//! [onConnected]
void fairwind::connections::SignalKWSClient::onConnected() {
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &fairwind::connections::SignalKWSClient::onTextMessageReceived);

}
//! [onConnected]

//! [onTextMessageReceived]
void fairwind::connections::SignalKWSClient::onTextMessageReceived(QString message) {
    QJsonObject jsonObjectUpdate;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8());

    // check validity of the document
    if (!jsonDocument.isNull()) {
        if (jsonDocument.isObject()) {
            jsonObjectUpdate = jsonDocument.object();
        }
    }

    //if (m_debug)
    //    qDebug() << "Update received:" << message;

    auto fairWind = fairwind::FairWind::getInstance();
    fairWind->getSignalKDocument()->update(jsonObjectUpdate);

}
//! [onTextMessageReceived]

QString fairwind::connections::SignalKWSClient::getName() const {
    return tr("Signal K WS Client");
}

/*
 * setLabel
 * Sets the client's label
 */
void fairwind::connections::SignalKWSClient::setLabel(QString label) {
    m_label = label;
}

/*
 * getLabel
 * Returns the client's label
 */
QString fairwind::connections::SignalKWSClient::getLabel() const {
    return m_label;
}