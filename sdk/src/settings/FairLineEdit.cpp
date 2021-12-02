#include <FairWindSdk/FairWind.hpp>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairLineEdit::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    // Get the settings ID
    auto settingsID = settings["id"].toString();

    // Set the current value
    this->setText(values[settingsID].toString());

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [settingsID, extension](QString newValue) {
        extension->updateSettings(settingsID, newValue);
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairLineEdit::getNewInstance() {
    return static_cast<ISettings *>(new FairLineEdit());
}

QString fairwind::ui::settings::FairLineEdit::getClassName() {
    return this->metaObject()->className();
}