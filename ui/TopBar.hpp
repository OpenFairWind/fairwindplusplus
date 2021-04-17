//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_TOPBAR_HPP
#define FAIRWIND_TOPBAR_HPP

#include <QWidget>

namespace Ui {
    class TopBar;
}

class TopBar: public QWidget {
Q_OBJECT

public:
    explicit TopBar(QWidget *parent = 0);
    ~TopBar();

private:
    Ui::TopBar *ui;
};


#endif //FAIRWIND_TOPBAR_HPP
