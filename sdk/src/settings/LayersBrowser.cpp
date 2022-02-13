#include <QVBoxLayout>
#include <QJsonObject>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QJsonArray>
#include <QLabel>
#include <QDebug>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/settings/LayersBrowser.hpp>


void fairwind::ui::settings::LayersBrowser::setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto layersLayout = new QVBoxLayout;

    for (int j = 0; j < currentValue.toArray().size(); j++) {
        auto item = currentValue.toArray()[j].toObject();
        auto layer = fairWind->instanceLayer(item["class"].toString());

        if (layer != nullptr) {
            auto vLayout = new QVBoxLayout;
            auto hLayout = new QHBoxLayout;
            auto vWidget = new QWidget;
            auto hWidget = new QGroupBox;
            auto label = new QLabel;
            auto icon = new QLabel;
            auto description = new QLabel;

            icon->setPixmap(QPixmap::fromImage(layer->getIcon()));
            label->setText(item["name"].toString());
            label->setFont(QFont("", 14));

            description->setText(item["description"].toString());

            vLayout->addWidget(label);
            vLayout->addWidget(description);

            vWidget->setLayout(vLayout);
            vWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            hLayout->addWidget(icon);
            hLayout->addWidget(vWidget);

            hWidget->setLayout(hLayout);

            layersLayout->addWidget(hWidget);

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
            layersLayout->addWidget(settingsContainer);
        }
    }

    this->setLayout(layersLayout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::LayersBrowser::getNewInstance() {
    return static_cast<ISettings *>(new LayersBrowser());
}

QString fairwind::ui::settings::LayersBrowser::getClassName() {
    return this->metaObject()->className();
}