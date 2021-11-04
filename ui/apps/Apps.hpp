//
// Created by Raffaele Montella on 13/04/21.
//

#ifndef FAIRWIND_APPS_HPP
#define FAIRWIND_APPS_HPP

#include <QWidget>

namespace Ui {
    class Apps;
}

namespace fairwind::ui::apps {
    class Apps : public QWidget {
        Q_OBJECT

    public:
        explicit Apps(QWidget *parent = 0);

        ~Apps();

        void toolButton_App_released();

        signals:

                void foregroundAppChanged(const QString hash);

    private:
        Ui::Apps *ui;
    };
}

#endif //FAIRWIND_APPS_HPP