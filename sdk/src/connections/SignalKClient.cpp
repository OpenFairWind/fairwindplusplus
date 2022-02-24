//
// Created by Raffaele Montella on 03/06/21.
//

#include <QNetworkReply>
#include <QCoreApplication>
#include <QJsonDocument>

#include <FairWind.hpp>
#include <FairWindSdk/connections/SignalKClient.hpp>

namespace fairwind::connections {
/*
 * SignalKAPIClient - Public Constructor
 */
    SignalKClient::SignalKClient(QObject *parent) :
            QObject(parent) {

        mUrl = "http://localhost:3000/signalk";
        mVersion = "v1";
        mActive = false;
        mDebug = false;
        mLabel = "Signal K Connection";
        mUsername = "admin";
        mPassword = "password";
    }

/*
 * ~SignalKAPIClient - Destructor
 */
    SignalKClient::~SignalKClient() {}

/*
 * getIcon
 * Returns the client's icon
 */
    QImage SignalKClient::getIcon() const {
        return QImage(":resources/images/icons/signalk_icon.png");
    }

/*
 * onSettings
 * Returns the client's settings
 */
    QWidget *SignalKClient::onSettings() {
        return nullptr;
    }

/*
 * onInit
 * Initialization method
 */
    void SignalKClient::onInit(QMap<QString, QVariant> params) {
        qDebug() << "SignalKAPIClient::onInit(" << params << ")";


        auto fairWind = fairwind::FairWind::getInstance();
        auto signalKDocument = fairWind->getSignalKDocument();

        connect(signalKDocument, &SignalKDocument::created, this, &SignalKClient::onCreated);
        connect(signalKDocument, &SignalKDocument::updated, this, &SignalKClient::onUpdated);

        connect(&mWebSocket, &QWebSocket::connected, this, &SignalKClient::onConnected);
        connect(&mWebSocket, &QWebSocket::disconnected, this, &SignalKClient::onDisconnected);

        if (params.contains("url")) {
            mUrl = params["url"].toString();
        }

        if (params.contains("version")) {
            mVersion = params["version"].toString();
        }

        if (params.contains("label")) {
            mLabel = params["label"].toString();
        }

        if (params.contains("active")) {
            mActive = params["active"].toBool();
        }

        if (params.contains("debug")) {
            mDebug = params["debug"].toBool();
        }

        if (params.contains("restore")) {
            mRestore = params["restore"].toBool();
        }


        if (params.contains("username")) {
            mUsername = params["username"].toString();
        }

        if (params.contains("password")) {
            mUsername = params["password"].toString();
        }

        // Check if the self is set manually
        QString self;
        if (params.contains("self")) {
            self = params["self"].toString();
        }

        if (mActive) {

            mServer = signalkGet(mUrl);
            login();

            if (mRestore) {
                QJsonObject allSignalK = getAll();
                fairWind->getSignalKDocument()->insert("", allSignalK);
            }

            // Check if the self is defined
            if (!self.isEmpty()) {

                // Override the self definition
                signalKDocument->setSelf(self);
            }

            mWebSocket.open(QUrl(ws()));

        }
    }

/*
 * getNewInstance
 * Creates and returns a new instance of the client
 */
    fairwind::connections::IConnection *SignalKClient::getNewInstance() {
        return static_cast<IConnection *>(new SignalKClient());
    }

    QString SignalKClient::getClassName() const {
        return this->metaObject()->className();
    }

    void SignalKClient::setActive(bool active) {
        mActive = active;
    }

    bool SignalKClient::isActive() const {
        return mActive;
    }

/*
 * getSelf
 * Returns the self key
 */
    QString SignalKClient::getSelf() {
        auto result = httpGet(http()+"self");
        qDebug() << "SignalKClient::getSelf :" << result;
        return result.replace("\"","");
    }

    QJsonObject SignalKClient::getAll() {
        return signalkGet(http());
    }


/*
 * setName
 * Sets the client's name
 */
    QString SignalKClient::getName() const {
        return tr("Signal K Client");
    }

/*
 * setLabel
 * Sets the client's label
 */
    void SignalKClient::setLabel(QString label) {
        mLabel = label;
    }

/*
 * getLabel
 * Returns the client's label
 */
    QString SignalKClient::getLabel() const {
        return mLabel;
    }

    void SignalKClient::onCreated(const QString &path, const QJsonValue &newValue) {
        QString processedPath = path;
        processedPath = processedPath.replace(".","/");
        signalkPost(http()+processedPath,newValue.toObject());
    }

    void SignalKClient::onUpdated(const QString &path, const QJsonValue &newValue) {
        QString processedPath = path;
        processedPath = processedPath.replace(".","/");
        signalkPut(http()+processedPath,newValue.toObject());
    }

    QJsonObject SignalKClient::signalkGet(QString url) {
        auto data = httpGet(url);
        return QJsonDocument::fromJson(data).object();
    }

    QJsonObject SignalKClient::signalkPut(QString url, QJsonObject payload) {
        if (!mToken.isEmpty()) {
            payload["token"] = mToken;
        }
        qDebug() << "SignalKClient::signalkPut payload: " << payload;
        auto data = httpPut(url,payload);
        return QJsonDocument::fromJson(data).object();
    }

    QJsonObject SignalKClient::signalkPost(QString url, QJsonObject payload) {
        if (!mToken.isEmpty()) {
            payload["token"] = mToken;
        }
        qDebug() << "SignalKClient::signalkPost payload: " << payload;
        auto data = httpPost(url, payload);
        return QJsonDocument::fromJson(data).object();
    }

    /*
 * httpGet
 * Executes a http get request
 */
    QByteArray SignalKClient::httpGet(QString url) {
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "application/json");

        if (!mCookie.isEmpty()) {
            req.setRawHeader("Cookie", mCookie.toLatin1());
        }

        QScopedPointer<QNetworkReply> reply(manager.get(req));

        QTime timeout = QTime::currentTime().addSecs(10);
        while (QTime::currentTime() < timeout && !reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Failure" << reply->errorString();
        }
        QByteArray data = reply->readAll();
        return data;
    }

    /*
 * httpPost
 * Executes a http post request
 */
    QByteArray SignalKClient::httpPost(QString url, QJsonObject payload) {

        QJsonDocument jsonDocument;
        jsonDocument.setObject(payload);

        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "application/json");

        if (!mCookie.isEmpty()) {
            req.setRawHeader("Cookie", mCookie.toLatin1());
            qDebug() << "SignalKClient::httpPost cookie: " << mCookie.toLatin1();
        }

        QScopedPointer<QNetworkReply> reply(manager.post(req, jsonDocument.toJson()));

        QTime timeout = QTime::currentTime().addSecs(10);
        while (QTime::currentTime() < timeout && !reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Failure" << reply->errorString();
        }
        QByteArray data = reply->readAll();

        auto cookie = reply->rawHeader("Set-Cookie");
        if (cookie!= nullptr && cookie.size()>0) {
            mCookie = cookie;
            qDebug() << "mCookie: " <<mCookie;
        }
        /*
        QList<QByteArray> headerList = reply->rawHeaderList();
                foreach(QByteArray head, headerList) {
                qDebug() << head << ":" << reply->rawHeader(head);
            }
        */

        return data;
    }

    /*
 * httpPost
 * Executes a http post request
 */
    QByteArray SignalKClient::httpPut(QString url, QJsonObject payload) {

        QJsonDocument jsonDocument;
        jsonDocument.setObject(payload);

        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "application/json");

        if (!mCookie.isEmpty()) {
            req.setRawHeader("Cookie", mCookie.toLatin1());
        }

        QScopedPointer<QNetworkReply> reply(manager.put(req, jsonDocument.toJson()));

        QTime timeout = QTime::currentTime().addSecs(10);
        while (QTime::currentTime() < timeout && !reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Failure" << reply->errorString();
        }
        QByteArray data = reply->readAll();
        return data;
    }

    bool SignalKClient::login() {
        bool result = false;
        QJsonObject payload;
        payload["username"] = mUsername;
        payload["password"] = mPassword;
        QJsonObject data = signalkPost(mUrl + "/" + mVersion + "/auth/login", payload);
        qDebug() << "SignalKClient::login : " << data;

        if (data.contains("token") && data["token"].isString()) {
            mToken = data["token"].toString();
            qDebug() << "SignalKClient::login token: " << mToken;
            result = true;
        } else if (data.contains("message") && data["message"].isString() ){
            qDebug() << data["message"].toString();
        }

        return result;
    }

/*
        {
 "endpoints": {
   "v1": {
     "version": "1.41.3",
     "signalk-http": "http://localhost:3000/signalk/v1/api/",
     "signalk-ws": "ws://localhost:3000/signalk/v1/stream",
     "signalk-tcp": "tcp://localhost:8375"
   }
 },
 "server": {
   "id": "signalk-server-node",
   "version": "1.41.3"
 }
}

        */

    QString SignalKClient::http() {
        return getEndpointByProtocol("http");
    }

    QString SignalKClient::ws() {
        return getEndpointByProtocol("ws");
    }

    QString SignalKClient::tcp() {
        return getEndpointByProtocol("tcp");
    }

    QString SignalKClient::getEndpointByProtocol(const QString &protocol) {
        if (mServer.contains("endpoints") & mServer["endpoints"].isObject()) {
            auto jsonObjectEndponts = mServer["endpoints"].toObject();
            if (jsonObjectEndponts.contains(mVersion) && jsonObjectEndponts[mVersion].isObject()) {
                auto jsonObjectVersion = jsonObjectEndponts[mVersion].toObject();
                if (jsonObjectVersion.contains("signalk-" + protocol) &&
                    jsonObjectVersion["signalk-" + protocol].isString()) {
                    return jsonObjectVersion["signalk-" + protocol].toString();
                }
            }
        }
        return {};
    }

//! [onConnected]
    void SignalKClient::onConnected() {
        if (mDebug)
            qDebug() << "WebSocket connected";
        connect(&mWebSocket, &QWebSocket::textMessageReceived,
                this, &SignalKClient::onTextMessageReceived);

    }
//! [onConnected]

//! [onDisconnected]
    void SignalKClient::onDisconnected() {
        if (mDebug)
            qDebug() << "WebSocket disconnected";
    }
//! [onDisconnected]

//! [onTextMessageReceived]
    void SignalKClient::onTextMessageReceived(QString message) {
        QJsonObject jsonObjectUpdate;

        QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8());

        // check validity of the document
        if (!jsonDocument.isNull()) {
            if (jsonDocument.isObject()) {
                jsonObjectUpdate = jsonDocument.object();
            }
        }

        //if (m_debug)
        //    qDebug() << "Update received:" << message;

        auto fairWind = fairwind::FairWind::getInstance();
        fairWind->getSignalKDocument()->update(jsonObjectUpdate);

    }
//! [onTextMessageReceived]
}