//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Flag.h" resolved

#include <QJsonObject>
#include "Flag.hpp"
#include "ui_Flag.h"

namespace fairwind::apps::imsf {
    Flag::Flag(QWidget *parent, QJsonObject jsonObject) :
            QWidget(parent), ui(new Ui::Flag) {
        ui->setupUi(this);
        if (jsonObject.contains("resource") && jsonObject["resource"].isString()) {
            QString resource = jsonObject["resource"].toString();
            ui->label_Image->setPixmap(QPixmap::fromImage(QImage(resource)));
        }
        if (jsonObject.contains("letter") && jsonObject["letter"].isString()) {
            QString letter = jsonObject["letter"].toString();
            ui->label_Letter->setText(letter);
        }
        if (jsonObject.contains("codeWord") && jsonObject["codeWord"].isString()) {
            QString codeWord = jsonObject["codeWord"].toString();
            ui->label_CodeWord->setText(codeWord);
        }
        if (jsonObject.contains("pronunciation") && jsonObject["pronunciation"].isString()) {
            QString pronunciation = jsonObject["pronunciation"].toString();
            ui->label_Pronunciation->setText(pronunciation);
        }
    }

    Flag::~Flag() {
        delete ui;
    }
} // fairwind::apps::imsf
