//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYSINGLETEXT_HPP
#define FAIRWIND_DISPLAYSINGLETEXT_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindDisplay.hpp>


namespace Ui {
    class DisplaySingleText;
}


namespace fairwind::displays {


    class FAIRWINDSDK_LIB_DECL DisplaySingleText : public QWidget, public fairwind::displays::IFairWindDisplay {
    Q_OBJECT


    public:
        explicit DisplaySingleText(QWidget *parent = nullptr);
        ~DisplaySingleText();

        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IFairWindDisplay *getNewInstance() override;
        QWidget *onSettings() override;
        bool smaller() override;
        bool bigger() override;

        void setLabel(QString label);

        void setUnits(QString label);

        void setText(QString text);

        void subscribe(QString fullPath);

    public slots:

        void update(const QJsonObject update);

    private:
        Ui::DisplaySingleText *ui;
        QString mUnits;
        QString mFullPath;
        QString mSrcUnits;
        QString mDescription;
        QChar mFillChar;
        QChar mFormat;
        int mPrecision;
        int mFieldWidth;
    };

}


#endif //FAIRWIND_DISPLAYSINGLETEXT_HPP
