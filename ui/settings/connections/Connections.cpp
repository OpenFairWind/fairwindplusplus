//
// Created by Raffaele Montella on 16/07/21.
//

#include "Connections.hpp"
#include "ui_Connections.h"

fairwind::ui::settings::connections::Connections::Connections(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Connections) {

    ui->setupUi(this);
}

fairwind::ui::settings::connections::Connections::~Connections() {
    delete ui;
}

void fairwind::ui::settings::connections::Connections::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}
