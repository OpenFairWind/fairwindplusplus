//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYDOUBLETEXT_HPP
#define FAIRWIND_DISPLAYDOUBLETEXT_HPP


#include <QWidget>
#include "DisplaySingleText.hpp"

namespace Ui {
    class DisplayDoubleText;
}

class DisplayDoubleText: public DisplaySingleText {
    Q_OBJECT

public:
    explicit DisplayDoubleText(QWidget *parent=0);
    ~DisplayDoubleText();

    void setText2(QString text);

private:
    Ui::DisplayDoubleText *ui;
};


#endif //FAIRWIND_DISPLAYDOUBLETEXT_HPP
