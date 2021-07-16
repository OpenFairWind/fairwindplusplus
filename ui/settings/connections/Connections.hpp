//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_CONNECTIONS_HPP
#define FAIRWIND_CONNECTIONS_HPP

#include <QWidget>

namespace Ui {
    class Connections;
}

namespace fairwind::ui::settings::connections {

    class Connections : public QWidget {
        Q_OBJECT

    public:
        explicit Connections(QWidget *parent = 0);

        ~Connections();

    protected :
        void showEvent(QShowEvent *event);

    private:
        Ui::Connections *ui;
    };
}

#endif //FAIRWIND_CONNECTIONS_HPP
