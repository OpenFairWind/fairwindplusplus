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

    ui->tabWidget->addTab(new ui::settings::generic::Generic(),"Generic");
    ui->tabWidget->addTab(new ui::settings::connections::Connections(),"Connections");
    ui->tabWidget->addTab(new ui::settings::applications::Applications(), "Applications");

}

fairwind::ui::settings::Settings::~Settings() {
    delete ui;
}

void fairwind::ui::settings::Settings::showEvent(QShowEvent *e)
{



}
