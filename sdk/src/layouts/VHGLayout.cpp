//
// Created by Raffaele Montella on 10/06/21.
//

#include <QJsonArray>

#include "FairWindSdk/layouts/VHGLayout.hpp"
#include "ui_VHGLayout.h"

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>

fairwind::layouts::VHGLayout::VHGLayout(QWidget *parent) :
        QWidget(parent),
        LayoutBase(),
        ui(new Ui::VHGLayout) {
    // Setup the UI
    ui->setupUi(this);
    // Remember the available layouts
    setUI("vertical", ui->verticalLayout);
    setUI("horizontal", ui->horizontalLayout);
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

void fairwind::layouts::VHGLayout::onInit(QMap <QString, QVariant> params) {
    qDebug() << "VHGLayout::onInit(" << params << ")";
}

fairwind::layouts::ILayout *fairwind::layouts::VHGLayout::getNewInstance() {
    return static_cast<ILayout *>(new fairwind::layouts::VHGLayout());
}

QString fairwind::layouts::VHGLayout::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::layouts::VHGLayout::addDisplay(QString key, displays::IDisplay *display) {
    // Check if the new layout is a grid layout
    if (key.startsWith("grid")) {
        int rowSpan = 1;
        int colSpan = 1;
        auto parts = key.split(",");
        int row = parts[1].toInt();
        int col = parts[2].toInt();
        if (parts.size() == 5) {
            rowSpan = parts[3].toInt();
            colSpan = parts[4].toInt();
        }
        // Cast display to QWidget*
        auto widget = dynamic_cast<QWidget *>(display);
        // Check if the new widget is valid
        if (widget) {
            // Add the widget to the gridlayout
            ui->gridLayout->addWidget(widget, row, col, rowSpan, colSpan);
        }

    } else {
        // Add the display to the VHGLayout
        LayoutBase::addDisplay(key, display);
    }
}

QWidget *fairwind::layouts::VHGLayout::getWidget() {
    return dynamic_cast<QWidget *>(this);;
}