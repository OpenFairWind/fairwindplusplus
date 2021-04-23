//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplayDoubleText.h"
#include "DisplayDoubleText.hpp"

DisplayDoubleText::DisplayDoubleText(QWidget *parent) :
        DisplaySingleText(parent),
        ui(new Ui::DisplayDoubleText) {
    ui->setupUi(parent);

}

DisplayDoubleText::~DisplayDoubleText() {
    delete ui;
}



void DisplayDoubleText::setText2(QString text) {
    ui->label_Value2->setText(text);
}