//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_GENERIC_HPP
#define FAIRWIND_GENERIC_HPP

#include <QWidget>

namespace Ui {
    class Generic;
}

namespace fairwind::ui::settings::generic {

    class Generic : public QWidget {
        Q_OBJECT

    public:
        explicit Generic(QWidget *parent = 0);

        ~Generic();

    protected :
        void showEvent(QShowEvent *event);

    private:
        Ui::Generic *ui;
    };
}


#endif //FAIRWIND_GENERIC_HPP
