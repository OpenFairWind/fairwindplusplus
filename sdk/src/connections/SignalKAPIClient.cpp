//
// Created by Raffaele Montella on 03/06/21.
//

#include <QNetworkReply>
#include <QCoreApplication>
#include <QJsonDocument>

#include <FairWind.hpp>
#include <FairWindSdk/connections/SignalKAPIClient.hpp>

/*
 * SignalKAPIClient - Public Constructor
 */
fairwind::connections::SignalKAPIClient::SignalKAPIClient(QObject *parent) :
        QObject(parent) {
    m_url = "localhost:3000/signalk/v1/api";
    m_debug = false;
    m_active = false;
}

/*
 * ~SignalKAPIClient - Destructor
 */
fairwind::connections::SignalKAPIClient::~SignalKAPIClient() {}

/*
 * getIcon
 * Returns the client's icon
 */
QImage fairwind::connections::SignalKAPIClient::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

/*
 * onSettings
 * Returns the client's settings
 */
QWidget *fairwind::connections::SignalKAPIClient::onSettings() {
    return m_settings;
}

/*
 * onInit
 * Initialization method
 */
void fairwind::connections::SignalKAPIClient::onInit(QMap <QString, QVariant> params) {
    qDebug() << "ConnectionSignalKAPIClient::onInit(" << params << ")";

    auto fairWind = fairwind::FairWind::getInstance();

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
        QJsonObject allSignalK = getAll();
        fairWind->getSignalKDocument()->setRoot(allSignalK);
    }
}

/*
 * getNewInstance
 * Creates and returns a new instance of the client
 */
fairwind::connections::IConnection *fairwind::connections::SignalKAPIClient::getNewInstance() {
    return static_cast<IConnection *>(new SignalKAPIClient());
}

QString fairwind::connections::SignalKAPIClient::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::connections::SignalKAPIClient::setActive(bool active) {
    m_active = active;
}

bool fairwind::connections::SignalKAPIClient::isActive() const {
    return m_active;
}

/*
 * getSelf
 * Returns the self key
 */
QString fairwind::connections::SignalKAPIClient::getSelf() {
    QString url = m_url.toString() + "/self";
    QString result = httpGet(url).replace("\"", "");
    qDebug() << "url:" << url << " result:" << result;
    return result;
}

QJsonObject fairwind::connections::SignalKAPIClient::getAll() {
    QString url = m_url.toString() + "/";
    QString httpResult = httpGet(url);
    QJsonDocument jsonDocument = QJsonDocument::fromJson(httpResult.toUtf8());
    return jsonDocument.object();
}

/*
 * httpGet
 * Executes a http get request
 */
QByteArray fairwind::connections::SignalKAPIClient::httpGet(QString url) {
    QNetworkRequest req(url);
    QScopedPointer <QNetworkReply> reply(manager.get(req));

    QTime timeout = QTime::currentTime().addSecs(10);
    while (QTime::currentTime() < timeout && !reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Failure" << reply->errorString();
    }
    QByteArray data = reply->readAll();
    return data;
}

/*
 * setName
 * Sets the client's name
 */
QString fairwind::connections::SignalKAPIClient::getName() const {
    return tr("Signal K API Client");
}

/*
 * setLabel
 * Sets the client's label
 */
void fairwind::connections::SignalKAPIClient::setLabel(QString label) {
    m_label = label;
}

/*
 * getLabel
 * Returns the client's label
 */
QString fairwind::connections::SignalKAPIClient::getLabel() const {
    return m_label;
}