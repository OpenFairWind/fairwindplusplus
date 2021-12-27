//
// Created by debian on 11/30/21.
//

#ifndef FAIRWIND_FAIRCOMBOBOX_HPP
#define FAIRWIND_FAIRCOMBOBOX_HPP

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IApp.hpp>
#include <QComboBox>

namespace fairwind::ui::settings {
    /*
     * FairComboBox
     * This widget is a combo box and presents a dropwdown list of options
     */
    class FairComboBox : public QWidget, public ISettings {
    Q_OBJECT

    public:
        void setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    };
}

#endif //FAIRWIND_FAIRCOMBOBOX_HPP
