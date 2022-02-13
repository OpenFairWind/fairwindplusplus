#include <QCheckBox>
#include <QString>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <FairWindApp.hpp>

void fairwind::ui::settings::FairCheckBox::setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) {
    // Set the checkbox's state according to the current value
    if (currentValue.toInt() == 0)
        this->setCheckState(Qt::CheckState::Unchecked);
    else
        this->setCheckState(Qt::CheckState::Checked);

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [this, slot]() {
        slot(this->checkState());
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairCheckBox::getNewInstance() {
    return static_cast<ISettings *>(new FairCheckBox());
}

QString fairwind::ui::settings::FairCheckBox::getClassName() {
    return this->metaObject()->className();
}