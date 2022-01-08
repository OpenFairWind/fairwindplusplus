//
// Created by filippo on 08/01/22.
//

#ifndef FAIRWIND_DISPLAYBARGAUGE_H
#define FAIRWIND_DISPLAYBARGAUGE_H

#include <QWidget>
#include <QLabel>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>
#include <qcgaugewidget.h>

namespace Ui {
    class DisplayBarGauge; }

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayBarGauge : public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
    Q_OBJECT

    public:
        explicit DisplayBarGauge(QWidget *parent = nullptr);
        ~DisplayBarGauge() override;

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;

        void setLabel(QString label) override;
        void setUnits(QString units) override;
        void setValue(QString value) override;
        void subscribe(QString fullPath) override;

    public slots:
        void update(const QJsonObject update) override;

    private:
        QcBar *vbar;
        QLabel *mLabel;
        QLabel *mUnits;
        Ui::DisplayBarGauge *ui;

        float _minValue;
        float _maxValue;
        float _currentValue;
        float _precision;
        float _shortStep;
        float _longStep;


    };
}

#endif //FAIRWIND_DISPLAYBARGAUGE_H
