//
// Created by Raffaele Montella on 12/04/21.
//

#include "TopBar.hpp"
#include "ui_TopBar.h"

TopBar::TopBar(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TopBar) {
    ui->setupUi(parent);
}

TopBar::~TopBar() {
    delete ui;
}
