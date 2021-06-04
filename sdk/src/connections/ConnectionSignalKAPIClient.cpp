//
// Created by Raffaele Montella on 03/06/21.
//

#include <QNetworkReply>
#include <QCoreApplication>
#include <QJsonDocument>
#include <FairWind.hpp>
#include "FairWindSdk/connections/ConnectionSignalKAPIClient.hpp"

ConnectionSignalKAPIClient::ConnectionSignalKAPIClient(QObject *parent):
        QObject(parent) {
    m_url = "localhost:3000/signalk/v1/api";
    m_debug = false;
    m_active = false;
}

ConnectionSignalKAPIClient::~ConnectionSignalKAPIClient() {

}

QImage ConnectionSignalKAPIClient::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *ConnectionSignalKAPIClient::onSettings() {
    return nullptr;
}

void ConnectionSignalKAPIClient::onInit(QMap<QString, QVariant> params) {
    qDebug() << "ConnectionSignalKAPIClient::onInit(" << params << ")";

    auto fairWind=fairwind::FairWind::getInstance();

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
        QJsonObject allSignalK = getAll();
        fairWind->getSignalKDocument()->setRoot(allSignalK);
    }
}

fairwind::connections::IFairWindConnection *ConnectionSignalKAPIClient::getNewInstance() {
    return static_cast<IFairWindConnection *>(new ConnectionSignalKAPIClient());
}

QString ConnectionSignalKAPIClient::getClassName() const {
    return this->metaObject()->className();
}

void ConnectionSignalKAPIClient::setActive(bool active) {
    m_active=active;
}

bool ConnectionSignalKAPIClient::isActive() const {
    return m_active;
}

QString ConnectionSignalKAPIClient::getSelf() {
    QString url=m_url.toString()+"/self";
    QString result=httpGet( url).replace("\"","");
    qDebug() << "url:" << url << " result:" << result;
    return result;
}

QJsonObject ConnectionSignalKAPIClient::getAll() {
    QString url=m_url.toString()+"/";
    QString httpResult=httpGet( url);
    QJsonDocument jsonDocument=QJsonDocument::fromJson(httpResult.toUtf8());
    return jsonDocument.object();
}

QByteArray ConnectionSignalKAPIClient::httpGet(QString url) {
    QNetworkRequest req(url);
    QScopedPointer<QNetworkReply> reply(manager.get(req));

    QTime timeout= QTime::currentTime().addSecs(10);
    while( QTime::currentTime() < timeout && !reply->isFinished()){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Failure" <<reply->errorString();
    }
    QByteArray data = reply->readAll();
    return data;
}


