//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYSINGLETEXT_HPP
#define FAIRWIND_DISPLAYSINGLETEXT_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/IDisplay.hpp>

namespace Ui {
    class DisplaySingleText;
}


namespace fairwind::displays {


    class FAIRWINDSDK_LIB_DECL DisplaySingleText : public QWidget, public fairwind::displays::DisplayBase, public fairwind::displays::IDisplay {
    Q_OBJECT


    public:
        explicit DisplaySingleText(QWidget *parent = nullptr);
        ~DisplaySingleText();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;
        bool smaller() override;
        bool bigger() override;

        void setLabel(QString label)  override;
        void setUnits(QString units)  override;
        void setValue(QString value)  override;
        void subscribe(QString fullPath)  override;

    public slots:

        void update(const QJsonObject update) override;

    private:
        Ui::DisplaySingleText *ui;

    };

}


#endif //FAIRWIND_DISPLAYSINGLETEXT_HPP
