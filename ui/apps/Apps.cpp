//
// Created by Raffaele Montella on 13/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QScreen>
#include <QRect>

#include "Apps.hpp"
#include "ui_Apps.h"

/*
 * Apps
 * Public constructor - This will present the available apps in FairWind
 */
fairwind::ui::apps::Apps::Apps(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Apps) {
    // Setup the UI
    ui->setupUi(this);

    // Create a new grid layout
    auto *layout = new QGridLayout(ui->scrollAreaWidgetContents);
    auto scrollArea = ui->scrollArea;
    // Set the UI scroll area with the newly created layout
    ui->scrollAreaWidgetContents->setLayout(layout);

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
    auto apps = fairWind->getApps();

    QRect rec = QGuiApplication::primaryScreen()->geometry();

    int size = ((64 * rec.height()) / 480) * (rec.height() / 480);

    // Iterate on the available apps' hash values
    for (auto &hash: apps.keys()) {
        // Get the hash value
        auto app = apps[hash];
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
            button->setIconSize(QSize(size, size));
            // Set the button's style to have an icon and some text beneath it
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            // Launch the app when the button is clicked
            connect(button, &QToolButton::released, this, &Apps::toolButton_App_released);

            // Add the newly created button to the grid layout as a widget
            layout->addWidget(button, row, col);
        }

        row++;
        if (row == rows) {
            row = 0;
            col++;
        }
    }

    connect(buttonLeft, static_cast<void (QToolButton::*)(bool state)>(&QToolButton::clicked), this, [scrollArea]() {
        scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() + 10);
    })
}

/*
 * ~Apps
 * Apps' destructor
 */
fairwind::ui::apps::Apps::~Apps() {
    delete ui;
}

/*
 * toolButton_App_released
 * Method called when the user wants to launch an app
 */
void fairwind::ui::apps::Apps::toolButton_App_released() {
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
