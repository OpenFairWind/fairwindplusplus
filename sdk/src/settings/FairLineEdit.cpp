#include <QLineEdit>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairLineEdit.hpp>

void fairwind::ui::settings::FairLineEdit::setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IApp* extension) {
    auto config = extension->getConfig();

    this->setFont(QFont("", 14));
    this->setText(config[settingsID].toString());

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [settingsID, extension](QString newValue) {
        extension->updateSettings(settingsID, std::move(newValue));
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairLineEdit::getNewInstance() {
    return static_cast<ISettings *>(new FairLineEdit());
}

QString fairwind::ui::settings::FairLineEdit::getClassName() {
    return this->metaObject()->className();
}