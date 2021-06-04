//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_CONNECTIONSIGNALKAPICLIENT_HPP
#define FAIRWIND_CONNECTIONSIGNALKAPICLIENT_HPP

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <FairWindSdk/IFairWindConnection.hpp>

class ConnectionSignalKAPIClient : public QObject, public fairwind::connections::IFairWindConnection {
    Q_OBJECT

public:
    explicit ConnectionSignalKAPIClient(QObject *parent = nullptr);
    ~ConnectionSignalKAPIClient();

    QImage getIcon() const override;
    void onInit(QMap<QString, QVariant> params) override;
    IFairWindConnection *getNewInstance() override;
    QWidget *onSettings() override;
    QString getClassName() const override;
    void setActive(bool active) override;
    bool isActive() const override;

    QString getSelf();
    QJsonObject getAll();

private:
    QNetworkAccessManager manager;
    QUrl m_url;
    bool m_debug;
    bool m_active;

    QByteArray httpGet(QString url);

};


#endif //FAIRWIND_CONNECTIONSIGNALKAPICLIENT_HPP
