//
// Created by Raffaele Montella on 13/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QTableWidgetItem>
#include <ui/settings/connections/Connections.hpp>
#include <ui/settings/applications/Applications.hpp>
#include <ui/settings/generic/Generic.hpp>
#include "Settings.hpp"
#include "ui_Settings.h"


fairwind::ui::settings::Settings::Settings(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Settings) {

    ui->setupUi(this);

    FairWind *fairWind = FairWind::getInstance();

    for (const auto settings: *(fairWind->getSettings())) {
        ui->tabWidget->addTab(dynamic_cast<QWidget *>(settings), settings->getName());
    }
}

fairwind::ui::settings::Settings::~Settings() {
    delete ui;
}

void fairwind::ui::settings::Settings::showEvent(QShowEvent *e)
{
}
