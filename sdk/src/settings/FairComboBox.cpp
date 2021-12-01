
#include <FairWindSdk/FairWind.hpp>
#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>

#include <FairWindSdk/settings/FairComboBox.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairComboBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto settingsID = settings["id"].toString();

    auto domain = settings["domain"].toArray();

    this->addItem(values[settingsID].toString());

    for (int j = 0; j < domain.size(); j++) {
        if (domain[j].toString() != values[settingsID].toString())
            this->addItem(domain[j].toString());
    }

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