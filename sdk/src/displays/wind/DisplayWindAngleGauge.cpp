//
// Created by Raffaele Montella on 09/06/21.
//

#include "ui_DisplayWindAngleGauge.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>

#include "FairWindSdk/displays/DisplayWindAngleGauge.hpp"

fairwind::displays::DisplayWindAngleGauge::DisplayWindAngleGauge(QWidget *parent):
    QWidget(parent),
    DisplayBase(),
    ui(new Ui::DisplayWindAngleGauge) {

    ui->setupUi(this);

    mMinValue=-180;
    mMaxValue=180;
    mStep=15;
}

fairwind::displays::DisplayWindAngleGauge::~DisplayWindAngleGauge() {

}

QImage fairwind::displays::DisplayWindAngleGauge::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplayWindAngleGauge::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplayWindAngleGauge::onInit(QMap<QString, QVariant> params) {

    qDebug() << "fairwind::displays::DisplayWindAngleGauge:onInit " << params;

    // Setup parameters
    QString context="${self}";
    if (params.contains("context")) {
        context = params["context"].toString();
    }

    // Create the gauge widget
    mGaugeWidget = new QcGaugeWidget;



    // Add an arc
    QcArcItem *arcItem=mGaugeWidget->addArc(55);
    //arcItem->setValueRange(mMinValue,mMaxValue);
    arcItem->setDgereeRange(mMinValue,mMaxValue);

    /*
    QcDegreesItem *degreesItem=mGaugeWidget->addDegrees(65);
    degreesItem->setValueRange(mMinValue,mMaxValue);
    degreesItem->setDgereeRange(mMinValue,mMaxValue);
    degreesItem->setStep(mStep);
    degreesItem->setSubDegree(true);
    */

    /*
    QcColorBand *clrBandPort = mGaugeWidget->addColorBand(50);
    clrBandPort->setValueRange(mMinValue, 0);
    clrBandPort->setDgereeRange(mMinValue,0);
    //clrBandPort->setColors(colorsLeft);

    QcColorBand *clrBandStarboard= mGaugeWidget->addColorBand(50);
    clrBandStarboard->setValueRange(mMinValue, 0);
    clrBandStarboard->setDgereeRange(0,mMaxValue);
    //clrBandStarboard->setColors(colorsLeft);
    */

    QcValuesItem *valuesItem=mGaugeWidget->addValues(80);
    valuesItem->setValueRange(mMinValue,mMaxValue);
    valuesItem->setDgereeRange(mMinValue,mMaxValue);
    valuesItem->setStep(mStep);

    mLabel=mGaugeWidget->addLabel(70);

    mUnits=mGaugeWidget->addLabel(50);

    mValue = mGaugeWidget->addLabel(40);

    mNeedle = mGaugeWidget->addNeedle(60);
    mNeedle->setLabel(mValue);
    mNeedle->setColor(Qt::blue);
    mNeedle->setValueRange(mMinValue,mMaxValue);
    //mNeedle->setDgereeRange(mMinValue,mMaxValue);

    mGaugeWidget->addBackground(7);

    subscribe(context+".environment.wind.angleApparent");

    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }

    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    if (params.contains("units")) {
        setUnits(params["units"].toString());
    }
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }

    ui->horizontalLayout->addWidget(mGaugeWidget);
}

fairwind::displays::IDisplay *fairwind::displays::DisplayWindAngleGauge::getNewInstance() {
    return static_cast<IDisplay *>(new DisplayWindAngleGauge());
}

QString fairwind::displays::DisplayWindAngleGauge::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplayWindAngleGauge::smaller() { return isVisible(); }
bool fairwind::displays::DisplayWindAngleGauge::bigger() { return isVisible(); }

void fairwind::displays::DisplayWindAngleGauge::setLabel(QString label) {
    mLabel->setText(label);
}

void fairwind::displays::DisplayWindAngleGauge::setUnits(QString units) {
    mUnits->setText(units);
}

void fairwind::displays::DisplayWindAngleGauge::setValue(QString text) {
    mValue->setText(text);
    double value=text.toDouble();
    mNeedle->setCurrentValue(value);
}

void fairwind::displays::DisplayWindAngleGauge::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);
    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplayWindAngleGauge::update));
}

void fairwind::displays::DisplayWindAngleGauge::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;

    DisplayBase::update(update);
}
