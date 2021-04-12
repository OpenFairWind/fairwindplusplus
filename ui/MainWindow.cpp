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
    m_topBar = new TopBar(this);
    m_bottonBar = new BottomBar(this);


    QGridLayout *layout = new QGridLayout(ui->scrollAreaWidgetContents_Apps);
    ui->scrollAreaWidgetContents_Apps->setLayout(layout);

    int cols=4,rows=2;

    for(int col=0;col<cols;col++) {
        layout->setColumnMinimumWidth(col, 64);
    }
    for(int row=0;row<rows;row++) {
        layout->setRowMinimumHeight(row, 64);
    }


    int row=0, col=0, page=0;



    auto fairWind=fairwind::FairWind::getInstance();
    auto apps=fairWind->getApps();
    qDebug() << "apps:" << apps.keys();

    for (auto &hash : apps.keys()) {
        auto app=apps[hash];
        if (app->getActive()) {
            auto *button = new QToolButton();
            button->setObjectName("toolbutton_"+hash);
            button->setText(app->getName());
            QImage icon=app->getIcon();
            button->setIcon(QPixmap::fromImage(icon));
            button->setIconSize(QSize(256,256));
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            connect(button, &QToolButton::released, this, &MainWindow::toolButton_App_released);

            layout->addWidget(button,row,col);
        }

        row++;
        if (row==rows) {
            row=0;
            col++;
        }
    }

    this->setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->setCurrentIndex(0);

    QTimer::singleShot(0, this, SLOT(showFullScreen()));
}

void MainWindow::toolButton_App_released()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget) {
        return;
    }

    QString hash=buttonWidget->objectName().replace("toolbutton_","");

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
            ui->stackedWidget->addWidget(widgetApp);
            mapWidgets.insert(hash,widgetApp);
        }
    }
    if (widgetApp) {
        ui->stackedWidget->setCurrentWidget(widgetApp);
    }

}


MainWindow::~MainWindow()
{
    delete m_bottonBar;
    delete m_topBar;
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() {
    return ui;
}

