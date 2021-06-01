//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYSINGLETEXT_HPP
#define FAIRWIND_DISPLAYSINGLETEXT_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>

namespace Ui {
    class DisplaySingleText;
}

class FAIRWINDSDK_LIB_DECL DisplaySingleText: public QWidget {
    Q_OBJECT


public:
    explicit DisplaySingleText(QWidget *parent=nullptr);
    ~DisplaySingleText();

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
    double mConversionFactor;
};


#endif //FAIRWIND_DISPLAYSINGLETEXT_HPP
