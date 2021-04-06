/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_Apps;
    QVBoxLayout *verticalLayout_Apps;
    QScrollArea *scrollArea_Apps;
    QWidget *scrollAreaWidgetContents_Apps;
    QWidget *page_Settings;
    QVBoxLayout *verticalLayout_Setting;
    QTabWidget *tabWidget_Settings;
    QWidget *tab_Settings;
    QHBoxLayout *horizontalLayout_Settings;
    QScrollArea *scrollArea_Settings;
    QWidget *scrollAreaWidgetContents_Settings;
    QVBoxLayout *verticalLayout_Settings_Buttons;
    QPushButton *pushButton_Settings_Cancel;
    QPushButton *pushButton_Settings_Save;
    QWidget *tab_Data_Connections;
    QHBoxLayout *horizontalLayout_Data_Connections;
    QScrollArea *scrollArea_Data_Connections;
    QWidget *scrollAreaWidgetContents_Data_Connections;
    QVBoxLayout *verticalLayout_Data_Connections_Buttons;
    QPushButton *pushButton_Data_Connections_Cancel;
    QPushButton *pushButton_Data_Connections_Add;
    QPushButton *pushButton_Data_Connections_Save;
    QWidget *tab_Plugin_Config;
    QHBoxLayout *horizontalLayout_Plugin_Config;
    QScrollArea *scrollArea_Plugin_Config;
    QWidget *scrollAreaWidgetContents_Plugin_Config;
    QVBoxLayout *verticalLayout_Plugin_Config_Buttons;
    QPushButton *pushButton_Plugin_Config_Cancel;
    QPushButton *pushButton_Plugin_Config_Upload;
    QPushButton *pushButton_Plugin_Config_Store;
    QPushButton *pushButton_Plugin_Config_Save;
    QToolBar *toolBarBottom;
    QToolBar *toolBarTop;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 633);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setAutoFillBackground(false);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 20, 342, 238));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget { background-image: url(:/resources/images/carbon_base.png); }"));
        page_Apps = new QWidget();
        page_Apps->setObjectName(QString::fromUtf8("page_Apps"));
        sizePolicy.setHeightForWidth(page_Apps->sizePolicy().hasHeightForWidth());
        page_Apps->setSizePolicy(sizePolicy);
        verticalLayout_Apps = new QVBoxLayout(page_Apps);
        verticalLayout_Apps->setObjectName(QString::fromUtf8("verticalLayout_Apps"));
        scrollArea_Apps = new QScrollArea(page_Apps);
        scrollArea_Apps->setObjectName(QString::fromUtf8("scrollArea_Apps"));
        sizePolicy.setHeightForWidth(scrollArea_Apps->sizePolicy().hasHeightForWidth());
        scrollArea_Apps->setSizePolicy(sizePolicy);
        scrollArea_Apps->setStyleSheet(QString::fromUtf8(""));
        scrollArea_Apps->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_Apps->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea_Apps->setWidgetResizable(true);
        scrollArea_Apps->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_Apps = new QWidget();
        scrollAreaWidgetContents_Apps->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_Apps"));
        scrollAreaWidgetContents_Apps->setGeometry(QRect(0, 8, 316, 196));
        scrollArea_Apps->setWidget(scrollAreaWidgetContents_Apps);

        verticalLayout_Apps->addWidget(scrollArea_Apps);

        stackedWidget->addWidget(page_Apps);
        page_Settings = new QWidget();
        page_Settings->setObjectName(QString::fromUtf8("page_Settings"));
        verticalLayout_Setting = new QVBoxLayout(page_Settings);
        verticalLayout_Setting->setObjectName(QString::fromUtf8("verticalLayout_Setting"));
        tabWidget_Settings = new QTabWidget(page_Settings);
        tabWidget_Settings->setObjectName(QString::fromUtf8("tabWidget_Settings"));
        tab_Settings = new QWidget();
        tab_Settings->setObjectName(QString::fromUtf8("tab_Settings"));
        horizontalLayout_Settings = new QHBoxLayout(tab_Settings);
        horizontalLayout_Settings->setObjectName(QString::fromUtf8("horizontalLayout_Settings"));
        scrollArea_Settings = new QScrollArea(tab_Settings);
        scrollArea_Settings->setObjectName(QString::fromUtf8("scrollArea_Settings"));
        scrollArea_Settings->setWidgetResizable(true);
        scrollAreaWidgetContents_Settings = new QWidget();
        scrollAreaWidgetContents_Settings->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_Settings"));
        scrollAreaWidgetContents_Settings->setGeometry(QRect(0, 0, 179, 157));
        scrollArea_Settings->setWidget(scrollAreaWidgetContents_Settings);

        horizontalLayout_Settings->addWidget(scrollArea_Settings);

        verticalLayout_Settings_Buttons = new QVBoxLayout();
        verticalLayout_Settings_Buttons->setObjectName(QString::fromUtf8("verticalLayout_Settings_Buttons"));
        pushButton_Settings_Cancel = new QPushButton(tab_Settings);
        pushButton_Settings_Cancel->setObjectName(QString::fromUtf8("pushButton_Settings_Cancel"));

        verticalLayout_Settings_Buttons->addWidget(pushButton_Settings_Cancel, 0, Qt::AlignTop);

        pushButton_Settings_Save = new QPushButton(tab_Settings);
        pushButton_Settings_Save->setObjectName(QString::fromUtf8("pushButton_Settings_Save"));

        verticalLayout_Settings_Buttons->addWidget(pushButton_Settings_Save, 0, Qt::AlignTop);


        horizontalLayout_Settings->addLayout(verticalLayout_Settings_Buttons);

        tabWidget_Settings->addTab(tab_Settings, QString());
        tab_Data_Connections = new QWidget();
        tab_Data_Connections->setObjectName(QString::fromUtf8("tab_Data_Connections"));
        horizontalLayout_Data_Connections = new QHBoxLayout(tab_Data_Connections);
        horizontalLayout_Data_Connections->setObjectName(QString::fromUtf8("horizontalLayout_Data_Connections"));
        scrollArea_Data_Connections = new QScrollArea(tab_Data_Connections);
        scrollArea_Data_Connections->setObjectName(QString::fromUtf8("scrollArea_Data_Connections"));
        scrollArea_Data_Connections->setWidgetResizable(true);
        scrollAreaWidgetContents_Data_Connections = new QWidget();
        scrollAreaWidgetContents_Data_Connections->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_Data_Connections"));
        scrollAreaWidgetContents_Data_Connections->setGeometry(QRect(0, 0, 179, 157));
        scrollArea_Data_Connections->setWidget(scrollAreaWidgetContents_Data_Connections);

        horizontalLayout_Data_Connections->addWidget(scrollArea_Data_Connections);

        verticalLayout_Data_Connections_Buttons = new QVBoxLayout();
        verticalLayout_Data_Connections_Buttons->setObjectName(QString::fromUtf8("verticalLayout_Data_Connections_Buttons"));
        pushButton_Data_Connections_Cancel = new QPushButton(tab_Data_Connections);
        pushButton_Data_Connections_Cancel->setObjectName(QString::fromUtf8("pushButton_Data_Connections_Cancel"));

        verticalLayout_Data_Connections_Buttons->addWidget(pushButton_Data_Connections_Cancel);

        pushButton_Data_Connections_Add = new QPushButton(tab_Data_Connections);
        pushButton_Data_Connections_Add->setObjectName(QString::fromUtf8("pushButton_Data_Connections_Add"));

        verticalLayout_Data_Connections_Buttons->addWidget(pushButton_Data_Connections_Add);

        pushButton_Data_Connections_Save = new QPushButton(tab_Data_Connections);
        pushButton_Data_Connections_Save->setObjectName(QString::fromUtf8("pushButton_Data_Connections_Save"));

        verticalLayout_Data_Connections_Buttons->addWidget(pushButton_Data_Connections_Save, 0, Qt::AlignTop);


        horizontalLayout_Data_Connections->addLayout(verticalLayout_Data_Connections_Buttons);

        tabWidget_Settings->addTab(tab_Data_Connections, QString());
        tab_Plugin_Config = new QWidget();
        tab_Plugin_Config->setObjectName(QString::fromUtf8("tab_Plugin_Config"));
        horizontalLayout_Plugin_Config = new QHBoxLayout(tab_Plugin_Config);
        horizontalLayout_Plugin_Config->setObjectName(QString::fromUtf8("horizontalLayout_Plugin_Config"));
        scrollArea_Plugin_Config = new QScrollArea(tab_Plugin_Config);
        scrollArea_Plugin_Config->setObjectName(QString::fromUtf8("scrollArea_Plugin_Config"));
        scrollArea_Plugin_Config->setWidgetResizable(true);
        scrollAreaWidgetContents_Plugin_Config = new QWidget();
        scrollAreaWidgetContents_Plugin_Config->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_Plugin_Config"));
        scrollAreaWidgetContents_Plugin_Config->setGeometry(QRect(0, 0, 174, 157));
        scrollArea_Plugin_Config->setWidget(scrollAreaWidgetContents_Plugin_Config);

        horizontalLayout_Plugin_Config->addWidget(scrollArea_Plugin_Config);

        verticalLayout_Plugin_Config_Buttons = new QVBoxLayout();
        verticalLayout_Plugin_Config_Buttons->setObjectName(QString::fromUtf8("verticalLayout_Plugin_Config_Buttons"));
        pushButton_Plugin_Config_Cancel = new QPushButton(tab_Plugin_Config);
        pushButton_Plugin_Config_Cancel->setObjectName(QString::fromUtf8("pushButton_Plugin_Config_Cancel"));

        verticalLayout_Plugin_Config_Buttons->addWidget(pushButton_Plugin_Config_Cancel);

        pushButton_Plugin_Config_Upload = new QPushButton(tab_Plugin_Config);
        pushButton_Plugin_Config_Upload->setObjectName(QString::fromUtf8("pushButton_Plugin_Config_Upload"));

        verticalLayout_Plugin_Config_Buttons->addWidget(pushButton_Plugin_Config_Upload);

        pushButton_Plugin_Config_Store = new QPushButton(tab_Plugin_Config);
        pushButton_Plugin_Config_Store->setObjectName(QString::fromUtf8("pushButton_Plugin_Config_Store"));

        verticalLayout_Plugin_Config_Buttons->addWidget(pushButton_Plugin_Config_Store);

        pushButton_Plugin_Config_Save = new QPushButton(tab_Plugin_Config);
        pushButton_Plugin_Config_Save->setObjectName(QString::fromUtf8("pushButton_Plugin_Config_Save"));

        verticalLayout_Plugin_Config_Buttons->addWidget(pushButton_Plugin_Config_Save, 0, Qt::AlignTop);


        horizontalLayout_Plugin_Config->addLayout(verticalLayout_Plugin_Config_Buttons);

        tabWidget_Settings->addTab(tab_Plugin_Config, QString());

        verticalLayout_Setting->addWidget(tabWidget_Settings);

        stackedWidget->addWidget(page_Settings);
        MainWindow->setCentralWidget(centralwidget);
        toolBarBottom = new QToolBar(MainWindow);
        toolBarBottom->setObjectName(QString::fromUtf8("toolBarBottom"));
        toolBarBottom->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-top-color: rgb(103, 105, 105);\n"
"border-right-color: rgb(0, 0, 0);\n"
"border-bottom-color: rgb(0, 0, 0);\n"
"border-left-color: rgb(0, 0, 0);\n"
"color: rgb(250, 255, 255);"));
        toolBarBottom->setMovable(false);
        toolBarBottom->setFloatable(false);
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBarBottom);
        toolBarTop = new QToolBar(MainWindow);
        toolBarTop->setObjectName(QString::fromUtf8("toolBarTop"));
        toolBarTop->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-bottom-color: rgb(103, 105, 105);\n"
"border-right-color: rgb(0, 0, 0);\n"
"border-top-color: rgb(0, 0, 0);\n"
"border-left-color: rgb(0, 0, 0);\n"
"color: rgb(250, 255, 255);"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarTop);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        tabWidget_Settings->setCurrentIndex(0);
        pushButton_Settings_Cancel->setDefault(true);
        pushButton_Data_Connections_Cancel->setDefault(true);
        pushButton_Plugin_Config_Cancel->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FairWind", nullptr));
        pushButton_Settings_Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_Settings_Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        pushButton_Data_Connections_Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_Data_Connections_Add->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton_Data_Connections_Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Data_Connections), QCoreApplication::translate("MainWindow", "Data Connections", nullptr));
        pushButton_Plugin_Config_Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_Plugin_Config_Upload->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        pushButton_Plugin_Config_Store->setText(QCoreApplication::translate("MainWindow", "Store", nullptr));
        pushButton_Plugin_Config_Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Plugin_Config), QCoreApplication::translate("MainWindow", "Plugin Config", nullptr));
        toolBarBottom->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolBarTop->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
