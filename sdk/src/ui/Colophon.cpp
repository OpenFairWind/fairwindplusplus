//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ColophonPage.h" resolved

#include <IFairWindApp.hpp>
#include <FairWindSdk/ui/Colophon.hpp>
#include "ui_Colophon.h"


namespace fairwind::ui {

    Colophon::Colophon(PageBase *parent) :
            PanelBase(parent), ui(new Ui::Colophon) {
        ui->setupUi(this);

        connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&PanelBase::onAccepted);
    }

    void Colophon::onAdded() {
        auto appBase = getFairWindApp();

        ui->labelName->setText(appBase->getName());
        ui->labelDesc->setText(appBase->getDesc());
        ui->labelVersion->setText(appBase->getVersion());
        ui->labelCopyright->setText(appBase->getCopyright());
        ui->labelLicense->setText(appBase->getLicense());
        ui->labelVendor->setText(appBase->getVendor());
        ui->toolButtonIcon->setIcon(QPixmap::fromImage(appBase->getIcon()));
    }

    Colophon::~Colophon() {
        delete ui;
    }


} // fairwind::apps::imsf
