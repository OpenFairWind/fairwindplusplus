//
// Created by Raffaele Montella on 16/03/22.
//

#ifndef FAIRWIND_DISPLAYSIMPLETIMESERIES_HPP
#define FAIRWIND_DISPLAYSIMPLETIMESERIES_HPP

#include <QWidget>
#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IDisplay.hpp>

namespace Ui {
    class DisplaySimpleTimeSeries;
}

namespace fairwind::displays {
    /*
     * DisplayChart
     * A visual display component that emulates the functionalities fo a chart, providing different data at once
     */
    class FAIRWINDSDK_LIB_DECL DisplaySimpleTimeSeries : public QWidget, public fairwind::displays::IDisplay {
        Q_OBJECT
    public:
        explicit DisplaySimpleTimeSeries(QWidget *parent = 0);
        ~DisplaySimpleTimeSeries();

        // IDisplay methods
        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;


    public slots:


    private:
        Ui::DisplaySimpleTimeSeries *ui;

        QWidget *m_widget = nullptr;
        QJsonObject mConfig;
    };
}


#endif //FAIRWIND_DISPLAYSIMPLETIMESERIES_HPP
