//
// Created by Raffaele Montella on 10/06/21.
//

#include <QJsonObject>
#include <QWidget>
#include "FairWindSdk/layouts/LayoutBase.hpp"

fairwind::layouts::LayoutBase::LayoutBase() {

}

fairwind::layouts::LayoutBase::~LayoutBase() {

}

void fairwind::layouts::LayoutBase::addDisplay(QString key, fairwind::displays::IDisplay *display) {

    if (mLayouts.contains(key)) {
        auto widget = dynamic_cast<QWidget *>(display);
        if (widget) {
            mLayouts[key]->addWidget(widget);
        }
    }
}

void fairwind::layouts::LayoutBase::setUI(QString key, QLayout *layout) {
    mLayouts[key] = layout;
}
