//
// Created by Raffaele Montella on 13/04/21.
//

#include <QTableWidgetItem>

#include <FairWindSdk/FairWind.hpp>
#include <ui/settings/connections/Connections.hpp>
#include <ui/settings/applications/Applications.hpp>
#include <ui/settings/generic/Generic.hpp>

#include "Settings.hpp"
#include "ui_Settings.h"

/*
 * Settings
 * Public constructor - This presents a view organised in tabs
 */
fairwind::ui::settings::Settings::Settings(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Settings) {
    // Setup the UI
    ui->setupUi(this);

    // Get the singleton instance of FairWind
    FairWind *fairWind = FairWind::getInstance();

    // Get the registered settings pages from the FairWind instance itself
    for (const auto settings: *(fairWind->getSettingsList())) {
        // Add a new tab for each page
        ui->tabWidget->addTab(dynamic_cast<QWidget *>(settings), settings->getName());
    }
}

/*
 * ~Settings
 * Settings' destructor
 */
fairwind::ui::settings::Settings::~Settings() {
    delete ui;
}

/*
 * showEvent
 * *** to be implemented ***
 */
void fairwind::ui::settings::Settings::showEvent(QShowEvent *e) {}