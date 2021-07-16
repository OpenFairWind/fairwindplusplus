//
// Created by Raffaele Montella on 21/03/21.
//

#ifndef FAIRWINDS_MAINWINDOW_HPP
#define FAIRWINDS_MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include <ui/topbar/TopBar.hpp>
#include <ui/bottombar/BottomBar.hpp>


#include "FairWindSdk/App.hpp"
#include "ui/apps/Apps.hpp"
#include "ui/settings/Settings.hpp"


class BottomBar;
class TopBar;

namespace Ui {
    class MainWindow;
}

namespace fairwind::ui {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        ~MainWindow();

        Ui::MainWindow *getUi();

    public slots:
        void setForegroundApp(QString hash);
        void onApps();
        void onSettings();


    private:
        Ui::MainWindow *ui;
        QMap<QString, QWidget *> mapWidgets;

        apps::Apps *m_apps = nullptr;
        settings::Settings *m_settings = nullptr;
        topbar::TopBar *m_topBar = nullptr;
        bottombar::BottomBar *m_bottonBar = nullptr;
    };
}


#endif //FAIRWINDS_MAINWINDOW_HPP
