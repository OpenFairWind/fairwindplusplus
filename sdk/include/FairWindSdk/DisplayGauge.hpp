//
// Created by Raffaele Montella on 31/05/21.
//

#ifndef FAIRWIND_DISPLAYGAUGE_HPP
#define FAIRWIND_DISPLAYGAUGE_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <qcgaugewidget.h>

namespace Ui {
    class DisplayGauge;
}

class FAIRWINDSDK_LIB_DECL DisplayGauge: public QWidget {
    Q_OBJECT
public:
    explicit DisplayGauge(QWidget *parent=nullptr);
    ~DisplayGauge();

private:
    QcLabelItem *mLabel;
    QcGaugeWidget *mGaugeWidget;
    QcNeedleItem *mNeedle;
    Ui::DisplayGauge *ui;
};


#endif //FAIRWIND_DISPLAYGAUGE_HPP
