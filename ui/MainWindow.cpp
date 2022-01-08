//
// Created by Raffaele Montella on 21/03/21.
//

#include <QTimer>
#include <QToolButton>

#include <FairWindSdk/FairWind.hpp>

#include "MainWindow.hpp"
#include "ui/topbar/TopBar.hpp"
#include "ui/bottombar/BottomBar.hpp"
#include "ui/settings/Settings.hpp"
#include "ui_MainWindow.h"

/*
 * MainWindow
 * Public constructor - This presents FairWind's UI
 */
fairwind::ui::MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Setup the UI
    ui->setupUi(this);

    // Instantiate a new Apps object which will contain the loaded apps
    m_apps = new fairwind::ui::apps::Apps(ui->stackedWidget_Center);
    ui->stackedWidget_Center->addWidget(m_apps);

    // Instantiate a new Settings object which will contain the registered settings
    m_settings = new fairwind::ui::settings::Settings(ui->stackedWidget_Center);
    ui->stackedWidget_Center->addWidget(m_settings);

    // Instantiate TopBar and BottomBar object
    m_topBar = new fairwind::ui::topbar::TopBar(ui->widget_Top);
    m_bottonBar = new fairwind::ui::bottombar::BottomBar(ui->widget_Bottom);

    // Place the Apps object at the center of the UI
    setCentralWidget(ui->centralwidget);
    ui->stackedWidget_Center->setCurrentWidget(m_apps);

    // Show a new foreground app when pressing on the Apps object
    QObject::connect(m_apps, &apps::Apps::foregroundAppChanged, this, &MainWindow::setForegroundApp);

    // Show the apps view when the user clicks on the Apps button inside the BottomBar object
    QObject::connect(m_bottonBar, &bottombar::BottomBar::setApps, this, &MainWindow::onApps);

    // Show the settings view when the user clicks on the Settings button inside the BottomBar object
    QObject::connect(m_bottonBar, &bottombar::BottomBar::setSettings, this, &MainWindow::onSettings);

    QTimer::singleShot(0, this, SLOT(showFullScreen()));
}

/*
 * ~MainWindow
 * MainWindow's destructor
 */
fairwind::ui::MainWindow::~MainWindow() {
    // Delete every property
    if (m_settings) {
        delete m_settings;
        m_settings = nullptr;
    }

    if (m_apps) {
        delete m_apps;
        m_apps = nullptr;
    }

    if (m_bottonBar) {
        delete m_bottonBar;
        m_bottonBar = nullptr;
    }

    if (m_topBar) {
        delete m_topBar;
        m_topBar = nullptr;
    }

    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

/*
 * getUi
 * Returns the widget's UI
 */
Ui::MainWindow *fairwind::ui::MainWindow::getUi() {
    return ui;
}

/*
 * setForegroundApp
 * Method called when the user clicks on the Apps widget: show a new foreground app with the provided hash value
 */
void fairwind::ui::MainWindow::setForegroundApp(QString hash) {
    qDebug() << "MainWindow hash:" << hash;

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the map containing all the loaded apps and pick the one that matches the provided hash
    auto app = fairWind->getApps()[hash];

    // Get the fairwind app
    fairwind::apps::IApp *fairWindApp = fairWind->getAppByExtensionId(app->getExtension());

    // The QT widget implementing the app
    QWidget *widgetApp = nullptr;

    // Check if the requested app has been already launched by the user
    if (mapWidgets.contains(hash)) {

        // If yes, get its widget from mapWidgets
        widgetApp = mapWidgets[hash];
    } else {
        // invoke the app onStart method
        widgetApp = fairWindApp->onStart(this, app->getArgs());

        // Check if the widget is valid
        if (widgetApp) {

            // Add it to the UI
            ui->stackedWidget_Center->addWidget(widgetApp);

            // Store it in mapWidgets for future usage
            mapWidgets.insert(hash, widgetApp);
        }
    }

    // Check if the widget is valid
    if (widgetApp) {

        // Check if there is an app on foreground
        if (m_fairWindApp) {

            // Call the foreground app onPause method
            m_fairWindApp->onPause();
        }

        // Set the current app
        m_fairWindApp = fairWindApp;

        // Update the UI with the new widget
        ui->stackedWidget_Center->setCurrentWidget(widgetApp);

        // Call the new foreground app onResume method
        m_fairWindApp->onResume();

        // Set the current app in ui components
        m_topBar->setFairWindApp(m_fairWindApp);
    }
}

/*
 * onApps
 * Method called when the user clicks the Apps button on the BottomBar object
 */
void fairwind::ui::MainWindow::onApps() {

    // Check if there is an app on foreground
    if (m_fairWindApp) {

        // Call the foreground app onPause method
        m_fairWindApp->onPause();
    }

    // No current app
    m_fairWindApp = nullptr;

    // Show the apps view
    ui->stackedWidget_Center->setCurrentWidget(m_apps);

    // Set the current app in ui components
    m_topBar->setFairWindApp(m_fairWindApp);
}

/*
 * onSettings
 * Method called when the user clicks the Settings button on the BottomBar object
 */
void fairwind::ui::MainWindow::onSettings() {
    // Show the settings view
    ui->stackedWidget_Center->setCurrentWidget(m_settings);
}