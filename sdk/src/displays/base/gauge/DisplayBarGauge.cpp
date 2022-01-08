//
// Created by filippo on 08/01/22.
//

#include "ui_DisplayBarGauge.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplayBarGauge.hpp>

fairwind::displays::DisplayBarGauge::DisplayBarGauge(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayBarGauge) {

    ui->setupUi(this);
   // _minValue= 0;
  //  _maxValue=10;
    _currentValue=0;
    _precision = 1;
    _shortStep= 1;
    _longStep = 10;
}
void fairwind::displays::DisplayBarGauge::onInit(QMap<QString, QVariant> params) {

    qDebug() << "fairwind::displays::DisplayBarGauge::onInit: " << params;

    // Setup parameters
    if (params.contains("minValue")) {
        _minValue = (float)params["minValue"].toDouble();
    }

    if (params.contains("maxValue")) {
        _maxValue = (float)params["maxValue"].toDouble();
    }
    if (params.contains("shortStep")) {
        _shortStep = (float)params["shortStep"].toDouble();
    }
    if (params.contains("longStep")) {
        _longStep = (float)params["longtStep"].toDouble();
    }
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

    // Create the gauge widget
    vbar = new QcBar;
    vbar->setDirection(QcBar::DirectionEnum::Vertical);
    vbar->setBgColor(Qt::darkGray);
    vbar->setProgressColor(Qt::darkBlue);
    vbar->setLineColor(Qt::white);
    vbar->setRange(_minValue,_maxValue);
    vbar->setCurrentValue(_currentValue);
    vbar->setPrecision(_precision);
    vbar->setShortStep(_shortStep);
    vbar->setLongStep(_longStep);
    vbar->setRulerRight(true);
    vbar->setRulerLeft(true);
    //vbar->setMargin(0);
    //vbar->setSpacing(1);
    float h = this->height();
    float labelHeight = h*0.10;

    mLabel=new QLabel();
    mLabel->setMaximumHeight(labelHeight);
    mLabel->setAlignment(Qt::AlignCenter);
    mLabel->setStyleSheet("QLabel {color: darkGrey;}");
    mLabel->setText("%");

    ui->verticalLayout->addWidget(vbar);
    ui->verticalLayout->addWidget(mLabel);

}

fairwind::displays::DisplayBarGauge::~DisplayBarGauge() {
    delete ui;
}

QImage fairwind::displays::DisplayBarGauge::getIcon() const {
    return QImage(":resources/images/icons/display_gauge_icon.png");
}

QWidget *fairwind::displays::DisplayBarGauge::onSettings() {
    return nullptr;
}

fairwind::displays::IDisplay *fairwind::displays::DisplayBarGauge::getNewInstance() {
    return static_cast<IDisplay *>(new DisplayBarGauge());
}

QString fairwind::displays::DisplayBarGauge::getClassName() const {
    return this->metaObject()->className();
}
void fairwind::displays::DisplayBarGauge::update(const QJsonObject update) {

    DisplayBase::update(update);
}
void fairwind::displays::DisplayBarGauge::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);
    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplayBarGauge::update));
}

void fairwind::displays::DisplayBarGauge::setLabel(QString label) {
    mLabel->setText(label);
}

void fairwind::displays::DisplayBarGauge::setUnits(QString units) {
    mUnits->setText(units);
}

void fairwind::displays::DisplayBarGauge::setValue(QString text) {
    double value=text.toDouble();
    mLabel->setText(QString::number(value)+ "%");
    vbar->setCurrentValue(value);

}