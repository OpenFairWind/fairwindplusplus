//
// Created by Raffaele Montella on 19/04/21.
//

#ifndef FAIRWIND_SIGNALKAPICLIENT_HPP
#define FAIRWIND_SIGNALKAPICLIENT_HPP


#include <QNetworkAccessManager>

class SignalKAPIClient: public QObject {
    Q_OBJECT
public:
    explicit SignalKAPIClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    ~SignalKAPIClient();

    QString getSelf();

private:
    QNetworkAccessManager manager;
    QUrl m_url;
    bool m_debug;

    QByteArray httpGet(QString url);
};


#endif //FAIRWIND_SIGNALKAPICLIENT_HPP
