//
// Created by Raffaele Montella on 21/03/21.
//

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QToolButton>
#include <QProcess>
#include <QWebEngineView>
#include "MainWindow.hpp"

#include "ui_MainWindow.h"
#include "WebView.hpp"


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


    apps.emplace_back("Chart","chart.png","fairwind://chart.app");
    apps.emplace_back("Sonar","sonar.png","fairwind://sonar.app");
    apps.emplace_back("Radar","radar.png","fairwind://radar.app");
    apps.emplace_back("Dashboard","dashboard.png","fairwind://dashboard.app");
    apps.emplace_back("Audio","audio.png","fairwind://audio.app");
    apps.emplace_back("Video","video.png","fairwind://video.app");
    apps.emplace_back("UAV","uav.png","fairwind://uav.app");
    apps.emplace_back("Signal K","signalk.png","http://192.168.1.199:3000");
    apps.emplace_back("Freeboard","freeboard.png","http://192.168.1.199:3000/@signalk/freeboard-sk/");
    apps.emplace_back("Instrument Panel","instrumentpanel.png","http://192.168.1.199:3000/@signalk/instrumentpanel/");
    apps.emplace_back("OpenCPN","opencpn.png","system:///Applications/OpenCPN.app/Contents/MacOS/OpenCPN -fullscreen");
    apps.emplace_back("Navionics Web App","navionics.png","https://webapp.navionics.com");



    for (auto & app : apps) {

        QString id=QString(app.name.c_str()).replace(" ","_");
        mapApps.insert( std::pair<QString,App>(id,app) );
        QString name=QString(app.name.c_str());
        QString icon=QString(("apps/"+app.icon).c_str());

        auto *button = new QToolButton();
        button->setObjectName("toolbutton_"+id);
        button->setText(name);
        button->setIcon(QIcon(icon));
        button->setIconSize(QSize(256,256));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(button, &QToolButton::released, this, &MainWindow::toolButton_App_released);

        layout->addWidget(button,row,col);

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
    if (!buttonWidget)
        return;

    QString id=buttonWidget->objectName().replace("toolbutton_","");

    App app=mapApps.at(id);
    QString url(app.url.c_str());
    QStringList args;

    if (url.startsWith("system://")) {
        url=url.replace("system://","");
        QProcess::startDetached(url);
        showMinimized();
    } else if (url.startsWith("http://") || url.startsWith("https://")) {
        QWidget *widgetWebApp;
        if (mapWidgets.count(id)>0) {
            widgetWebApp = mapWidgets.at(id);
        } else {
            widgetWebApp = new QWidget();

            auto *webView = new WebView(widgetWebApp);
            webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

            auto *widgetWebApp_Buttons = new QWidget(widgetWebApp);

            auto *pushButton_Home=new QPushButton(widgetWebApp_Buttons);
            pushButton_Home->setText("Home");
            pushButton_Home->setObjectName("toolbutton_WebApp_Button_home_"+id);
            connect(pushButton_Home, &QToolButton::clicked, this, &MainWindow::toolButton_WebApp_Button_clicked);



            auto *pushButton_Prev=new QPushButton(widgetWebApp_Buttons);
            pushButton_Prev->setText("<");

            auto *pushButton_Next=new QPushButton(widgetWebApp_Buttons);
            pushButton_Next->setText(">");

            auto *hBoxLayout = new QHBoxLayout();
            widgetWebApp->setLayout(hBoxLayout);
            hBoxLayout->addWidget(webView);
            hBoxLayout->addWidget(widgetWebApp_Buttons);

            auto *vBoxLayout = new QVBoxLayout();
            vBoxLayout->setAlignment(Qt::AlignTop);
            vBoxLayout->addWidget(pushButton_Home);
            vBoxLayout->addWidget(pushButton_Prev);
            vBoxLayout->addWidget(pushButton_Next);
            widgetWebApp_Buttons->setLayout(vBoxLayout);


            webView->load(QUrl(url));

            ui->stackedWidget->addWidget(widgetWebApp);
            mapWidgets.insert(std::pair<QString,QWidget *>(id,widgetWebApp));
        }

        ui->stackedWidget->setCurrentWidget(widgetWebApp);
    }

}

void MainWindow::toolButton_WebApp_Button_clicked()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    int action=0;
    QString objectName=buttonWidget->objectName();
    if (objectName.indexOf("_home_")>=0) {
        objectName=objectName.replace("_home_","");
        action=1;
    } else if (objectName.indexOf("_prev_")>=0) {
        objectName=objectName.replace("_prev_","");
        action=2;
    } else if (objectName.indexOf("_next_")>=0) {
        objectName=objectName.replace("_next_","");
        action=3;
    }
    QString id=objectName.replace("toolbutton_WebApp_Button","");

    App app=mapApps.at(id);
    QWidget *widgetWebApp = mapWidgets.at(id);

    switch (action) {
        case 1:
            QString url(app.url.c_str());
            ((WebView *)(widgetWebApp->children()[0]))->load(QUrl(url));
            break;
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