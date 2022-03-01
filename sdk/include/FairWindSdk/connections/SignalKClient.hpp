//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_SIGNALKCLIENT_HPP
#define FAIRWIND_SIGNALKCLIENT_HPP

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IConnection.hpp>

namespace fairwind::connections {
    class FAIRWINDSDK_LIB_DECL SignalKClient : public QObject, public fairwind::connections::IConnection {
    Q_OBJECT
    public:
        explicit SignalKClient(QObject *parent = nullptr);
        ~SignalKClient();

        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IConnection *getNewInstance() override;
        QWidget *onSettings() override;
        QString getClassName() const override;
        void setActive(bool active) override;
        bool isActive() const override;

        QString getName() const override;
        void setLabel(QString label) override;
        QString getLabel() const override;

        QString getSelf();

        QJsonObject getAll();

        bool login();

        QString http();
        QString ws();
        QString tcp();

        QJsonObject signalkGet(QString url);
        QJsonObject signalkPost(QString url, QJsonObject payload);
        QJsonObject signalkPut(QString url, QJsonObject payload);


    private slots:
        void onConnected();
        void onDisconnected();
        void onTextMessageReceived(QString message);

        QJsonValue onCreated(const QString &path, const QJsonValue &newValue);
        QJsonValue onUpdated(const QString &path, const QJsonValue &newValue);
        QJsonValue onFetched(const QString &path);

    private:
        QString mUsername;
        QString mPassword;
        QString mToken;
        QString mCookie;


        QWebSocket mWebSocket;

        QNetworkAccessManager manager;
        QString mUrl;
        QString mVersion;
        bool mRestore;
        bool mDebug;
        bool mActive;
        QString mLabel;

        QByteArray httpGet(QString url);
        QByteArray httpPost(QString url, QJsonObject payload);
        QByteArray httpPut(QString url, QJsonObject payload);

        QString getEndpointByProtocol(const QString &protocol);

        QJsonObject mServer;
    };
}

#endif //FAIRWIND_SIGNALKCLIENT_HPP