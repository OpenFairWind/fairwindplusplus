//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_APPLICATIONS_HPP
#define FAIRWIND_APPLICATIONS_HPP

#include <QWidget>

namespace Ui {
    class Applications;
}

namespace fairwind::ui::settings::applications {

    class Applications : public QWidget {
        Q_OBJECT

    public:
        explicit Applications(QWidget *parent = 0);

        ~Applications();

    protected :
        void showEvent(QShowEvent *event);

    private:
        Ui::Applications *ui;
    };
}


#endif //FAIRWIND_APPLICATIONS_HPP
