#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairComboBox.hpp>

void fairwind::ui::settings::FairComboBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    // Get the settings ID
    auto settingsID = settings["id"].toString();

    // Get the settings possible values
    auto domain = settings["domain"].toArray();

    this->setFont(QFont("", 14));
    this->setStyleSheet("background:#404040");

    // Add the current value
    this->addItem(values[settingsID].toString());

    // Add the remaining values from the domain
    for (auto && j : domain) {
        if (j.toString() != values[settingsID].toString())
            this->addItem(j.toString());
    }

    // When the current value changes, call the updateSettings method to save the changes
    connect(comboBox,static_cast<void (QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), this, [settingsID, extension]() {
        extension->updateSettings(settingsID, this->currentText());
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairComboBox::getNewInstance() {
    return static_cast<ISettings *>(new FairComboBox());
}

QString fairwind::ui::settings::FairComboBox::getClassName() {
    return this->metaObject()->className();
}