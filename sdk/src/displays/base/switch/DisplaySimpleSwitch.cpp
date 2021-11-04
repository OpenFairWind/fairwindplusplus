//
// Created by Raffaele Montella on 15/09/21.
//

#include "FairWindSdk/displays/DisplaySimpleSwitch.hpp"

#include "ui_DisplaySimpleSwitch.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySimpleSwitch.hpp>

/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
fairwind::displays::DisplaySimpleSwitch::DisplaySimpleSwitch(QWidget *parent) :
QWidget(parent),
DisplayBase(),
ui(new Ui::DisplaySimpleSwitch) {

    // Initialize the user interface
    ui->setupUi(this);



}

/**
 * DisplaySingleText destructor
 */
fairwind::displays::DisplaySimpleSwitch::~DisplaySimpleSwitch() {
    delete ui;
}

QImage fairwind::displays::DisplaySimpleSwitch::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplaySimpleSwitch::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplaySimpleSwitch::onInit(QMap<QString, QVariant> params) {
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

fairwind::displays::IDisplay *fairwind::displays::DisplaySimpleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplaySimpleSwitch());
}

void fairwind::displays::DisplaySimpleSwitch::setLabel(QString label) {
    ui->switchLabel->setText(label);
}

void fairwind::displays::DisplaySimpleSwitch::setUnits(QString units) {
    //ui->label_Units->setText(units);
}

void fairwind::displays::DisplaySimpleSwitch::setValue(QString value) {
    //ui->label_Value1->setText(value);
}

void fairwind::displays::DisplaySimpleSwitch::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplaySingleText::update));
}

void fairwind::displays::DisplaySimpleSwitch::update(const QJsonObject update) {
    //qDebug() << "DisplaySimpleSwitch::update:" << update;

    DisplayBase::update(update);
}



QString fairwind::displays::DisplaySimpleSwitch::getClassName() const {
    return this->metaObject()->className();
}