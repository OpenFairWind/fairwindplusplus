//
// Created by Raffaele Montella on 10/06/21.
//

#ifndef FAIRWIND_VHGLAYOUT_HPP
#define FAIRWIND_VHGLAYOUT_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QWidget>
#include <FairWindSdk/ILayout.hpp>
#include <FairWindSdk/layouts/LayoutBase.hpp>
#include <FairWindSdk/IDisplay.hpp>

namespace Ui {
    class VHGLayout;
}

namespace fairwind::layouts {
class FAIRWINDSDK_LIB_DECL VHGLayout: public QWidget, public fairwind::layouts::LayoutBase, public fairwind::layouts::ILayout {
        Q_OBJECT

    public:
        explicit VHGLayout(QWidget *parent = nullptr);
        ~VHGLayout();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        ILayout *getNewInstance() override;
        QWidget *onSettings() override;

        QWidget *getWidget() override;
        void addDisplay(QString key, displays::IDisplay *display) override;

    private:
        Ui::VHGLayout *ui;
    };
}


#endif //FAIRWIND_VHGLAYOUT_HPP
