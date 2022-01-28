//
// Created by filippo on 09/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DisplayToggleSwitch.h" resolved

#include "ui_DisplayToggleSwitch.h"
#include "FairWind.hpp"

#include <QJsonArray>
#include <displays/DisplayToggleSwitch.hpp>

fairwind::displays::DisplayToggleSwitch::DisplayToggleSwitch(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplayToggleSwitch) {

    ui->setupUi(this);
 }

fairwind::displays::DisplayToggleSwitch::~DisplayToggleSwitch() {
    delete ui;
}

void fairwind::displays::DisplayToggleSwitch::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }

    toggle = new ToggleButton(nullptr, ToggleButton::Style::EMPTY, false, Qt::darkRed);
    connect(toggle, &ToggleButton::onClick, this, &DisplayToggleSwitch::slotOnClick);

    if (params.contains("value")) {
        setValue(params["value"].toString());
    }
    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("description")) {
        setToolTip(params["description"].toString());
    }

    toggle->setMaximumWidth(80);
    ui->layoutFrameTS->addWidget(toggle);
}

QImage fairwind::displays::DisplayToggleSwitch::getIcon() const {
    return QImage(":resources/images/icons/display_icon.png");
}

QWidget *fairwind::displays::DisplayToggleSwitch::onSettings() {
    return nullptr;
}

fairwind::displays::IDisplay *fairwind::displays::DisplayToggleSwitch::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplayToggleSwitch());
}

void fairwind::displays::DisplayToggleSwitch::setLabel(QString label) {
    ui->labelToggleSwitch->setText(label);
}

void fairwind::displays::DisplayToggleSwitch::setUnits(QString units) {

}
void fairwind::displays::DisplayToggleSwitch::setValue(QString value) {
    qDebug()<<"DisplayToggleSwitch::setValue "<<value;
    toggle->setValue(value.contains(_on) ? true : false);
}

void fairwind::displays::DisplayToggleSwitch::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
                                this,SLOT(DisplayToggleSwitch::update));
}

void fairwind::displays::DisplayToggleSwitch::update(const QJsonObject update) {
    qDebug() << "DisplayToggleSwitch::update:" << update;
    DisplayBase::update(update);
}

QString fairwind::displays::DisplayToggleSwitch::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::displays::DisplayToggleSwitch::slotOnClick(bool status)
{
    qDebug("DisplayToggleSwitch::slotOnClick ");
    QJsonValue valueToPut = status ? _on : _off;
    //qDebug() << "DisplayToggleSwitch::valueToPut " << valueToPut<<"status"<<status;

    auto path = DisplayBase::getFullPath();
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    signalKDocument->insert(path,valueToPut);
}

