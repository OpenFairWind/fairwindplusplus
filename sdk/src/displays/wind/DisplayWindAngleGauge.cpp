//
// Created by Raffaele Montella on 09/06/21.
//

#include "ui_DisplayWindAngleGauge.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>

#include "FairWindSdk/displays/DisplayWindAngleGauge.hpp"

/*
 * DisplayWindAngleGauge - Public Constructor
 */
fairwind::displays::DisplayWindAngleGauge::DisplayWindAngleGauge(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayWindAngleGauge) {
    // Setup the UI
    ui->setupUi(this);

    mMinValue = -180;
    mMaxValue = 180;
    mStep = 15;
}

/*
 * ~DisplayWindAngleGauge - Destructor
 */
fairwind::displays::DisplayWindAngleGauge::~DisplayWindAngleGauge() {}

/*
 * getIcon
 * Returns the display's icon
 */
QImage fairwind::displays::DisplayWindAngleGauge::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

/*
 * onSettings
 * Returns the display's settings
 */
QWidget *fairwind::displays::DisplayWindAngleGauge::onSettings() {
    return nullptr;
}

/*
 * onInit
 * Initialization method
 */
void fairwind::displays::DisplayWindAngleGauge::onInit(QMap <QString, QVariant> params) {
    qDebug() << "fairwind::displays::DisplayWindAngleGauge:onInit " << params;

    // Setup parameters
    QString context = "${self}";
    if (params.contains("context")) {
        context = params["context"].toString();
    }

    // Create the gauge widget
    mGaugeWidget = new QcGaugeWidget;

    // Add an arc
    QcArcItem *arcItem = mGaugeWidget->addArc(55);
    arcItem->setValueRange(mMinValue, mMaxValue);
    arcItem->setDegreeRange(mMinValue, mMaxValue);

    // Add a degree component
    QcDegreesItem *degreesItem = mGaugeWidget->addDegrees(65);
    degreesItem->setValueRange(mMinValue, mMaxValue);
    degreesItem->setDegreeRange(mMinValue, mMaxValue);
    degreesItem->setDegreeOffset(90);
    degreesItem->setStep(10);
    degreesItem->setSubDegree(true);

    QcColorBand *clrBandPort = mGaugeWidget->addColorBand(50);
    clrBandPort->setValueRange(-60, -20);
    clrBandPort->setDegreeRange(-60, -20);
    clrBandPort->setDegreeOffset(90);
    QList <QPair<QColor, float>> colorsPort;
    colorsPort.append(QPair<QColor, float>(Qt::darkRed, -60));
    colorsPort.append(QPair<QColor, float>(Qt::darkRed, -20));
    clrBandPort->setColors(colorsPort);

    QcColorBand *clrBandStarboard = mGaugeWidget->addColorBand(50);
    clrBandStarboard->setValueRange(20, 60);
    clrBandStarboard->setDegreeRange(20, 60);
    clrBandStarboard->setDegreeOffset(90);
    QList <QPair<QColor, float>> colorsStarboard;
    colorsStarboard.append(QPair<QColor, float>(Qt::darkGreen, 20));
    colorsStarboard.append(QPair<QColor, float>(Qt::darkGreen, 60));
    clrBandStarboard->setColors(colorsStarboard);

    QcValuesItem *valuesItem = mGaugeWidget->addValues(80);
    valuesItem->setValueRange(-150, 150);
    valuesItem->setDegreeRange(-150, 150);
    valuesItem->setDegreeOffset(90);
    valuesItem->setStep(30);

    mLabel = mGaugeWidget->addLabel(70);

    mUnits = mGaugeWidget->addLabel(50);

    mValue = mGaugeWidget->addLabel(40);

    mNeedle = mGaugeWidget->addNeedle(60);
    mNeedle->setLabel(mValue);
    mNeedle->setColor(Qt::blue);
    mNeedle->setValueRange(mMinValue, mMaxValue);
    mNeedle->setDegreeRange(mMinValue, mMaxValue);
    mNeedle->setDegreeOffset(90);

    mGaugeWidget->addBackground(7);

    // Subscribe the get wind information
    subscribe(context + ".environment.wind.angleApparent");

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

/*
bool fairwind::displays::DisplayWindAngleGauge::smaller() { return isVisible(); }
bool fairwind::displays::DisplayWindAngleGauge::bigger() { return isVisible(); }
*/

void fairwind::displays::DisplayWindAngleGauge::setLabel(QString label) {
    mLabel->setText(label);
}

void fairwind::displays::DisplayWindAngleGauge::setUnits(QString units) {
    mUnits->setText(units);
}

void fairwind::displays::DisplayWindAngleGauge::setValue(QString text) {
    mValue->setText(text);
    double value = text.toDouble();
    mNeedle->setCurrentValue(value);
}

void fairwind::displays::DisplayWindAngleGauge::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);
    setToolTip(getDescription());
    signalKDocument->subscribe(getFullPath(),
                               this, SLOT(DisplayWindAngleGauge::update));
}

void fairwind::displays::DisplayWindAngleGauge::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;

    DisplayBase::update(update);
}