//
// Created by Raffaele Montella on 15/09/21.
//


#include "ui_DisplaySimpleSwitch.h"
#include "FairWind.hpp"

#include <QJsonArray>
#include <displays/DisplaySimpleSwitch.hpp>


/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
fairwind::displays::DisplaySimpleSwitch::DisplaySimpleSwitch(QWidget *parent) :
QWidget(parent),
DisplayBase(),
ui(new Ui::DisplaySimpleSwitch) {
    status = false;

    // Initialize the user interface
    ui->setupUi(this);

    setMaximumWidth(500);

    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onFinished(QNetworkReply *)));

}

/**
 * DisplaySingleText destructor
 */
fairwind::displays::DisplaySimpleSwitch::~DisplaySimpleSwitch() {
    delete ui;
}

QImage fairwind::displays::DisplaySimpleSwitch::getIcon() const {
    return QImage(":resources/images/icons/display_icon.png");
}

QWidget *fairwind::displays::DisplaySimpleSwitch::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplaySimpleSwitch::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    sbtn = new SwitchButton();
    connect(sbtn, &SwitchButton::onClick, this, &DisplaySimpleSwitch::slotOnClick);
    sbtn->setIcons(":resources/images/switches/simple_switch_on.png",":resources/images/switches/simple_switch_off.png");
    //sbtn->setStatus(true);

    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }
    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    ui->layoutFrameS->addWidget(sbtn);
}

fairwind::displays::IDisplay *fairwind::displays::DisplaySimpleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplaySimpleSwitch());
}

void fairwind::displays::DisplaySimpleSwitch::setLabel(QString label) {
    ui->labelSimpleSwitch->setText(label);
}

void fairwind::displays::DisplaySimpleSwitch::setUnits(QString units) {

}
void fairwind::displays::DisplaySimpleSwitch::setValue(QString value)
{
    qDebug()<<"DisplaySimpleSwitch::setValue "<<value;
    sbtn->setStatus(value.contains("on") ? true : false);
}

void fairwind::displays::DisplaySimpleSwitch::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplaySimpleSwitch::update));
}

void fairwind::displays::DisplaySimpleSwitch::update(const QJsonObject update) {
    //qDebug() << "DisplaySimpleSwitch::update:" << update;

    DisplayBase::update(update);
}

QString fairwind::displays::DisplaySimpleSwitch::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::displays::DisplaySimpleSwitch::slotOnClick(bool status)
{
    qDebug("DisplaySimpleSwitch::slotOnClick ");
 /*   auto valueToPut = !status ? "on" : "off";
    QByteArray data;
    QUrlQuery params;
    qDebug() << "valueToPut " << valueToPut<<"status"<<status;

    //auto path = DisplayBase::getFullPath();
   // params.addQueryItem("fullPath", DisplayBase::getFullPath());
    //params.addQueryItem("value", valueToPut);


    //data.append(params.toString().toUtf8());
    std::string d ="{ \" value\": 1.52, }";
    data.append(d.c_str());
    qDebug() << "data " << data << " "<<d.c_str();
    networkAccessManager->post(QNetworkRequest(QUrl("http://localhost:3000/signalk/v1/api/vessels/self/electrical/electrical/batteries/1/voltage")), data);
*/

    const QUrl url(QStringLiteral("http://localhost:3000/signalk/v1/api"));
    if(url.isValid())
    {
        qDebug()<<"Url valid";
    }
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto valueToPut = !status ? "on" : "off";
    auto path = DisplayBase::getFullPath();
/*
    QJsonObject obj;
    obj["requestId"] = "12345-23232-23232";
    obj["fullPath"] = path;
    obj["value"] = valueToPut;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    qDebug() << "data " << data;*/

// or "{  \"requestId\": \"123345-23232-232323\", \"put\": {  \"path\": \"electrical.switches.anchorLight.state\", \"value\": 1  } }"
    QByteArray data("{  \"requestId\": \"123345-23232-232323\", \"put\": {  \"path\": \"electrical.switches.anchorLight.state\", \"value\": 1  } }");
    qDebug() << "data " << data;
    QNetworkReply *reply = networkAccessManager->post(request, data);
    qDebug() << "dopo post ";
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug()<<"replyRead:" << contents;
        }
        else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
}

void fairwind::displays::DisplaySimpleSwitch::onFinished(QNetworkReply *r){
    qDebug("slot onFinished " );
    if(r->error() == QNetworkReply::NoError){
        QString contents = QString::fromUtf8(r->readAll());
        qDebug()<<"onFinisched Read:" << contents;
    }
}