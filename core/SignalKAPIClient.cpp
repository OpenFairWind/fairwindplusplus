//
// Created by Raffaele Montella on 19/04/21.
//

#include <QNetworkReply>
#include <QCoreApplication>
#include "SignalKAPIClient.hpp"

SignalKAPIClient::SignalKAPIClient(const QUrl &url, bool debug, QObject *parent):
        QObject(parent),
        m_url(url),
        m_debug(debug) {

    /*
    connect(&manager, &QNetworkAccessManager::finished,
            this, &SignalKAPIClient::onManagerFinished);
            */
}

SignalKAPIClient::~SignalKAPIClient() {

}

QString SignalKAPIClient::getSelf() {
    QString url=m_url.toString()+"/self";
    QString result=httpGet( url).replace("vessels.","").replace("\"","");
    qDebug() << "url:" << url << " result:" << result;
    return result;
}



QByteArray SignalKAPIClient::httpGet(QString url) {
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