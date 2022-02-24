//
// Created by Raffaele Montella on 18/04/21.
//

#ifndef FAIRWIND_SIGNALKDOCUMENT_HPP
#define FAIRWIND_SIGNALKDOCUMENT_HPP

#include <QRegularExpression>
#include <QJsonObject>
#include <QGeoCoordinate>
#include <QGeoView/QGVGlobal.h>

#include "FairWindSDK.hpp"

typedef void (*myfunc)();

class SignalKDocument;

class FAIRWINDSDK_LIB_DECL Waypoint: public QJsonObject {
public:
    Waypoint(const QString& id, const QString& name, const QString& description, const QString& type, const QGeoCoordinate& coordinate);

    QString id();
    QString name();
    QString description();
    QString type();
    QGeoCoordinate coordinate();
private:

};

class FAIRWINDSDK_LIB_DECL Note: public QJsonObject {
public:
    Note(const QString& title, const QString& description, const QGeoCoordinate& position);

    QString title();
    QString description();
    QGeoCoordinate position();
    QString region();
    QString geohash();
    QString mimeType();
    QString group();
    QString url();
    QStringList authors();
    QJsonObject properties();
    QString source();
    QDateTime timestamp();

    void setTitle(QString value);
    void setDescription(QString value);
    void setPosition(QGeoCoordinate position);
    void setRegion(QString value);
    void setGeohash(QString value);
    void setMimeType(QString value);
    void setGroup(QString value);
    void setUrl(QString value);
    void setAuthors(QStringList authors);
    void setProperties(QJsonObject properties);
    void setSource(QString value);

private:
    QString getValueStringByKeyOrEmpty(QString key);
    void setValueStringByKeyIfAny(QString key, QString value);
};

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
    void insert(const QString& path, const QJsonValue& newValue, int mode = 1);

    void set(const QString& fullPath, const QJsonValue& newValue);
    QJsonValue get(const QString& fullPath);

    QJsonValue subtree(const QString& path);

    QString getSelf();
    void setSelf(QString self);
    QString getVersion();

    QJsonObject getRoot();
    void setRoot(QJsonObject root);

    QGeoCoordinate getNavigationPosition(const QString& uuid);
    QGeoCoordinate getNavigationPosition();

    double getNavigationCourseOverGroundTrue(const QString& uuid);
    double getNavigationCourseOverGroundTrue();
    double getNavigationSpeedOverGround(const QString& uuid);
    double getNavigationSpeedOverGround();

    QString getMmsi();
    QString getMmsi(const QString& typeUuid);

    QString getNavigationState();
    QString getNavigationState(const QString& typeUuid);

    static QString currentISO8601TimeUTC();

    QString generateUUID();

public slots:
    void unsubscribe(QObject *receiver);

signals:
    void created(const QString &path, const QJsonValue &newValue);
    void updated(const QString &path, const QJsonValue &newValue);
    void changed(const QString &path);
    void updatedNavigationPosition();
    void updatedNavigationCourseOverGroundTrue();
    void updatedNavigationSpeedOverGround();

private:
    QJsonObject m_root;
    QList<Subscription> subscriptions;

    void modifyJsonValue(QJsonObject& obj, const QString& path, const QJsonValue& newValue);
    void object2pathAndValue(QMap<QString, QJsonValue> &map, const QString &path, const QJsonValue value);
};

#endif //FAIRWIND_SIGNALKDOCUMENT_HPP