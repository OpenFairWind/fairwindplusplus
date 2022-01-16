//
// Created by filippo on 09/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DisplayToggleSwitch.h" resolved

#include "ui_DisplayToggleSwitch.h"
#include "FairWind.hpp"

#include <QJsonArray>
#include <displays/DisplayToggleSwitch.hpp>

fairwind::displays::DisplayToggleSwitch::DisplayToggleSwitch(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayToggleSwitch) {

    ui->setupUi(this);
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onFinished(QNetworkReply *)));

}

fairwind::displays::DisplayToggleSwitch::~DisplayToggleSwitch() {
    delete ui;
}

void fairwind::displays::DisplayToggleSwitch::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }

    toggle = new ToggleButton(nullptr, ToggleButton::Style::EMPTY, false, Qt::darkRed);

    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    toggle->setMaximumWidth(80);
    ui->layoutFrameTS->addWidget(toggle);
}

QImage fairwind::displays::DisplayToggleSwitch::getIcon() const {
    return QImage(":resources/images/icons/display_icon.png");
}

QWidget *fairwind::displays::DisplayToggleSwitch::onSettings() {
    return nullptr;
}

fairwind::displays::IDisplay *fairwind::displays::DisplayToggleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplayToggleSwitch());
}

void fairwind::displays::DisplayToggleSwitch::setLabel(QString label) {
    ui->labelToggleSwitch->setText(label);
}

void fairwind::displays::DisplayToggleSwitch::setUnits(QString units) {

}
void fairwind::displays::DisplayToggleSwitch::setValue(QString value) {
    //ui->label_Value1->setText(value);
 /*   if (value.contains("on")) {
        status=true;
    } else {
        status=false;
    }

    updateStatus();*/
    qDebug()<<"DisplaySimpleSwitch::setValue "<<value;
    //toggle->setStatus(value.contains("on") ? true : false);
}

void fairwind::displays::DisplayToggleSwitch::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplayToggleSwitch::update));
}

void fairwind::displays::DisplayToggleSwitch::update(const QJsonObject update) {
    //qDebug() << "DisplaySimpleSwitch::update:" << update;

    DisplayBase::update(update);
}

QString fairwind::displays::DisplayToggleSwitch::getClassName() const {
    return this->metaObject()->className();
}


void fairwind::displays::DisplayToggleSwitch::slotOnClick(bool status)
{
    qDebug("DisplayToggleSwitch::slotOnClick ");
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

void fairwind::displays::DisplayToggleSwitch::onFinished(QNetworkReply *r){
    qDebug("slot onFinished " );
    if(r->error() == QNetworkReply::NoError){
        QString contents = QString::fromUtf8(r->readAll());
        qDebug()<<"onFinisched Read:" << contents;
    }
}

