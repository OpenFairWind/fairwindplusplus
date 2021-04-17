//
// Created by Raffaele Montella on 13/04/21.
//

#ifndef FAIRWIND_SETTINGS_HPP
#define FAIRWIND_SETTINGS_HPP

#include <QObject>

namespace Ui {
    class Settings;
}

class Settings: public QWidget {
Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    Ui::Settings *ui;
};


#endif //FAIRWIND_SETTINGS_HPP
