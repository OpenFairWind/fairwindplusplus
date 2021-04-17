//
// Created by Raffaele Montella on 13/04/21.
//

#include <core/FairWind.hpp>
#include "Settings.hpp"
#include "ui_Settings.h"


Settings::Settings(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Settings) {

    ui->setupUi(this);
}

Settings::~Settings() {
    delete ui;
}
