//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>

namespace fairwind::displays {
/**
 * DisplaySingleText constructor
 * @param parent The parent widget
 */
    DisplaySingleText::DisplaySingleText(QWidget *parent) :
            QWidget(parent),
            DisplayBase(),
            ui(new Ui::DisplaySingleText) {

        // Initialize the user interface
        ui->setupUi(this);

        // Get the display height
        int size = contentsRect().height();

        // Calculate the label font size
        QFont newFontLabel("Arial", size * 0.25);

        // Set the label font size
        ui->label_Label->setFont(newFontLabel);

        // Calculate the units font side
        QFont newFontUnits("Arial", size * 0.25);

        // Set the units font size
        ui->label_Units->setFont(newFontUnits);

        // Calculate the value font size
        QFont newFontValue("Arial", size * 0.75);

        // Set the value font size
        ui->label_Value1->setFont(newFontValue);

    }

/**
 * DisplaySingleText destructor
 */
    DisplaySingleText::~DisplaySingleText() {
        delete ui;
    }

    QImage DisplaySingleText::getIcon() const {
        return QImage(":resources/images/icons/display_simpletext_icon.png");
    }

    QWidget *DisplaySingleText::onSettings() {
        return nullptr;
    }

    void DisplaySingleText::onInit(QMap<QString, QVariant> params) {
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

    IDisplay *DisplaySingleText::getNewInstance() {
        return static_cast<IDisplay *>(new DisplaySingleText());
    }

    void DisplaySingleText::setLabel(QString label) {
        ui->label_Label->setText(label);
    }

    void DisplaySingleText::setUnits(QString units) {
        ui->label_Units->setText(units);
    }

    void DisplaySingleText::setValue(QString value) {
        ui->label_Value1->setText(value);
    }

    void DisplaySingleText::subscribe(QString fullPath) {
        auto fairWind = fairwind::FairWind::getInstance();
        auto signalKDocument = fairWind->getSignalKDocument();

        DisplayBase::subscribe(fullPath);

        setToolTip(getDescription());
        signalKDocument->subscribe(getFullPath(),
                                   this, SLOT(fairwind::displays::DisplaySingleText::update));
    }

    void DisplaySingleText::update(const QJsonObject update) {
        //qDebug() << "DisplaySingleText::update:" << update;

        DisplayBase::update(update);
    }


    QString DisplaySingleText::getClassName() const {
        return this->metaObject()->className();
    }
}