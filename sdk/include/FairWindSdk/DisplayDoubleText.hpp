//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYDOUBLETEXT_HPP
#define FAIRWIND_DISPLAYDOUBLETEXT_HPP


#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>

namespace Ui {
    class DisplayDoubleText;
}

class FAIRWINDSDK_LIB_DECL DisplayDoubleText: public QWidget {
    Q_OBJECT

public:
    explicit DisplayDoubleText(QWidget *parent=nullptr);
    ~DisplayDoubleText();

    void setLabel(QString label);
    void setText1(QString text);
    void setText2(QString text);

private:
    Ui::DisplayDoubleText *ui;
};


#endif //FAIRWIND_DISPLAYDOUBLETEXT_HPP
