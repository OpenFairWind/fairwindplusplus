//
// Created by Raffaele Montella on 31/05/21.
//


#include "ui_DisplayGauge.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplayGauge.hpp>

fairwind::displays::DisplayGauge::DisplayGauge(QWidget *parent):
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayGauge) {

    ui->setupUi(this);
}

fairwind::displays::DisplayGauge::~DisplayGauge() {
    delete ui;
}

QImage fairwind::displays::DisplayGauge::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplayGauge::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplayGauge::onInit(QMap<QString, QVariant> params) {

    // Create the gauge widget
    mGaugeWidget = new QcGaugeWidget;

    float minValue=0;
    float maxValue=16;
    float step=1;

    // Add an arc
    QcArcItem *arcItem=mGaugeWidget->addArc(55);
    arcItem->setColor(Qt::white);

    QcDegreesItem *degreesItem=mGaugeWidget->addDegrees(65);
    degreesItem->setColor(Qt::white);
    degreesItem->setValueRange(minValue,maxValue);
    degreesItem->setStep(step);
    degreesItem->setSubDegree(true);

    //QcColorBand *clrBand = mGaugeWidget->addColorBand(50);
    //clrBand->setValueRange(minValue,maxValue);

    QcValuesItem *valuesItem=mGaugeWidget->addValues(80);
    valuesItem->setValueRange(minValue,maxValue);
    valuesItem->setStep(1);
    valuesItem->setColor(Qt::white);

    mLabel=mGaugeWidget->addLabel(70);
    mLabel->setColor(Qt::white);

    mValue = mGaugeWidget->addLabel(40);
    mValue->setColor(Qt::white);

    mNeedle = mGaugeWidget->addNeedle(60);
    mNeedle->setLabel(mValue);
    mNeedle->setColor(Qt::blue);
    mNeedle->setValueRange(minValue,maxValue);

    mGaugeWidget->addBackground(7);

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
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }

    ui->horizontalLayout->addWidget(mGaugeWidget);
}

fairwind::displays::IFairWindDisplay *fairwind::displays::DisplayGauge::getNewInstance() {
    return static_cast<IFairWindDisplay *>(new DisplayGauge());
}

QString fairwind::displays::DisplayGauge::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplayGauge::smaller() { return isVisible(); }
bool fairwind::displays::DisplayGauge::bigger() { return isVisible(); }

void fairwind::displays::DisplayGauge::setLabel(QString label) {
    mLabel->setText(label);
}

void fairwind::displays::DisplayGauge::setUnits(QString units) {

}

void fairwind::displays::DisplayGauge::setValue(QString text) {
    mValue->setText(text);
    double value=text.toDouble();
    mNeedle->setCurrentValue(value);
}

void fairwind::displays::DisplayGauge::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);
    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplayGauge::update));
}

void fairwind::displays::DisplayGauge::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;

    DisplayBase::update(update);
}

