//
// Created by Raffaele Montella on 16/09/21.
//

#include "FairWindSdk/displays/DisplayVerticalBarGauge.hpp"

#include "ui_DisplayVerticalBarGauge.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplayVerticalBarGauge.hpp>

/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
fairwind::displays::DisplayVerticalBarGauge::DisplayVerticalBarGauge(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayVerticalBarGauge) {

    // Initialize the user interface
    ui->setupUi(this);



}

/**
 * DisplaySingleText destructor
 */
fairwind::displays::DisplayVerticalBarGauge::~DisplayVerticalBarGauge() {
    delete ui;
}

QImage fairwind::displays::DisplayVerticalBarGauge::getIcon() const {
    return QImage(":resources/images/icons/display_icon.png");
}

QWidget *fairwind::displays::DisplayVerticalBarGauge::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplayVerticalBarGauge::onInit(QMap<QString, QVariant> params) {
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

    if (params.contains("value")) {
        setValue(params["value"].toString());
    }
}

fairwind::displays::IDisplay *fairwind::displays::DisplayVerticalBarGauge::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplayVerticalBarGauge());
}

void fairwind::displays::DisplayVerticalBarGauge::setLabel(QString label) {
    ui->_valueLabel->setText(label);
}

void fairwind::displays::DisplayVerticalBarGauge::setUnits(QString units) {
    //ui->label_Units->setText(units);
}

void fairwind::displays::DisplayVerticalBarGauge::setValue(QString value) {
    //ui->label_Value1->setText(value);
}

void fairwind::displays::DisplayVerticalBarGauge::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplaySingleText::update));
}

void fairwind::displays::DisplayVerticalBarGauge::update(const QJsonObject update) {
    //qDebug() << "DisplayVerticalBarGauge::update:" << update;

    DisplayBase::update(update);
}



QString fairwind::displays::DisplayVerticalBarGauge::getClassName() const {
    return this->metaObject()->className();
}