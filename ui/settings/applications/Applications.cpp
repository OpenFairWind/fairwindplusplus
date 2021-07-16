//
// Created by Raffaele Montella on 16/07/21.
//

#include "Applications.hpp"
#include "ui_Applications.h"

fairwind::ui::settings::applications::Applications::Applications(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Applications) {
    ui->setupUi(this);
}

fairwind::ui::settings::applications::Applications::~Applications() {
    delete ui;
}

void fairwind::ui::settings::applications::Applications::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}


