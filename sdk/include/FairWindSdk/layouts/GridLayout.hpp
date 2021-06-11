//
// Created by Raffaele Montella on 11/06/21.
//

#ifndef FAIRWIND_GRIDLAYOUT_HPP
#define FAIRWIND_GRIDLAYOUT_HPP


#include <FairWindSdk/FairWindSDK.hpp>
#include <QWidget>
#include <FairWindSdk/ILayout.hpp>
#include <FairWindSdk/layouts/LayoutBase.hpp>
#include <FairWindSdk/IDisplay.hpp>


namespace fairwind::layouts {
    class FAIRWINDSDK_LIB_DECL GridLayout: public QWidget, public fairwind::layouts::LayoutBase, public fairwind::layouts::ILayout {
    Q_OBJECT

    public:
    explicit GridLayout(QWidget *parent = nullptr);
    ~GridLayout();

    QString getClassName() const override;
    QImage getIcon() const override;
    void onInit(QMap<QString, QVariant> params) override;
    ILayout *getNewInstance() override;
    QWidget *onSettings() override;

    QWidget *getWidget() override;
    void addDisplay(QString key, displays::IDisplay *display) override;

    private:
        QGridLayout *mGridLayout;
};
}



#endif //FAIRWIND_GRIDLAYOUT_HPP
