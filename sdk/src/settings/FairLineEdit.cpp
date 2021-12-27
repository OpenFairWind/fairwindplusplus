#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <QLabel>
#include <QGridLayout>
#include <utility>

void fairwind::ui::settings::FairLineEdit::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto layout = new QGridLayout;
    // Get the settings ID
    auto settingsID = settings["id"].toString();
    // Create a label
    auto label = new QLabel(settings["displayName"].toString() + ":");
    auto lineEdit = new QLineEdit;

    QFont font = QFont("", 20);

    label->setFont(font);
    lineEdit->setFont(font);
    lineEdit->setText(values[settingsID].toString());

    // When the current value changes, call the updateSettings method to save the changes
    connect(lineEdit,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [settingsID, extension](QString newValue) {
        extension->updateSettings(settingsID, std::move(newValue));
    });

    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 0, 1);

    layout->setColumnStretch(0, 10);
    layout->setColumnStretch(1, 20);

    this->setLayout(layout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairLineEdit::getNewInstance() {
    return static_cast<ISettings *>(new FairLineEdit());
}

QString fairwind::ui::settings::FairLineEdit::getClassName() {
    return this->metaObject()->className();
}