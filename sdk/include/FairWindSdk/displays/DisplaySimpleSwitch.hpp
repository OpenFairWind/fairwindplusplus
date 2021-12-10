//
// Created by Raffaele Montella on 15/09/21.
//

#ifndef FAIRWIND_DISPLAYSIMPLESWITCH_HPP
#define FAIRWIND_DISPLAYSIMPLESWITCH_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>


namespace Ui {
    class DisplaySimpleSwitch;
}

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplaySimpleSwitch: public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
        Q_OBJECT
    public:
        explicit DisplaySimpleSwitch(QWidget *parent = nullptr);
        ~DisplaySimpleSwitch();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;


        void setLabel(QString label) override;
        void setUnits(QString units) override;
        void setValue(QString value) override;
        void subscribe(QString fullPath) override;

        void updateStatus();

        public slots:
        void update(const QJsonObject update) override;
        void onRelease();

    private:
        Ui::DisplaySimpleSwitch *ui;
        bool status;

    };
}


#endif //FAIRWIND_DISPLAYSIMPLESWITCH_HPP
