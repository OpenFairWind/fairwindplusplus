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

    mGaugeWidget = new QcGaugeWidget;
    mGaugeWidget->addArc(55);
    mGaugeWidget->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand = mGaugeWidget->addColorBand(50);
    clrBand->setValueRange(0,100);
    mGaugeWidget->addValues(80)->setValueRange(0,100);
    mLabel=mGaugeWidget->addLabel(70);

    QcLabelItem *lab = mGaugeWidget->addLabel(40);
    lab->setText("0");
    mNeedle = mGaugeWidget->addNeedle(60);
    mNeedle->setLabel(lab);
    mNeedle->setColor(Qt::blue);
    mNeedle->setValueRange(0,100);
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
    if (params.contains("text")) {
        setText(params["text"].toString());
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

void fairwind::displays::DisplayGauge::setText(QString text) {

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

