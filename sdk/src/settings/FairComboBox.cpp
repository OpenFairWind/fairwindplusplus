#include <QComboBox>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QGridLayout>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/settings/FairComboBox.hpp>
#include <FairWindApp.hpp>

void fairwind::ui::settings::FairComboBox::setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) {
    // Get the settings possible values
    auto domain = details["domain"].toArray();

    this->setFont(QFont("", 14));

    // Add the current value
    this->addItem(currentValue.toString());

    // Add the remaining values from the domain
    for (auto && j : domain) {
        if (j.toObject()["key"] != currentValue)
            this->addItem(j.toObject()["key"].toString());
    }

    connect(this, static_cast<void (FairComboBox::*)(int index)>(&FairComboBox::currentIndexChanged), this, [this, slot]() {
        slot(this->currentText());
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairComboBox::getNewInstance() {
    return static_cast<ISettings *>(new FairComboBox());
}

QString fairwind::ui::settings::FairComboBox::getClassName() {
    return this->metaObject()->className();
}