//
// Created by Raffaele Montella on 10/06/21.
//

#ifndef FAIRWIND_PAGE4X4LAYOUT_HPP
#define FAIRWIND_PAGE4X4LAYOUT_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QWidget>
#include <FairWindSdk/ILayout.hpp>
#include <FairWindSdk/layouts/LayoutBase.hpp>
#include <FairWindSdk/IDisplay.hpp>

namespace Ui {
    class Page4x4Layout;
}

namespace fairwind::layouts {
class FAIRWINDSDK_LIB_DECL Page4x4Layout: public QWidget, public fairwind::layouts::LayoutBase, public fairwind::layouts::ILayout {
        Q_OBJECT

    public:
        explicit Page4x4Layout(QWidget *parent = nullptr);
        ~Page4x4Layout();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        ILayout *getNewInstance() override;
        QWidget *onSettings() override;

        QWidget *getWidget() override;
        void addDisplay(QString key, displays::IDisplay *display) override;

    private:
        Ui::Page4x4Layout *ui;
    };
}


#endif //FAIRWIND_PAGE4X4LAYOUT_HPP
