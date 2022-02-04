//
// Created by Raffaele Montella on 13/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Warning.h" resolved

#include <IFairWindApp.hpp>
#include <FairWindSdk/ui/Warning.hpp>
#include "ui_Warning.h"

namespace fairwind::ui {
    Warning::Warning(PageBase *parent, fairwind::apps::FairWindApp *appBase, QString message, QString details) :
            PageBase(parent, appBase), ui(new Ui::Warning) {
        ui->setupUi(this);

        ui->labelMessage->setText(message);
        ui->labelDetails->setText(details);

        connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&Warning::onAccepted);
    }

    Warning::~Warning() {
        delete ui;
    }

    void Warning::onAccepted() {
        getFairWindApp()->remove((PageBase *)this);
    }


} // fairwind::ui
