//
// Created by Raffaele Montella on 31/05/21.
//


#include "ui_DisplayGauge.h"
#include <FairWindSdk/displays/DisplayGauge.hpp>


fairwind::displays::DisplayGauge::DisplayGauge(QWidget *parent):
        QWidget(parent),
        ui(new Ui::DisplayGauge) {

    ui->setupUi(this);

    mGaugeWidget = new QcGaugeWidget;
    mGaugeWidget->addArc(55);
    mGaugeWidget->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand = mGaugeWidget->addColorBand(50);
    clrBand->setValueRange(0,100);
    mGaugeWidget->addValues(80)->setValueRange(0,100);
    mLabel=mGaugeWidget->addLabel(70);
    mLabel->setText("");
    QcLabelItem *lab = mGaugeWidget->addLabel(40);
    lab->setText("0");
    mNeedle = mGaugeWidget->addNeedle(60);
    mNeedle->setLabel(lab);
    mNeedle->setColor(Qt::blue);
    mNeedle->setValueRange(0,100);
    mGaugeWidget->addBackground(7);

    ui->horizontalLayout->addWidget(mGaugeWidget);
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
    //qDebug() << "DisplaySingleText::onInit(" << params << ")";
}

fairwind::displays::IFairWindDisplay *fairwind::displays::DisplayGauge::getNewInstance() {
    return static_cast<IFairWindDisplay *>(new DisplayGauge());
}

QString fairwind::displays::DisplayGauge::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplayGauge::smaller() { return isVisible(); }
bool fairwind::displays::DisplayGauge::bigger() { return isVisible(); }