//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYSINGLETEXT_HPP
#define FAIRWIND_DISPLAYSINGLETEXT_HPP

#include <QWidget>

namespace Ui {
    class DisplaySingleText;
}

class DisplaySingleText: public QWidget {
    Q_OBJECT

public:
    explicit DisplaySingleText(QWidget *parent=0);
    ~DisplaySingleText();

    void setLabel(QString label);
    void setText1(QString text);

private:
    Ui::DisplaySingleText *ui;
};


#endif //FAIRWIND_DISPLAYSINGLETEXT_HPP
