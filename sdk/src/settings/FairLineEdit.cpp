#include <QLineEdit>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <FairWindApp.hpp>

void fairwind::ui::settings::FairLineEdit::setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) {
    this->setFont(QFont("", 14));
    this->setText(currentValue.toString());

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [slot] (QString newValue) {
        slot(newValue);
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairLineEdit::getNewInstance() {
    return static_cast<ISettings *>(new FairLineEdit());
}

QString fairwind::ui::settings::FairLineEdit::getClassName() {
    return this->metaObject()->className();
}