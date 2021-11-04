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

    public
        slots:
                void setForegroundApp(QString
        hash);

        void onApps();

        void onSettings();

    private:
        Ui::MainWindow *ui;
        // This will be populated with the apps launched by the user for quick usage
        QMap<QString, QWidget *> mapWidgets;

        // QWidget containing the loaded apps
        apps::Apps *m_apps = nullptr;
        // QWidget containing a tab for every registered settings page
        settings::Settings *m_settings = nullptr;
        // QWidget containing useful infos
        topbar::TopBar *m_topBar = nullptr;
        // QWidget containing navigation buttons
        bottombar::BottomBar *m_bottonBar = nullptr;
    };
}

#endif //FAIRWINDS_MAINWINDOW_HPP