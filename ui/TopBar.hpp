//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_TOPBAR_HPP
#define FAIRWIND_TOPBAR_HPP


#include <QToolBar>

class MainWindow;

namespace Ui {
    class TopBar;
}

class TopBar : QObject {
    Q_OBJECT

public:
    TopBar(MainWindow *mainWindow);

private:
    MainWindow *m_mainWindow;
};


#endif //FAIRWIND_TOPBAR_HPP
