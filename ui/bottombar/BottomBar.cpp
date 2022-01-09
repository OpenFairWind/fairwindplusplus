//
// Created by Raffaele Montella on 12/04/21.
//

#include <ui_BottomBar.h>
#include <FairWindSdk/FairWind.hpp>

#include "BottomBar.hpp"

/*
 * BottomBar
 * Public constructor - This presents some navigation buttons at the bottom of the screen
 */
fairwind::ui::bottombar::BottomBar::BottomBar(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BottomBar) {
    // Setup the UI
    ui->setupUi(parent);

    // emit a signal when the Apps tool button from the UI is clicked
    connect(ui->toolButton_Apps, &QToolButton::released, this, &BottomBar::apps_clicked);
    // emit a signal when the Settings tool button from the UI is clicked
    connect(ui->toolButton_Settings, &QToolButton::released, this, &BottomBar::settings_clicked);
}

/*
 * settings_clicked
 * Method called when the user wants to view the settings screen
 */
void fairwind::ui::bottombar::BottomBar::settings_clicked() {
    // Emit the signal to tell the MainWindow to update the UI and show the settings screen
    emit setSettings();
}

/*
 * apps_clicked
 * Method called when the user wants to view the apps screen
 */
void fairwind::ui::bottombar::BottomBar::apps_clicked() {
    // Emit the signal to tell the MainWindow to update the UI and show the apps screen
    emit setApps();
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();
    signalKDocument->save("signalkmodel.json");
}

/*
 * ~BottomBar
 * BottomBar's destructor
 */
fairwind::ui::bottombar::BottomBar::~BottomBar() {
    delete ui;
}