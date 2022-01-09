//
// Created by Raffaele Montella on 15/09/21.
//


#include "ui_DisplaySimpleSwitch.h"
#include "FairWind.hpp"

#include <QJsonArray>
#include <displays/DisplaySimpleSwitch.hpp>


/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
fairwind::displays::DisplaySimpleSwitch::DisplaySimpleSwitch(QWidget *parent) :
QWidget(parent),
DisplayBase(),
ui(new Ui::DisplaySimpleSwitch) {
    status = false;

    // Initialize the user interface
    ui->setupUi(this);
    //connect(ui->switchButton, &QPushButton::released, this, &DisplaySimpleSwitch::onRelease);
}

/**
 * DisplaySingleText destructor
 */
fairwind::displays::DisplaySimpleSwitch::~DisplaySimpleSwitch() {
    delete ui;
}

QImage fairwind::displays::DisplaySimpleSwitch::getIcon() const {
    return QImage(":resources/images/icons/display_icon.png");
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
    sbtn = new SwitchButton();
    sbtn->setStylesheet(":resources/images/switches/toggle_off.png",":resources/images/switches/toggle_on.png");

    ui->verticalLayout->addWidget(sbtn);
}

fairwind::displays::IDisplay *fairwind::displays::DisplaySimpleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplaySimpleSwitch());
}

void fairwind::displays::DisplaySimpleSwitch::setLabel(QString label) {
    //ui->labelGroupBox->setTitle(label);
}

void fairwind::displays::DisplaySimpleSwitch::setUnits(QString units) {
    //ui->label_Units->setText(units);
}

void fairwind::displays::DisplaySimpleSwitch::setValue(QString value) {
    //ui->label_Value1->setText(value);
    if (value.contains("on")) {
        status=true;
    } else {
        status=false;
    }

    updateStatus();
}


void fairwind::displays::DisplaySimpleSwitch::updateStatus() {
    if (status) {
       // ui->switchButton->setText("simpleswitch_on");
    } else {
       // ui->switchButton->setText("simpleswitch_off");
    }
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

void fairwind::displays::DisplaySimpleSwitch::onRelease() {
    status=!status;
    updateStatus();
}


