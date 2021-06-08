//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplayDoubleText.h"
#include <FairWindSdk/displays/DisplayDoubleText.hpp>


fairwind::displays::DisplayDoubleText::DisplayDoubleText(QWidget *parent) :
        ui(new Ui::DisplayDoubleText) {
    ui->setupUi(this);

}

fairwind::displays::DisplayDoubleText::~DisplayDoubleText() {
    delete ui;
}

QImage fairwind::displays::DisplayDoubleText::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::displays::DisplayDoubleText::onSettings() {
    return nullptr;
}

void fairwind::displays::DisplayDoubleText::onInit(QMap<QString, QVariant> params) {
    //qDebug() << "DisplaySingleText::onInit(" << params << ")";
}

fairwind::displays::IDisplay *fairwind::displays::DisplayDoubleText::getNewInstance() {
    return static_cast<IDisplay *>(new DisplayDoubleText());
}

void fairwind::displays::DisplayDoubleText::setLabel(QString label) {

    int size= contentsRect().height()*0.25;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Label->setFont(newFont);        //Set the new font with new size
    ui->label_Label->setText(label);
}

void fairwind::displays::DisplayDoubleText::setText1(QString text) {
    int size= contentsRect().height()*0.375;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Value1->setFont(newFont);        //Set the new font with new size
    ui->label_Value1->setText(text);
}

void fairwind::displays::DisplayDoubleText::setText2(QString text) {
    int size= contentsRect().height()*0.375;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Value2->setFont(newFont);
    ui->label_Value2->setText(text);
}

QString fairwind::displays::DisplayDoubleText::getClassName() const {
    return this->metaObject()->className();
}

bool fairwind::displays::DisplayDoubleText::smaller() { return isVisible(); }
bool fairwind::displays::DisplayDoubleText::bigger() { return isVisible(); }