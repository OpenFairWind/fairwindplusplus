//
// Created by Raffaele Montella on 21/03/21.
//

#ifndef FAIRWINDS_MAINWINDOW_HPP
#define FAIRWINDS_MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>
#include <QWebEngineProfile>

#include <QDebug>
#include <QPluginLoader>

#include "../core/App.hpp"
#include "../include/FairWindApp.hpp"
#include "../include/IFairWindPlugin.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap<QString, QWidget *> mapWidgets;


    void toolButton_App_released();
    void toolButton_Apps_released();
    void toolButton_Settings_released();

    QWebEngineProfile *m_profile;

    void toolButton_WebApp_Button_clicked();


};


#endif //FAIRWINDS_MAINWINDOW_HPP
