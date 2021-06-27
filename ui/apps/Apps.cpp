//
// Created by Raffaele Montella on 13/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include "Apps.hpp"
#include "ui_Apps.h"


Apps::Apps(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Apps) {

    ui->setupUi(this);


    QGridLayout *layout = new QGridLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(layout);


    int cols=4,rows=2;

    for(int col=0;col<cols;col++) {
        layout->setColumnMinimumWidth(col, 64);
    }
    for(int row=0;row<rows;row++) {
        layout->setRowMinimumHeight(row, 64);
    }


    int row=0, col=0, page=0;



    auto fairWind=fairwind::FairWind::getInstance();
    auto apps=fairWind->getApps();

    for (auto &hash : apps.keys()) {
        auto app=apps[hash];
        if (app->getActive()) {
            qDebug() << "Apps::Apps name:" << app->getName();
            auto *button = new QToolButton();
            button->setObjectName("toolbutton_"+hash);
            button->setText(app->getName());
            QImage icon=app->getIcon();
            button->setIcon(QPixmap::fromImage(icon));
            button->setIconSize(QSize(256,256));
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            connect(button, &QToolButton::released, this, &Apps::toolButton_App_released);

            layout->addWidget(button,row,col);
        }

        row++;
        if (row==rows) {
            row=0;
            col++;
        }
    }
}




Apps::~Apps() {
    delete ui;
}


void Apps::toolButton_App_released()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget) {
        return;
    }

    QString hash=buttonWidget->objectName().replace("toolbutton_","");
    qDebug() << "Apps - hash:" << hash;
    emit foregroundAppChanged(hash);


}
