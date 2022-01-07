//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>

/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
fairwind::displays::DisplaySingleText::DisplaySingleText(QWidget *parent) :
        QWidget(parent),
        DisplayBase(),
        ui(new Ui::DisplaySingleText) {

    // Initialize the user interface
    ui->setupUi(this);

    // Get the display height
    int size= contentsRect().height();

    // Calculate the label font size
    QFont newFontLabel("Arial",size*0.25);

    // Set the label font size
    ui->label_Label->setFont(newFontLabel);

    // Calculate the units font side
    QFont newFontUnits("Arial",size*0.25);

    // Set the units font size
    ui->label_Units->setFont(newFontUnits);

    // Calculate the value font size
    QFont newFontValue("Arial",size*0.75);

    // Set the value font size
    ui->label_Value1->setFont(newFontValue);

}

/**
 * DisplaySingleText destructor
 */
fairwind::displays::DisplaySingleText::~DisplaySingleText() {
    delete ui;
}

QImage fairwind::displays::DisplaySingleText::getIcon() const {
    return QImage(":resources/images/icons/display_simpletext_icon.png");
}

QWidget *fairwind::displays::DisplaySingleText::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplaySingleText::onInit(QMap<QString, QVariant> params) {
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

    if (params.contains("units")) {
        setUnits(params["units"].toString());
    }
    if (params.contains("value")) {
        setValue(params["value"].toString());
    }
}

fairwind::displays::IDisplay *fairwind::displays::DisplaySingleText::getNewInstance() {
    return static_cast<IDisplay *>(new fairwind::displays::DisplaySingleText());
}

void fairwind::displays::DisplaySingleText::setLabel(QString label) {
    ui->label_Label->setText(label);
}

void fairwind::displays::DisplaySingleText::setUnits(QString units) {
    ui->label_Units->setText(units);
}

void fairwind::displays::DisplaySingleText::setValue(QString value) {
    ui->label_Value1->setText(value);
}

void fairwind::displays::DisplaySingleText::subscribe(QString fullPath) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    DisplayBase::subscribe(fullPath);

    setToolTip(getDescription());
    signalKDocument->subscribe( getFullPath(),
            this,SLOT(DisplaySingleText::update));
}

void fairwind::displays::DisplaySingleText::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;

    DisplayBase::update(update);
}



QString fairwind::displays::DisplaySingleText::getClassName() const {
    return this->metaObject()->className();
}
