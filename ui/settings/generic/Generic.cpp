//
// Created by Raffaele Montella on 16/07/21.
//

#include <FairWindSdk/FairWind.hpp>

#include "Generic.hpp"
#include "ui_Generic.h"

/*
 * Generic
 * Public constructor - This presents the generic settings inside a tab
 */
fairwind::ui::settings::generic::Generic::Generic(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Generic) {
    // Setup th the UI
    ui->setupUi(this);
}

/*
 * ~Generic
 * Generic's destructor
 */
fairwind::ui::settings::generic::Generic::~Generic() {
    delete ui;
}

/*
 * showEvent
 * Method called when the tab has to be shown
 */
void fairwind::ui::settings::generic::Generic::showEvent(QShowEvent *event) {
    qDebug() << "fairwind::ui::settings::generic::Generic::showEvent";

    // Continue with the regular showEvent
    QWidget::showEvent(event);
}

/*
 * getIcon
 * Returns a QImage containing the generic settings icon
 */
QImage fairwind::ui::settings::generic::Generic::getIcon() const {
    return QImage(":resources/images/icons/generic_icon.png");
}

/*
 * getName
 * Return a string containing the generic settings name
 */
QString fairwind::ui::settings::generic::Generic::getName() const {
    return tr("Generic");
}

/*
 * getNewInstance
 * Returns a new instance of Generic
 */
fairwind::ui::settings::ISettings *fairwind::ui::settings::generic::Generic::getNewInstance() {
    return static_cast<ISettings *>(new Generic());
}

/*
 * getClassName
 * Returns the current Generic instance class name
 */
QString fairwind::ui::settings::generic::Generic::getClassName() const {
    return this->metaObject()->className();
}