//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_SIGNALKAPICLIENT_HPP
#define FAIRWIND_SIGNALKAPICLIENT_HPP

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindConnection.hpp>

namespace fairwind::connections {

    class FAIRWINDSDK_LIB_DECL SignalKAPIClient : public QObject, public fairwind::connections::IFairWindConnection {
    Q_OBJECT

    public:
        explicit SignalKAPIClient(QObject *parent = nullptr);
        ~SignalKAPIClient();

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
}

#endif //FAIRWIND_SIGNALKAPICLIENT_HPP
