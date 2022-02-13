//
// Created by Ciro De Vita on 28/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Displays.h" resolved

#include "Displays.hpp"
#include "ui_Displays.h"

namespace fairwind::apps::settings::browser {
    Displays::Displays(QWidget *parent) :
            QWidget(parent), ui(new Ui::Displays) {
        ui->setupUi(this);
    }

    Displays::~Displays() {
        delete ui;
    }

    fairwind::ui::settings::ISettings *Displays::getNewInstance() {
        return static_cast<ISettings *>(new Displays());
    }

    QString Displays::getClassName() {
        return this->metaObject()->className();
    }

    void Displays::setDetails(std::function<void(QVariant)> slot, QJsonObject details, QJsonValue currentValue) {

    }
} // fairwind::apps::settings::browser
