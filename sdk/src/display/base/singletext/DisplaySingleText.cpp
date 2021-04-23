//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"
#include "DisplaySingleText.hpp"


DisplaySingleText::DisplaySingleText(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplaySingleText) {
    ui->setupUi(parent);

}

DisplaySingleText::~DisplaySingleText() {
    delete ui;
}

void DisplaySingleText::setLabel(QString label) {
    ui->label_Label->setText(label);
}

void DisplaySingleText::setText1(QString text) {
    ui->label_Value1->setText(text);
}
