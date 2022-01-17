#include <QHBoxLayout>
#include <QJsonObject>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QJsonArray>
#include <QLabel>
#include <QDebug>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/settings/DisplaysBrowser.hpp>
#include <FairWindApp.hpp>

void fairwind::ui::settings::DisplaysBrowser::setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto displaysLayout = new QVBoxLayout;

    for (int j = 0; j < currentValue.toArray().size(); j++) {
        auto item = currentValue.toArray()[j].toObject();
        auto display = fairWind->instanceDisplay(item["class"].toString());

        if (display != nullptr) {
            auto layout = new QHBoxLayout;
            auto widget = new QGroupBox;
            auto label = new QLabel;
            auto icon = new QLabel;
            auto checkBox = new QCheckBox;

            icon->setPixmap(QPixmap::fromImage(display->getIcon()));
            label->setText(item["class"].toString());
            label->setFont(QFont("", 14));
            label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            layout->addWidget(icon);
            layout->addWidget(label);

            widget->setLayout(layout);

            displaysLayout->addWidget(widget);

            auto settingsContainer = new QWidget;
            auto layout2 = new QGridLayout;

            for (int i = 0; i < item.keys().size(); i++) {
                QString key = item.keys()[i];
                QJsonValue currentValue2 = item[key];

                auto label = new QLabel(key + ":");
                label->setFont(QFont("", 12));
                // Add the label
                layout2->addWidget(label, i, 0);

                if (currentValue2.isString()) {
                    auto valueWidget = new QLineEdit(currentValue2.toString());
                    // Add the widget to the container
                    layout2->addWidget(valueWidget, i, 1);

                    connect(valueWidget, &QLineEdit::textChanged, this, [j, key, currentValue, valueWidget, slot](QString newValue) {
                        QJsonValueRef item = currentValue.toArray()[j];
                        QJsonValueRef ref = item.toObject()[key];

                        ref = newValue;

                        slot(currentValue);
                    });
                } else if (currentValue2.isBool()) {
                    auto valueWidget = new QCheckBox;

                    if (currentValue2.toBool())
                        valueWidget->setCheckState(Qt::CheckState::Checked);
                    else
                        valueWidget->setCheckState(Qt::CheckState::Unchecked);

                    // Add the label
                    layout2->addWidget(label, i, 0);
                    // Add the widget to the container
                    layout2->addWidget(valueWidget, i, 1);

                    connect(valueWidget, &QCheckBox::stateChanged, this, [j, key, currentValue, valueWidget, slot]() {
                        QJsonValueRef item = currentValue.toArray()[j];
                        QJsonValueRef ref = item.toObject()[key];

                        ref = valueWidget->checkState() == 2 ? true : false;

                        slot(currentValue);
                    });
                } else if (currentValue2.isDouble()) {
                    auto valueWidget = new QSpinBox();
                    // Add the widget to the container
                    layout2->addWidget(valueWidget, i, 1);

                    valueWidget->setValue(currentValue2.toInt());

                    connect(valueWidget, static_cast<void (QSpinBox::*)(int i)>(&QSpinBox::valueChanged), this, [j, key, currentValue, valueWidget, slot]() {
                        QJsonValueRef item = currentValue.toArray()[j];
                        QJsonValueRef ref = item.toObject()[key];

                        ref = valueWidget->value();

                        slot(currentValue);
                    });
                }
            }

            settingsContainer->setLayout(layout2);
            displaysLayout->addWidget(settingsContainer);
        }
    }

    this->setLayout(displaysLayout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::DisplaysBrowser::getNewInstance() {
    return static_cast<ISettings *>(new DisplaysBrowser());
}

QString fairwind::ui::settings::DisplaysBrowser::getClassName() {
    return this->metaObject()->className();
}