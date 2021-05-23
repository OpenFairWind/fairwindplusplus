//
// Created by Raffaele Montella on 18/04/21.
//

#ifndef FAIRWIND_SIGNALKDOCUMENT_HPP
#define FAIRWIND_SIGNALKDOCUMENT_HPP


#include <QJsonObject>
#include <QGeoView/QGVGlobal.h>

#include "FairWindSDK.hpp"

typedef void (*myfunc)();

class SignalKDocument;

class FAIRWINDSDK_LIB_DECL Subscription  {


public:
    Subscription()=default;
    Subscription(const QString &fullPath, QObject *receiver, const char *member);
    Subscription(Subscription const &other);

    ~Subscription();

    bool match(SignalKDocument *signalKDocument, const QString &fullPath);
    bool checkReceiver(QObject *);

private:
    QRegularExpression regularExpression;
    QObject *receiver;
    QString memberName;
};

class FAIRWINDSDK_LIB_DECL SignalKDocument: public QObject {
    Q_OBJECT




public:
    explicit SignalKDocument();
    ~SignalKDocument();

    void save(QString fileName);
    void load(QString fileName);

    typedef QString (*FunctionType)(void);

    void subscribe(const QString &fullPath, QObject *receiver, const char *member);

    QJsonObject makeUpdate(const QString &fullPath);
    void update(QJsonObject &jsonObjectUpdate);
    void insert(const QString& path, const QJsonValue& newValue);
    QJsonValue subtree(const QString& path);

    QString getSelf();
    void setSelf(QString self);
    QString getVersion();

    QJsonObject getRoot();
    void setRoot(QJsonObject root);

    QGV::GeoPos getNavigationPosition(const QString& uuid);
    QGV::GeoPos getNavigationPosition();

    double getNavigationCourseOverGroundTrue(const QString& uuid);
    double getNavigationCourseOverGroundTrue();
    double getNavigationSpeedOverGround(const QString& uuid);
    double getNavigationSpeedOverGround();

    QString getMmsi();
    QString getMmsi(const QString& typeUuid);

    QString getNavigationState();
    QString getNavigationState(const QString& typeUuid);

    static QString currentISO8601TimeUTC();

public slots:
    void unsubscribe(QObject *receiver);

signals:
    void updated(const QString &path);
    void updatedNavigationPosition();
    void updatedNavigationCourseOverGroundTrue();
    void updatedNavigationSpeedOverGround();

private:
    QJsonObject m_root;
    QList<Subscription> subscriptions;

    void modifyJsonValue(QJsonObject& obj, const QString& path, const QJsonValue& newValue);

};


#endif //FAIRWIND_SIGNALKDOCUMENT_HPP
