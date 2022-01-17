//
// Created by debian on 11/30/21.
//

#ifndef FAIRWIND_FAIRCOMBOBOX_HPP
#define FAIRWIND_FAIRCOMBOBOX_HPP

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <QComboBox>
#include <QString>

namespace fairwind::ui::settings {
    /*
     * FairComboBoxqmake
     * This widget is a combo box and presents a dropwdown list of options
     */
    class FAIRWINDSDK_LIB_DECL FairComboBox : public QComboBox, public ISettings {
    Q_OBJECT

    public:
        void setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    };
}

#endif //FAIRWIND_FAIRCOMBOBOX_HPP
