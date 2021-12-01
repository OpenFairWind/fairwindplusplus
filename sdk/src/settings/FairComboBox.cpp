
#include <FairWindSdk/FairWind.hpp>
#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>

#include <FairWindSdk/settings/FairComboBox.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairComboBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    // Get the settings ID
    auto settingsID = settings["id"].toString();

    // Get the settings possible values
    auto domain = settings["domain"].toArray();

    // Add the current value
    this->addItem(values[settingsID].toString());

    // Add the remaining values from the domain
    for (int j = 0; j < domain.size(); j++) {
        if (domain[j].toString() != values[settingsID].toString())
            this->addItem(domain[j].toString());
    }

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), this, [settingsID, extension, this]() {
        extension->updateSettings(settingsID, this->currentText());
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairComboBox::getNewInstance() {
    return static_cast<ISettings *>(new FairComboBox());
}

QString fairwind::ui::settings::FairComboBox::getClassName() {
    return this->metaObject()->className();
}