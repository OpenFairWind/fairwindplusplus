//
// Created by Raffaele Montella on 18/04/21.
//

#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <iomanip>
#include <sstream>

#include "SignalKDocument.hpp"

SignalKDocument::SignalKDocument() {
    insert("version", "1.0.0");
}

SignalKDocument::~SignalKDocument() {}

void SignalKDocument::update(QJsonObject &jsonObjectUpdate) {
    auto context = jsonObjectUpdate["context"].toString();
    auto updates = jsonObjectUpdate["updates"].toArray();
    for (auto updateItem: updates) {
        QJsonObject source = updateItem.toObject()["source"].toObject();
        QString timeStamp = updateItem.toObject()["timestamp"].toString();
        auto values = updateItem.toObject()["values"].toArray();
        for (auto valueItem: values) {
            QString fullPath = context + "." + valueItem.toObject()["path"].toString();
            QJsonValue value = valueItem.toObject()["value"];
            insert(fullPath + ".value", value);
            insert(fullPath + ".source", source);
            insert(fullPath + ".timestamp", timeStamp);

        }
    }
    //qDebug() << m_jsonDocument.toJson();

}

void SignalKDocument::modifyJsonValue(QJsonObject &obj, const QString &path, const QJsonValue &newValue) {
    const int indexOfDot = path.indexOf('.');
    const QString propertyName = path.left(indexOfDot);
    const QString subPath = indexOfDot > 0 ? path.mid(indexOfDot + 1) : QString();

    QJsonValue subValue = obj[propertyName];

    if (subPath.isEmpty()) {
        subValue = newValue;
    } else {
        QJsonObject obj = subValue.toObject();
        modifyJsonValue(obj, subPath, newValue);
        subValue = obj;
    }

    obj[propertyName] = subValue;
}

void SignalKDocument::insert(const QString &fullPath, const QJsonValue &newValue) {
    modifyJsonValue(m_root, fullPath, newValue);

    //qDebug() << "SignalKDocument::insert: " << fullPath;
    emit updated(fullPath);

    if (fullPath.indexOf(getSelf() + ".navigation.position") >= 0) {
        emit updatedNavigationPosition();
    } else if (fullPath.indexOf(getSelf() + "navigation.courseOverGroundTrue") >= 0) {
        emit updatedNavigationCourseOverGroundTrue();
    } else if (fullPath.indexOf(getSelf() + "navigation.speedOverGround") >= 0) {
        emit updatedNavigationSpeedOverGround();
    }

    for (auto subscription: subscriptions) {
        subscription.match(this, fullPath);
    }
}

/*
 * getSelf
 * Returns the SignalK document self key
 */
QString SignalKDocument::getSelf() {
    return m_root["self"].toString();
}

/*
 * getVersion
 * Returns the SignalK document version
 */
QString SignalKDocument::getVersion() {
    return m_root["version"].toString();
}

QJsonValue SignalKDocument::subtree(const QString &path) {
    QStringList parts = path.split(".");
    QJsonValue jsonValue = m_root;
    for (auto part: parts) {
        if (jsonValue.isObject()) {
            QJsonObject jsonObject = jsonValue.toObject();
            jsonValue = jsonObject[part];
        } else {
            break;
        }
    }

    return jsonValue;
}

/*
 * save
 * Saves the current SignalK document state in a local file
 */
void SignalKDocument::save(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(m_root);
    jsonFile.write(jsonDocument.toJson());
}

/*
 * load
 * Loads a new SignalK document state from a local file
 */
void SignalKDocument::load(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    QString jsonString = jsonFile.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
}

/*
 * setSelf
 * Inserts a new self key inside the SignalK document
 */
void SignalKDocument::setSelf(QString self) {
    insert("self", self);
}

/*
 * getNavigationPosition
 * Helper method, calls the actual getNavigationPosition(QString) method
 */
QGV::GeoPos SignalKDocument::getNavigationPosition() {
    return getNavigationPosition(getSelf());
}

/*
 * getNavigationPosition
 * Returns the navigation information received from the SignalK settings in form of a QGV GeoPos object
 */
QGV::GeoPos SignalKDocument::getNavigationPosition(const QString &uuid) {
    QGV::GeoPos result;
    QString path = uuid + ".navigation.position.value";

    QJsonValue positionValue = subtree(path);
    if (positionValue.isObject()) {
        double latitude = positionValue.toObject()["latitude"].toDouble();
        double longitude = positionValue.toObject()["longitude"].toDouble();
        result.setLat(latitude);
        result.setLon(longitude);
    }
    return result;
}

/*
 * getNavigationCourseOverGroundTrue
 * Helper method, calls the actual getNavigationCourseOverGroundTrue(QString) method
 */
double SignalKDocument::getNavigationCourseOverGroundTrue() {
    return getNavigationCourseOverGroundTrue(getSelf());
}

double SignalKDocument::getNavigationCourseOverGroundTrue(const QString &uuid) {
    QString path = uuid + ".navigation.courseOverGroundTrue";
    double courseOverGroundTrue = subtree(path)["value"].toDouble();
    return courseOverGroundTrue;
}

/*
 * getNavigationSpeedOverGround
 * Helper method, calls the actual getNavigationSpeedOverGround(QString) method
 */
double SignalKDocument::getNavigationSpeedOverGround() {
    return getNavigationSpeedOverGround(getSelf());
}

double SignalKDocument::getNavigationSpeedOverGround(const QString &uuid) {
    QString path = uuid + ".navigation.speedOverGround";
    double speedOverGround = subtree(path)["value"].toDouble();
    return speedOverGround;
}

/*
 * subscribe
 * Subscribes to a new SignalK key to receive new navigation infos
 */
void SignalKDocument::subscribe(const QString &fullPath, QObject *receiver, const char *member) {
    Subscription subscription(fullPath, receiver, member);
    subscriptions.append(subscription);
    connect(receiver, &QObject::destroyed, this, &SignalKDocument::unsubscribe);
}

/*
 * unsubscribe
 * Unsubscribes from a SignalK key to stop receiving navigation infos
 */
void SignalKDocument::unsubscribe(QObject *receiver) {
    QMutableListIterator <Subscription> i(subscriptions);
    while (i.hasNext()) {
        auto subscription = i.next();
        if (subscription.checkReceiver(receiver)) {
            i.remove();
        }
    }
}

/**
 * Generate a UTC ISO8601-formatted timestamp
 * and return as std::string
 */
QString SignalKDocument::currentISO8601TimeUTC() {
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%FT%TZ");
    return QString(ss.str().c_str());
}

QJsonObject SignalKDocument::makeUpdate(const QString &fullPath) {
    QJsonObject updateObject;
    QStringList parts = fullPath.split(".");

    if (parts[0] == "vessels") {
        QString context = parts[0] + "." + parts[1];
        updateObject["context"] = context;
        QJsonArray updates;
        QJsonObject update;
        QJsonObject source;
        source["label"] = "FairWind++";
        source["type"] = "SignalK";
        update["source"] = source;
        update["timestamp"] = currentISO8601TimeUTC();
        QJsonArray values;
        QJsonObject valueObject;

        QString path = fullPath;
        QJsonValue value = subtree(fullPath);
        path = path.replace(context + ".", "");

        if (path.endsWith(".value")) {
            path = path.left(path.length() - 6);
        }
        valueObject["path"] = path;
        valueObject["value"] = value;
        values.append(valueObject);
        update["values"] = values;
        updates.append(update);
        updateObject["updates"] = updates;
    }

    return updateObject;
}

/*
 * getRoot
 * Returns the root object
 */
QJsonObject SignalKDocument::getRoot() {
    return m_root;
}

/*
 * setRoot
 * Sets the root object
 */
void SignalKDocument::setRoot(QJsonObject root) {
    this->m_root = root;
}

/*
 * getMmsi(QString)
 * Returns the Marine Mobile Service Identity
 */
QString SignalKDocument::getMmsi(const QString &typeUuid) {
    QString result = "";
    QJsonValue jsonValue = subtree(typeUuid + ".mmsi");

    if (!jsonValue.isNull() && jsonValue.isString()) {
        result = jsonValue.toString();
    }

    return result;
}

/*
 * getMmsi
 * Helper method, calls the actual getMmsi(QString) method
 */
QString SignalKDocument::getMmsi() {
    return getMmsi(getSelf());
}

/*
 * getNavigationState(QString)
 * Returns the vessel's navigation state
 */
QString SignalKDocument::getNavigationState(const QString &typeUuid) {
    QString result = "";
    QJsonValue jsonValue = subtree(typeUuid + ".navigation.state");

    if (!jsonValue.isNull() && jsonValue.isObject() && jsonValue.toObject().contains("value")) {
        result = jsonValue.toObject()["value"].toString();
    }

    return result;
}

/*
 * getNavigationState
 * Helper method, calls the actual getNavigationState(QString) method
 */
QString SignalKDocument::getNavigationState() {
    return getNavigationState(getSelf());
}

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

bool Subscription::match(SignalKDocument *signalKDocument, const QString &fullPath) {
    if (regularExpression.match(fullPath).hasMatch()) {
        //qDebug() << "Subscription::match("  << fullPath << ") :" << memberName;
        QJsonObject updateObject = signalKDocument->makeUpdate(fullPath);

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