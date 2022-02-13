//
// Created by Raffaele Montella on 13/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Warning.h" resolved

#include <IFairWindApp.hpp>
#include <FairWindSdk/ui/Warning.hpp>
#include "ui_Warning.h"

namespace fairwind::ui {
    Warning::Warning(PageBase *parent, const QString &message, const QString &details) :
            PanelBase(parent), ui(new Ui::Warning) {

        // Setup the UI
        ui->setupUi(this);

        ui->labelMessage->setText(message);
        ui->labelDetails->setText(details);

        connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&PanelBase::onAccepted);
    }

    Warning::~Warning() {
        delete ui;
    }

} // fairwind::ui
