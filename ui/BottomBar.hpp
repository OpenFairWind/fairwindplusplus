//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_BOTTOMBAR_HPP
#define FAIRWIND_BOTTOMBAR_HPP


#include <ui/BottomBarIcon.hpp>
#include "MainWindow.hpp"

class MainWindow;

namespace Ui {
    class BottomBar;
}

class BottomBar : public QObject {
    Q_OBJECT
public:
    BottomBar(MainWindow *mainWindow);

public slots:
    void settings_released();
    void apps_released();

private:
    MainWindow *m_mainWindow;
    QVector<BottomBarIcon> m_bottombarIcons;


};

#endif //FAIRWIND_BOTTOMBAR_HPP
