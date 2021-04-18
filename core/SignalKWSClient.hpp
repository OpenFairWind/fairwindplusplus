//
// Created by Raffaele Montella on 18/04/21.
//

#ifndef FAIRWIND_SIGNALKWSCLIENT_HPP
#define FAIRWIND_SIGNALKWSCLIENT_HPP

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class SignalKWSClient : public QObject
{
Q_OBJECT
public:
    explicit SignalKWSClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);

signals:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};


#endif //FAIRWIND_SIGNALKWSCLIENT_HPP
