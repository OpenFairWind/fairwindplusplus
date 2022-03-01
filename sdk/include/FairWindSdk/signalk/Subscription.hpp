//
// Created by Raffaele Montella on 01/03/22.
//

#ifndef FAIRWIND_SDK_SIGNALK_SUBSCRIPTION_HPP
#define FAIRWIND_SDK_SIGNALK_SUBSCRIPTION_HPP

#include <QRegularExpression>
#include <QJsonObject>
#include <FairWindSDK/FairWindSDK.hpp>
#include <FairWindSdk/signalk/Document.hpp>


namespace fairwind::signalk {

    class Document;

    class FAIRWINDSDK_LIB_DECL Subscription {
    public:
        Subscription() = default;

        Subscription(const QString &fullPath, QObject *receiver, const char *member);

        Subscription(Subscription const &other);

        ~Subscription();

        bool match(Document *document, const QString &fullPath);

        bool checkReceiver(QObject *);

    private:
        QRegularExpression regularExpression;
        QObject *receiver;
        QString memberName;
    };
}

#endif //FAIRWIND_SDK_SIGNALK_SUBSCRIPTION_HPP
