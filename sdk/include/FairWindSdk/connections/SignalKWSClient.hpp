//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_SIGNALKWSCLIENT_HPP
#define FAIRWIND_SIGNALKWSCLIENT_HPP

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IConnection.hpp>

namespace fairwind::connections {
    class FAIRWINDSDK_LIB_DECL SignalKWSClient : public QObject, public fairwind::connections::IConnection {
    Q_OBJECT
    public:
        explicit SignalKWSClient(QObject *parent = nullptr);
        ~SignalKWSClient();

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

    signals:
        void closed();

    private slots:
        void onConnected();
        void onTextMessageReceived(QString message);

    private:
        QWidget *m_settings;

        QWebSocket m_webSocket;
        QUrl m_url;
        bool m_debug;
        bool m_active;
        QString m_label;
    };
}

#endif //FAIRWIND_SIGNALKWSCLIENT_HPP