//
// Created by __author__ on 21/01/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <QScreen>
#include <QRect>
#include <QScrollBar>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::launcherax10m {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        // Create a new grid layout
        auto *layout = new QGridLayout(ui->scrollAreaWidgetContents);
        auto scrollArea = ui->scrollArea;
        // Set the UI scroll area with the newly created layout
        ui->scrollAreaWidgetContents->setLayout(layout);
        scrollArea->horizontalScrollBar()->setVisible(false);

        auto buttonLeft = ui->toolButton_Left;
        auto buttonRight = ui->toolButton_Right;

        // Set the grid layout to have 4 columns and two rows
        int cols = 4, rows = 2;

        // Iterate on the columns
        for (int col = 0; col < cols; col++) {
            // Set the column width for each column
            layout->setColumnMinimumWidth(col, 64);
        }

        // Iterate on the rows
        for (int row = 0; row < rows; row++) {
            // Set the row height for each row
            layout->setRowMinimumHeight(row, 64);
        }

        int row = 0, col = 0, page = 0;

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the available apps list from the FairWind singleton itself
        //auto apps = fairWind->getApps();

        int screenHeight = QGuiApplication::primaryScreen()->geometry().height();
        int size = (64 * screenHeight) / 480;

        // Iterate on the available apps' hash values
        for (auto &hash: fairWind->getExtensionsHashes()) {
            // Get the hash value
            auto app = fairWind->getAppItemByHash(hash);
            // Check if the app is active
            if (app->getActive()) {
                // Create a new button
                auto *button = new QToolButton();
                // Set the app's hash value as the button's object name
                button->setObjectName("toolbutton_" + hash);
                // Set the app's name as the button's text
                button->setText(app->getName());
                // Get the app's icon
                QImage icon = app->getIcon();
                // Set the app's icon as the button's icon
                button->setIcon(QPixmap::fromImage(icon));
                // Give the button's icon a fixed square size of 256x256
                button->setIconSize(QSize(size * screenHeight / 480, size * screenHeight / 480));
                // Set the button's style to have an icon and some text beneath it
                button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
                // Launch the app when the button is clicked
                connect(button, &QToolButton::released, this, &MainPage::toolButton_App_released);

                // Add the newly created button to the grid layout as a widget
                layout->addWidget(button, row, col);
            }

            row++;
            if (row == rows) {
                row = 0;
                col++;
            }
        }

        connect(buttonLeft, static_cast<void (QToolButton::*)(bool state)>(&QToolButton::clicked), this, [scrollArea, size, screenHeight]() {
            scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() - (size * screenHeight / 480) * 2);
        });
        connect(buttonRight, static_cast<void (QToolButton::*)(bool state)>(&QToolButton::clicked), this, [scrollArea, size, screenHeight]() {
            scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() + (size * screenHeight / 480) * 2);
        });
    }

    MainPage::~MainPage() {
        delete ui;
    }

    /*
 * toolButton_App_released
 * Method called when the user wants to launch an app
 */
    void MainPage::toolButton_App_released() {
        // Get the sender button
        QWidget *buttonWidget = qobject_cast<QWidget *>(sender());
        // Check if the sender is valid
        if (!buttonWidget) {
            return;
        }

        // Get the app's hash value from the button's object name
        QString hash = buttonWidget->objectName().replace("toolbutton_", "");
        qDebug() << "Apps - hash:" << hash;
        // Emit the signal to tell the MainWindow to update the UI and show the app with that particular hash value
        emit foregroundAppChanged(hash);
    }

} // fairwind::apps::launcherax10m
