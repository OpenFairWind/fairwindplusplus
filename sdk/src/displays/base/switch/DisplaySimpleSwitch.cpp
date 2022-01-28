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
    setMaximumWidth(500);
    ui->labelSimpleSwitch->setFixedWidth(200);
}
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
    sbtn = new SwitchButton();
    sbtn->setFixedWidth(200);
    connect(sbtn, &SwitchButton::onClick, this, &DisplaySimpleSwitch::slotOnClick);
    sbtn->setIcons(":resources/images/switches/simple_switch_on.png",":resources/images/switches/simple_switch_off.png");

    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }
    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    ui->layoutFrameS->addWidget(sbtn);
}
fairwind::displays::IDisplay *fairwind::displays::DisplaySimpleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplaySimpleSwitch());
}
void fairwind::displays::DisplaySimpleSwitch::setLabel(QString label) {
    ui->labelSimpleSwitch->setText(label);
}
void fairwind::displays::DisplaySimpleSwitch::setUnits(QString units) {

}
void fairwind::displays::DisplaySimpleSwitch::setValue(QString value){
    qDebug()<<"DisplaySimpleSwitch::setValue "<<value;
    sbtn->setStatus(value.contains("on") ? true : false);
}

void fairwind::displays::DisplaySimpleSwitch::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplaySimpleSwitch::update));
}

void fairwind::displays::DisplaySimpleSwitch::update(const QJsonObject update) {
    qDebug() << "DisplaySimpleSwitch::update:" << update.value("value");

    DisplayBase::update(update);
}

QString fairwind::displays::DisplaySimpleSwitch::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::displays::DisplaySimpleSwitch::slotOnClick(bool status)
{
    qDebug("DisplaySimpleSwitch::slotOnClick ");
    QJsonValue valueToPut = !status ? "on" : "off";
    qDebug() << "valueToPut " << valueToPut<<"status"<<status;

    auto path = DisplayBase::getFullPath();
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    signalKDocument->insert(path,valueToPut);
}
