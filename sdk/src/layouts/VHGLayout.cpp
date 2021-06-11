//
// Created by Raffaele Montella on 10/06/21.
//

#include "FairWindSdk/layouts/VHGLayout.hpp"

#include "ui_VHGLayout.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>


fairwind::layouts::VHGLayout::VHGLayout(QWidget *parent) :
        QWidget(parent),
        LayoutBase(),
        ui(new Ui::VHGLayout) {
    ui->setupUi(this);
    setUI("vertical",ui->verticalLayout);
    setUI("horizontal",ui->horizontalLayout);
}

fairwind::layouts::VHGLayout::~VHGLayout() {
    delete ui;
}

QImage fairwind::layouts::VHGLayout::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::layouts::VHGLayout::onSettings() {
    return nullptr;
}

void fairwind::layouts::VHGLayout::onInit(QMap<QString, QVariant> params) {
    qDebug() << "VHGLayout::onInit(" << params << ")";
}

fairwind::layouts::ILayout *fairwind::layouts::VHGLayout::getNewInstance() {
    return static_cast<ILayout *>(new fairwind::layouts::VHGLayout());
}

QString fairwind::layouts::VHGLayout::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::layouts::VHGLayout::addDisplay(QString key, displays::IDisplay *display) {
    if (key.startsWith("grid")) {
        int rowSpan=1;
        int colSpan=1;
        auto parts=key.split(",");
        int row=parts[1].toInt();
        int col=parts[2].toInt();
        if (parts.size()==5) {
            rowSpan=parts[3].toInt();
            colSpan=parts[4].toInt();
        }
        auto widget = dynamic_cast<QWidget *>(display);
        if (widget) {
            ui->gridLayout->addWidget(widget,row,col,rowSpan,colSpan);
        }

    } else {
        LayoutBase::addDisplay(key, display);
    }
}

QWidget *fairwind::layouts::VHGLayout::getWidget() {
    return dynamic_cast<QWidget *>(this);;
}
