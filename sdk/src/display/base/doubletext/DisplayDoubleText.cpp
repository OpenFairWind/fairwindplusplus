//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplayDoubleText.h"
#include <FairWindSdk/DisplayDoubleText.hpp>

DisplayDoubleText::DisplayDoubleText(QWidget *parent) :
        ui(new Ui::DisplayDoubleText) {
    ui->setupUi(this);

}

DisplayDoubleText::~DisplayDoubleText() {
    delete ui;
}

void DisplayDoubleText::setLabel(QString label) {

    int size= contentsRect().height()*0.25;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Label->setFont(newFont);        //Set the new font with new size
    ui->label_Label->setText(label);
}

void DisplayDoubleText::setText1(QString text) {
    int size= contentsRect().height()*0.375;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Value1->setFont(newFont);        //Set the new font with new size
    ui->label_Value1->setText(text);
}

void DisplayDoubleText::setText2(QString text) {
    int size= contentsRect().height()*0.375;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Value2->setFont(newFont);
    ui->label_Value2->setText(text);
}