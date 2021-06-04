//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_CONNECTIONSIGNALKWSCLIENT_HPP
#define FAIRWIND_CONNECTIONSIGNALKWSCLIENT_HPP

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <FairWindSdk/IFairWindConnection.hpp>

class ConnectionSignalKWSClient : public QObject, public fairwind::connections::IFairWindConnection {
    Q_OBJECT

public:
    explicit ConnectionSignalKWSClient(QObject *parent = nullptr);
    ~ConnectionSignalKWSClient();

    QImage getIcon() const override;
    void onInit(QMap<QString, QVariant> params) override;
    IFairWindConnection *getNewInstance() override;
    QWidget *onSettings() override;
    QString getClassName() const override;
    void setActive(bool active) override;
    bool isActive() const override;

signals:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    bool m_active;
};


#endif //FAIRWIND_CONNECTIONSIGNALKWSCLIENT_HPP
