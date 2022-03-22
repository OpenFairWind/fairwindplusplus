//
// Created by Raffaele Montella on 16/03/22.
//

#include <FairWindSdk/displays/DisplaySimpleTimeSeries.hpp>

#include "ui_DisplaySimpleTimeSeries.h"

namespace fairwind::displays {
/*
 * DisplaySimpleTimeSeries - Public Constructor
 */
    DisplaySimpleTimeSeries::DisplaySimpleTimeSeries(QWidget *parent) :
            QWidget(parent),
            ui(new Ui::DisplaySimpleTimeSeries) {
        ui->setupUi(this);

        m_widget= new QWidget();
        ui->gridLayout->addWidget(m_widget, 0, 0);

        //QMetaObject::invokeMethod(this, "mapSetup", Qt::QueuedConnection);
    }

/*
 * ~DisplaySimpleTimeSeries - Destructor
 */
    DisplaySimpleTimeSeries::~DisplaySimpleTimeSeries() {
        delete ui;
    }

/*
 * getIcon
 * Returns the display's icon
 */
    QImage DisplaySimpleTimeSeries::getIcon() const {
        return QImage(":resources/images/icons/display_data_icon.png");
    }

/*
 * onSettings
 * Returns the display's settings
 */
    QWidget *DisplaySimpleTimeSeries::onSettings() {
        return nullptr;
    }

/*
 * getNewInstance
 * Creates and returns a new IDisplay object
 */
    IDisplay *DisplaySimpleTimeSeries::getNewInstance() {
        return static_cast<IDisplay *>(new DisplaySimpleTimeSeries());
    }

/*
 * onInit
 * Initialization method
 */
    void DisplaySimpleTimeSeries::onInit(QMap<QString, QVariant> params) {
        qDebug() << "DisplaySingleText::onInit(" << params << ")";
    }

    /*
     * getClassName
     * Returns the display's class name
     */
    QString DisplaySimpleTimeSeries::getClassName() const {
        return this->metaObject()->className();
    }
}