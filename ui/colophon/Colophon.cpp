//
// Created by Raffaele Montella on 08/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Colophon.h" resolved

#include "Colophon.hpp"
#include "ui_Colophon.h"

namespace fairwind::ui::colophon {
    Colophon::Colophon(QWidget *parent) :
            QDialog(parent), ui(new Ui::Colophon) {
        ui->setupUi(this);
    }

    Colophon::~Colophon() {
        delete ui;
    }
} // fairwind::ui::colophon
