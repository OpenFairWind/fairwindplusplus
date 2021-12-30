#include <QComboBox>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairComboBox.hpp>

void fairwind::ui::settings::FairComboBox::setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IApp* extension) {
    auto config = extension->getConfig();
    // Get the settings possible values
    auto domain = settings["domain"].toArray();

    this->setFont(QFont("", 14));

    // Add the current value
    this->addItem(config[settingsID].toString());

    // Add the remaining values from the domain
    for (auto && j : domain) {
        if (j.toObject()["key"].toString() != config[settingsID].toString())
            this->addItem(j.toObject()["key"].toString());
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