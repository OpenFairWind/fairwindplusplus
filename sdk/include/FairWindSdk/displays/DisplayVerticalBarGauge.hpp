//
// Created by Raffaele Montella on 16/09/21.
//

#ifndef FAIRWIND_DISPLAYVERTICALBARGAUGE_HPP
#define FAIRWIND_DISPLAYVERTICALBARGAUGE_HPP


#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>
#include <qcgaugewidget.h>

namespace Ui {
    class DisplayVerticalBarGauge;
}

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayVerticalBarGauge: public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
    Q_OBJECT
    public:
        explicit DisplayVerticalBarGauge(QWidget *parent = nullptr);
        ~DisplayVerticalBarGauge();

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

        Ui::DisplayVerticalBarGauge *ui;

    };
}

#endif //FAIRWIND_DISPLAYVERTICALBARGAUGE_HPP
