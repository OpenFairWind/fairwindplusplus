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
    _currentValue=0;
    _precision = 1;
    _shortStep= 10;
    _longStep = 50;
}
void fairwind::displays::DisplayBarGauge::onInit(QMap<QString, QVariant> params) {

    qDebug() << "fairwind::displays::DisplayBarGauge::onInit: " << params;
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
        _longStep = (float)params["longStep"].toDouble();
    }
// Create the Bargauge widget
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

    float h = this->height();
    float labelHeight = h*0.15;

    hLayout = new QHBoxLayout();

    mLabel=new QLabel();
    mLabel->setMaximumHeight(labelHeight);
    mLabel->setAlignment(Qt::AlignLeft);
    mLabel->setStyleSheet("QLabel {color: darkGrey;}");

    mValue = new QLabel();
    mValue->setMaximumHeight(labelHeight);
    mValue->setAlignment(Qt::AlignCenter);
    mValue->setStyleSheet("QLabel {color: darkGrey;}");

    mUnits = new QLabel();
    mUnits->setMaximumHeight(labelHeight);
    mUnits->setAlignment(Qt::AlignLeft);
    mUnits->setStyleSheet("QLabel {color: darkGrey;}");

    // Setup parameters

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

    ui->verticalLayout->addWidget(vbar);
    hLayout->addWidget(mLabel);
    hLayout->addWidget(mValue);
    hLayout->addWidget(mUnits);
    ui->verticalLayout->addLayout(hLayout);


    //ui->verticalLayout->addWidget(mLabel);
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
    mValue->setText(text);
    double value=text.toDouble();
    vbar->setCurrentValue(value);
}