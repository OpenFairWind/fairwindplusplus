//
// Created by Raffaele Montella on 01/03/22.
//

#include <FairWindSdk/signalk/Subscription.hpp>


namespace fairwind::signalk {
/*
 * Subscription - Public Constructor
 */
    Subscription::Subscription(const QString &fullPath, QObject *receiver, const char *member) {
        //qDebug() << "fullPath: " << fullPath << " receiver: " << receiver->metaObject()->className() << " member:" << member;
        QString re = QString(fullPath).replace(".", "[.]").replace(":", "[:]").replace("*", ".*");
        regularExpression = QRegularExpression(fullPath);
        this->receiver = receiver;
        memberName = QString(member);
        int pos = memberName.lastIndexOf("::");
        memberName = memberName.right(memberName.length() - pos - 2);
        //QString className=QString(receiver->metaObject()->className());
        //int pos=memberName.indexOf(className)+className.length()+2;
        //memberName= memberName.right(memberName.length()-pos);
        //qDebug() << "regularExpression: " << regularExpression << " receiver: " << receiver->metaObject()->className() << " member:" << memberName;
    }

/*
 * ~Subscription - Destructor
 */
    Subscription::~Subscription() = default;

/*
 * checkReceiver
 * Returns true is the provided receiver matches with the existent receiver in use
 */
    bool Subscription::checkReceiver(QObject *receiver) {
        if (this->receiver == receiver) return true;
        return false;
    }

    bool Subscription::match(Document *document, const QString &fullPath) {
        if (regularExpression.match(fullPath).hasMatch()) {
            //qDebug() << "Subscription::match("  << fullPath << ") :" << memberName;
            QJsonObject updateObject = document->makeUpdate(fullPath);

            QMetaObject::invokeMethod(receiver, memberName.toStdString().c_str(), Qt::AutoConnection,
                                      Q_ARG(QJsonObject, updateObject));
            //qDebug() << "Done!";
            return true;
        }

        return false;
    }

/*
 * Subscription - Public Constructor
 */
    Subscription::Subscription(Subscription const &other) {
        this->regularExpression = other.regularExpression;
        this->receiver = other.receiver;
        this->memberName = other.memberName;
    }
}



