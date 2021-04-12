//
// Created by Raffaele Montella on 12/04/21.
//

#include <QSizePolicy>
#include <QToolBar>
#include <QToolButton>
#include "BottomBar.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

BottomBar::BottomBar(MainWindow *mainWindow) {
    m_mainWindow=mainWindow;
    QToolBar *toolBar=m_mainWindow->getUi()->toolBarBottom;

    m_bottombarIcons.append(BottomBarIcon("My Data",":/resources/images/icons/imagebutton_mydata.png"));
    m_bottombarIcons.append(BottomBarIcon("MOB",":/resources/images/icons/imagebutton_mob.png"));

    m_bottombarIcons.append(
            BottomBarIcon(
                "Apps",
                ":/resources/images/icons/imagebutton_apps.png",
                &BottomBar::apps_released
                )
            );

    m_bottombarIcons.append(BottomBarIcon("Alarms",":/resources/images/icons/imagebutton_alarms.png"));

    m_bottombarIcons.append(BottomBarIcon(
            "Settings",
            ":/resources/images/icons/imagebutton_settings.png",
            &BottomBar::settings_released

    ));

    auto *widgetDummy2 = new QWidget(toolBar);
    widgetDummy2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    toolBar->addWidget(widgetDummy2);

    for(BottomBarIcon &bottomBarIcon: m_bottombarIcons) {
        auto *toolButton = new QToolButton();
        toolButton->setText(bottomBarIcon.getName());
        toolButton->setIcon(QIcon(QString(bottomBarIcon.getIcon())));
        toolButton->setIconSize(QSize(32,32));
        toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolBar->addWidget(toolButton);
        if (bottomBarIcon.getFunc()!= nullptr) {
            connect(toolButton, &QToolButton::released, this, bottomBarIcon.getFunc());
        }
    }

    auto *widgetDummy3 = new QWidget(toolBar);
    widgetDummy3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    toolBar->addWidget(widgetDummy3);
}

void BottomBar::settings_released() {
    m_mainWindow->getUi()->stackedWidget->setCurrentWidget(m_mainWindow->getUi()->page_Settings);
}

void BottomBar::apps_released() {
    m_mainWindow->getUi()->stackedWidget->setCurrentWidget(m_mainWindow->getUi()->page_Apps);
}

