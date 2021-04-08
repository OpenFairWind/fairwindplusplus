//
// Created by Raffaele Montella on 21/03/21.
//

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QToolButton>
#include "MainWindow.hpp"

#include "ui_MainWindow.h"
#include "../core/FairWind.hpp"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    m_profile = QWebEngineProfile::defaultProfile();

    ui->setupUi(this);

    QLabel *label_Latitude = new QLabel("40°51\".221 N");
    QLabel *label_Longitude = new QLabel("14°28\".435 E");

    QWidget *widgetDummy0 = new QWidget(this);
    widgetDummy0->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QLabel *label_Role = new QLabel("Skipper");

    QWidget *widgetDummy1 = new QWidget(this);
    widgetDummy1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QLabel *label_DateTime = new QLabel("Mon 22 Mar 13:50");

    ui->toolBarTop->addWidget(label_Latitude);
    ui->toolBarTop->addWidget(label_Longitude);
    ui->toolBarTop->addWidget(widgetDummy0);
    ui->toolBarTop->addWidget(label_Role);
    ui->toolBarTop->addWidget(widgetDummy1);
    ui->toolBarTop->addWidget(label_DateTime);

    typedef  void (MainWindow::*BottomBarIconFn)(void);

    class BottomBarIcon {
    public:
        BottomBarIcon() {
            name="";
            icon="";
            func= nullptr;
        }

        BottomBarIcon(std::string name, std::string icon) {
            this->name=name;
            this->icon=icon;
            this->func= nullptr;
        }
        BottomBarIcon(const BottomBarIcon &bottomBarIcon)  {
            this->name=bottomBarIcon.name;
            this->icon=bottomBarIcon.icon;
            this->func=bottomBarIcon.func;
        }

        BottomBarIcon(std::string name, std::string icon, BottomBarIconFn func) {
            this->name=name;
            this->icon=icon;
            this->func=func;

        }



        std::string name;
        std::string icon;
        BottomBarIconFn func= nullptr;
    };

    std::vector<BottomBarIcon> bottombarIcons;
    bottombarIcons.emplace_back("My Data",":/resources/images/icons/imagebutton_mydata.png");
    bottombarIcons.emplace_back("MOB",":/resources/images/icons/imagebutton_mob.png");
    bottombarIcons.emplace_back(
                    "Apps",
                    ":/resources/images/icons/imagebutton_apps.png",
                    &MainWindow::toolButton_Apps_released

                    );
    bottombarIcons.emplace_back("Alarms",":/resources/images/icons/imagebutton_alarms.png");
    bottombarIcons.emplace_back(
                    "Settings",
                    ":/resources/images/icons/imagebutton_settings.png",
                    &MainWindow::toolButton_Settings_released

                    );

    auto *widgetDummy2 = new QWidget(this);
    widgetDummy2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->toolBarBottom->addWidget(widgetDummy2);

    for(BottomBarIcon bottomBarIcon: bottombarIcons) {
        auto *toolButton = new QToolButton();
        toolButton->setText(bottomBarIcon.name.c_str());
        toolButton->setIcon(QIcon(QString(bottomBarIcon.icon.c_str())));
        toolButton->setIconSize(QSize(32,32));
        toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        ui->toolBarBottom->addWidget(toolButton);
        if (bottomBarIcon.func!= nullptr) {
            connect(toolButton, &QToolButton::released, this, bottomBarIcon.func);
        }
    }

    auto *widgetDummy3 = new QWidget(this);
    widgetDummy3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ui->toolBarBottom->addWidget(widgetDummy3);

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
        if (app->isPlugin()) {
            fairwind::extensions::plugins::IFairWindPlugin *fairWindPlugin =
                    fairWind->getPluginByExtensionId(app->getExtension());
            widgetApp=fairWindPlugin->onGui(this, app->getArgs());
        } else {
            fairwind::extensions::apps::IFairWindApp *fairWindApp =
                    fairWind->getAppByExtensionId(app->getExtension());
            widgetApp=fairWindApp->onGui(this, app->getArgs());
        }
        if (widgetApp) {
            ui->stackedWidget->addWidget(widgetApp);
            mapWidgets.insert(hash,widgetApp);
        }
    }
    if (widgetApp) {
        ui->stackedWidget->setCurrentWidget(widgetApp);
    }

}



void MainWindow::toolButton_Settings_released()
{


    ui->stackedWidget->setCurrentWidget(ui->page_Settings);
}

void MainWindow::toolButton_Apps_released()
{
    ui->stackedWidget->setCurrentWidget(ui->page_Apps);
}

MainWindow::~MainWindow()
{
    delete ui;
}

