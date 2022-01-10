//
// Created by filippo on 09/01/22.
//

#ifndef FAIRWIND_DISPLAYTOGGLESWITCH_HPP
#define FAIRWIND_DISPLAYTOGGLESWITCH_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>
#include <qcswitchwidget.hpp>



namespace Ui { class DisplayToggleSwitch; }

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayToggleSwitch : public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
    Q_OBJECT

    public:
        explicit DisplayToggleSwitch(QWidget *parent = nullptr);

        ~DisplayToggleSwitch() override;

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
        Ui::DisplayToggleSwitch *ui;
        ToggleButton *toggle;
        bool status;
    };

}
#endif //FAIRWIND_DISPLAYTOGGLESWITCH_HPP
