//
// Created by Raffaele Montella on 16/07/21.
//

#include "Generic.hpp"
#include "ui_Generic.h"

fairwind::ui::settings::generic::Generic::Generic(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Generic) {
    ui->setupUi(this);
}

fairwind::ui::settings::generic::Generic::~Generic() {
    delete ui;
}

void fairwind::ui::settings::generic::Generic::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}




