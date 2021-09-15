//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYDOUBLETEXT_HPP
#define FAIRWIND_DISPLAYDOUBLETEXT_HPP


#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IDisplay.hpp>

namespace Ui {
    class DisplayDoubleText;
}

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayDoubleText : public QWidget, public fairwind::displays::IDisplay {
    Q_OBJECT

    public:
        explicit DisplayDoubleText(QWidget *parent = nullptr);
        ~DisplayDoubleText();

        /* IDisplay methods */
        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;

        /*
        bool smaller() override;
        bool bigger() override;
         */

        void setLabel(QString label);

        void setText1(QString text);

        void setText2(QString text);

    private:
        Ui::DisplayDoubleText *ui;
    };
}

#endif //FAIRWIND_DISPLAYDOUBLETEXT_HPP
