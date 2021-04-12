//
// Created by Raffaele Montella on 12/04/21.
//

#include <QLabel>
#include "TopBar.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

TopBar::TopBar(MainWindow *mainWindow) {
    m_mainWindow = mainWindow;
    QToolBar *toolBar = m_mainWindow->getUi()->toolBarTop;

    auto *label_Latitude = new QLabel("40°51\".221 N");
    auto *label_Longitude = new QLabel("14°28\".435 E");

    auto *widgetDummy0 = new QWidget(toolBar);
    widgetDummy0->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    auto *label_Role = new QLabel("Skipper");

    auto *widgetDummy1 = new QWidget(toolBar);
    widgetDummy1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    auto *label_DateTime = new QLabel("Mon 22 Mar 13:50");

    toolBar->addWidget(label_Latitude);
    toolBar->addWidget(label_Longitude);
    toolBar->addWidget(widgetDummy0);
    toolBar->addWidget(label_Role);
    toolBar->addWidget(widgetDummy1);
    toolBar->addWidget(label_DateTime);
}
