//
// Created by Raffaele Montella on 09/06/21.
//

#ifndef FAIRWIND_DISPLAYWINDANGLEGAUGE_HPP
#define FAIRWIND_DISPLAYWINDANGLEGAUGE_HPP

#include <QWidget>

#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>
#include <qcgaugewidget.h>

namespace Ui {
    class DisplayWindAngleGauge;
}

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayWindAngleGauge: public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
    Q_OBJECT
    public:
        explicit DisplayWindAngleGauge(QWidget *parent = nullptr);
        ~DisplayWindAngleGauge();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;
        /*
        bool smaller() override;
        bool bigger() override;
    */
        void setLabel(QString label) override;
        void setUnits(QString units) override;
        void setValue(QString value) override;
        void subscribe(QString fullPath) override;

    public slots:
        void update(const QJsonObject update) override;

    private:
        QcLabelItem *mLabel;
        QcLabelItem *mUnits;
        QcLabelItem *mValue;
        QcGaugeWidget *mGaugeWidget;
        QcNeedleItem *mNeedle;
        Ui::DisplayWindAngleGauge *ui;

        float mMinValue;
        float mMaxValue;
        float mStep;
    };
}

#endif //FAIRWIND_DISPLAYWINDANGLEGAUGE_HPP