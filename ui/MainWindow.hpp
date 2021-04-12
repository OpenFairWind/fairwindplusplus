//
// Created by Raffaele Montella on 21/03/21.
//

#ifndef FAIRWINDS_MAINWINDOW_HPP
#define FAIRWINDS_MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>
#include <QDebug>


#include "../core/App.hpp"


class BottomBar;
class TopBar;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    Ui::MainWindow *getUi();

    void toolButton_App_released();

private:
    Ui::MainWindow *ui;
    QMap<QString, QWidget *> mapWidgets;

    TopBar *m_topBar = nullptr;
    BottomBar *m_bottonBar = nullptr;
};



#endif //FAIRWINDS_MAINWINDOW_HPP
