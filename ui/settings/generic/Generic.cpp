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

QImage fairwind::ui::settings::generic::Generic::getIcon() const {
    return QImage(":resources/images/icons/generic_icon.png");
}

QString fairwind::ui::settings::generic::Generic::getName() const {
    return tr("Generic");
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::generic::Generic::getNewInstance() {
    return static_cast<ISettings *>(new Generic());
}

QString fairwind::ui::settings::generic::Generic::getClassName() const {
    return this->metaObject()->className();
}


