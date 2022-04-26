//
// Created by Raffaele Montella on 31/05/21.
//

#include "ui_DisplayGauge.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplayGauge.hpp>

namespace fairwind::displays {
    DisplayGauge::DisplayGauge(QWidget *parent) :
            QWidget(parent),
            DisplayBase(),
            ui(new Ui::DisplayGauge) {

        ui->setupUi(this);

        mMinValue = 0;
        mMaxValue = 100;
        mStep = 10;
    }

    DisplayGauge::~DisplayGauge() {
        delete ui;
    }

    QImage DisplayGauge::getIcon() const {
        return QImage(":resources/images/icons/display_gauge_icon.png");
    }

    QWidget *DisplayGauge::onSettings() {
        return nullptr;
    }

    void DisplayGauge::onInit(QMap<QString, QVariant> params) {

        qDebug() << "DisplayGauge::onInit: " << params;

        // Setup parameters
        if (params.contains("minValue")) {
            mMinValue = (float) params["minValue"].toDouble();
        }

        if (params.contains("maxValue")) {
            mMaxValue = (float) params["maxValue"].toDouble();
        }

        if (params.contains("step")) {
            mStep = (float) params["step"].toDouble();
        }

        bool addColorBand = false;
        if (params.contains("colorBand")) {
            addColorBand = true;
        }

        // Create the gauge widget
        mGaugeWidget = new QcGaugeWidget;



        // Add an arc
        QcArcItem *arcItem = mGaugeWidget->addArc(55);

        QcDegreesItem *degreesItem = mGaugeWidget->addDegrees(65);
        degreesItem->setValueRange(mMinValue, mMaxValue);
        degreesItem->setStep(mStep);
        degreesItem->setSubDegree(true);

        if (addColorBand) {
            QcColorBand *clrBand = mGaugeWidget->addColorBand(50);
            clrBand->setValueRange(mMinValue, mMaxValue);
        }

        QcValuesItem *valuesItem = mGaugeWidget->addValues(80);
        valuesItem->setValueRange(mMinValue, mMaxValue);
        valuesItem->setStep(mStep);

        mLabel = mGaugeWidget->addLabel(70);

        mUnits = mGaugeWidget->addLabel(50);

        mValue = mGaugeWidget->addLabel(40);

        mNeedle = mGaugeWidget->addNeedle(60);
        mNeedle->setLabel(mValue);
        mNeedle->setColor(Qt::blue);
        mNeedle->setValueRange(mMinValue, mMaxValue);

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
        if (params.contains("value")) {
            setValue(params["value"].toString());
        }

        ui->horizontalLayout->addWidget(mGaugeWidget);
    }

    IDisplay *DisplayGauge::getNewInstance() {
        return static_cast<IDisplay *>(new DisplayGauge());
    }

    QString DisplayGauge::getClassName() const {
        return this->metaObject()->className();
    }

    void DisplayGauge::setLabel(QString label) {
        mLabel->setText(label);
    }

    void DisplayGauge::setUnits(QString units) {
        mUnits->setText(units);
    }

    void DisplayGauge::setValue(QString text) {
        mValue->setText(text);
        double value = text.toDouble();
        mNeedle->setCurrentValue(value);
    }

    void DisplayGauge::subscribe(QString fullPath) {
        auto fairWind = fairwind::FairWind::getInstance();
        auto signalKDocument = fairWind->getSignalKDocument();

        DisplayBase::subscribe(fullPath);
        setToolTip(getDescription());
        signalKDocument->subscribe(getFullPath(),
                                   this, SLOT(fairwind::displays::DisplayGauge::update));
    }

    void DisplayGauge::update(const QJsonObject update) {
        //qDebug() << "DisplaySingleText::update:" << update;

        DisplayBase::update(update);
    }
}
