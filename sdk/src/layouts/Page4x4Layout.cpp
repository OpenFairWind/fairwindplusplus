//
// Created by Raffaele Montella on 10/06/21.
//

#include "FairWindSdk/layouts/Page4x4Layout.hpp"

#include "ui_Page4x4Layout.h"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>


fairwind::layouts::Page4x4Layout::Page4x4Layout(QWidget *parent) :
        QWidget(parent),
        LayoutBase(),
        ui(new Ui::Page4x4Layout) {
    ui->setupUi(this);
}

fairwind::layouts::Page4x4Layout::~Page4x4Layout() {
    delete ui;
}

QImage fairwind::layouts::Page4x4Layout::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::layouts::Page4x4Layout::onSettings() {
    return nullptr;
}

void fairwind::layouts::Page4x4Layout::onInit(QMap<QString, QVariant> params) {
    qDebug() << "Page4x4Layout::onInit(" << params << ")";
}

fairwind::layouts::ILayout *fairwind::layouts::Page4x4Layout::getNewInstance() {
    return static_cast<ILayout *>(new fairwind::layouts::Page4x4Layout());
}

QString fairwind::layouts::Page4x4Layout::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::layouts::Page4x4Layout::addDisplay(QString key, displays::IDisplay *display) {
    auto parts = key.split(",");
    if (parts.size()>=2) {
        int rowSpan=1;
        int colSpan=1;
        int row = parts[0].toInt();
        int col = parts[1].toInt();
        if (parts.size()==4) {
            rowSpan=parts[2].toInt();
            colSpan=parts[3].toInt();
        }
        auto widget = dynamic_cast<QWidget *>(display);
        if (widget) {
            ui->gridLayout->addWidget(widget, row, col, rowSpan, colSpan);
        }
    }
    //LayoutBase::addDisplay(key, display);
}

QWidget *fairwind::layouts::Page4x4Layout::getWidget() {
    return dynamic_cast<QWidget *>(this);;
}
