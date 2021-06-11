//
// Created by Raffaele Montella on 11/06/21.
//

#include "FairWindSdk/layouts/GridLayout.hpp"

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/displays/DisplayBase.hpp>
#include <FairWindSdk/displays/DisplaySingleText.hpp>


fairwind::layouts::GridLayout::GridLayout(QWidget *parent) :
        QWidget(parent),
        LayoutBase() {

    mGridLayout = new QGridLayout();
    this->setLayout(mGridLayout);
}

fairwind::layouts::GridLayout::~GridLayout() {

}

QImage fairwind::layouts::GridLayout::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *fairwind::layouts::GridLayout::onSettings() {
    return nullptr;
}

void fairwind::layouts::GridLayout::onInit(QMap<QString, QVariant> params) {
    qDebug() << "GridLayout::onInit(" << params << ")";
}

fairwind::layouts::ILayout *fairwind::layouts::GridLayout::getNewInstance() {
    return static_cast<ILayout *>(new fairwind::layouts::GridLayout());
}

QString fairwind::layouts::GridLayout::getClassName() const {
    return this->metaObject()->className();
}

void fairwind::layouts::GridLayout::addDisplay(QString key, displays::IDisplay *display) {
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
            mGridLayout->addWidget(widget, row, col, rowSpan, colSpan);
        }
    }
}

QWidget *fairwind::layouts::GridLayout::getWidget() {
    return dynamic_cast<QWidget *>(this);
}
