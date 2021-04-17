//
// Created by Raffaele Montella on 21/03/21.
//

#include <QTimer>
#include <QLabel>

#include <QGridLayout>
#include <QToolButton>
#include "MainWindow.hpp"
#include "TopBar.hpp"
#include "BottomBar.hpp"
#include "ui_MainWindow.h"
#include "../core/FairWind.hpp"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    m_apps = new Apps(ui->stackedWidget_Center);
    ui->stackedWidget_Center->addWidget(m_apps);

    m_settings = new Settings(ui->stackedWidget_Center);
    ui->stackedWidget_Center->addWidget(m_settings);


    m_topBar = new TopBar(ui->widget_Top);
    m_bottonBar = new BottomBar(ui->widget_Bottom);


    setCentralWidget(ui->centralwidget);
    ui->stackedWidget_Center->setCurrentWidget(m_apps);

    QObject::connect(m_apps, &Apps::foregroundAppChanged, this, &MainWindow::setForegroundApp);


    QObject::connect(m_bottonBar, &BottomBar::setApps, this, &MainWindow::onApps);
    QObject::connect(m_bottonBar, &BottomBar::setSettings, this, &MainWindow::onSettings);




    QTimer::singleShot(0, this, SLOT(showFullScreen()));
}




MainWindow::~MainWindow()
{
    if (m_settings) {
        delete m_settings;
        m_settings = nullptr;
    }
    if (m_apps) {
        delete m_apps;
        m_apps= nullptr;
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

Ui::MainWindow *MainWindow::getUi() {
    return ui;
}



void MainWindow::setForegroundApp(QString hash) {
    qDebug() << "MainWindow hash:" << hash;
    auto fairWind = fairwind::FairWind::getInstance();

    auto app=fairWind->getApps()[hash];
    QWidget *widgetApp = nullptr;
    if (mapWidgets.find(hash)!=mapWidgets.end()) {
        widgetApp = mapWidgets[hash];
    } else {

        fairwind::apps::IFairWindApp *fairWindApp =
                fairWind->getAppByExtensionId(app->getExtension());
        widgetApp=fairWindApp->onGui(this, app->getArgs());

        if (widgetApp) {
            ui->stackedWidget_Center->addWidget(widgetApp);
            mapWidgets.insert(hash,widgetApp);
        }
    }
    if (widgetApp) {
        ui->stackedWidget_Center->setCurrentWidget(widgetApp);
    }
}

void MainWindow::onApps() {
    ui->stackedWidget_Center->setCurrentWidget(m_apps);
}

void MainWindow::onSettings() {
    ui->stackedWidget_Center->setCurrentWidget(m_settings);
}

