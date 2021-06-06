//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>


fairwind::displays::DisplaySingleText::DisplaySingleText(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplaySingleText) {
    ui->setupUi(this);


    int size= contentsRect().height();

    QFont newFontLabel("Arial",size*0.25);
    ui->label_Label->setFont(newFontLabel);

    QFont newFontUnits("Arial",size*0.25);
    ui->label_Units->setFont(newFontUnits);

    QFont newFontValue("Arial",size*0.75);
    ui->label_Value1->setFont(newFontValue);

}

fairwind::displays::DisplaySingleText::~DisplaySingleText() {
    delete ui;
}

QImage fairwind::displays::DisplaySingleText::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplaySingleText::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplaySingleText::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }

    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    if (params.contains("units")) {
        setUnits(params["units"].toString());
    }
    if (params.contains("text")) {
        setText(params["text"].toString());
    }
}

fairwind::displays::IFairWindDisplay *fairwind::displays::DisplaySingleText::getNewInstance() {
    return static_cast<IFairWindDisplay *>(new fairwind::displays::DisplaySingleText());
}

void fairwind::displays::DisplaySingleText::setLabel(QString label) {
    ui->label_Label->setText(label);
}

void fairwind::displays::DisplaySingleText::setUnits(QString units) {
    ui->label_Units->setText(units);
}

void fairwind::displays::DisplaySingleText::setText(QString text) {
    ui->label_Value1->setText(text);
}

void fairwind::displays::DisplaySingleText::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
            this,SLOT(DisplaySingleText::update));
}

void fairwind::displays::DisplaySingleText::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;

    DisplayBase::update(update);
}



QString fairwind::displays::DisplaySingleText::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplaySingleText::smaller() {
    ui->label_Label->setFont(QFont("Arial",ui->label_Label->font().pixelSize()-1));
    ui->label_Units->setFont(QFont("Arial",ui->label_Units->font().pixelSize()-1));
    ui->label_Value1->setFont(QFont("Arial",ui->label_Value1->font().pixelSize()-1));
    return isVisible();
}

bool fairwind::displays::DisplaySingleText::bigger() {
    ui->label_Label->setFont(QFont("Arial",ui->label_Label->font().pixelSize()+1));
    ui->label_Units->setFont(QFont("Arial",ui->label_Units->font().pixelSize()+1));
    ui->label_Value1->setFont(QFont("Arial",ui->label_Value1->font().pixelSize()+1));
    return isVisible();
}