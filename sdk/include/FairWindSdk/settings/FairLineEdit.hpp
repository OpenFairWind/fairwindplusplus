//
// Created by debian on 12/1/21.
//

#ifndef FAIRWIND_FAIRLINEEDIT_HPP
#define FAIRWIND_FAIRLINEEDIT_HPP

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IApp.hpp>
#include <QLineEdit>

namespace fairwind::ui::settings {
    /*
     * FairLineEdit
     * This widget is an editable line of text
     */
    class FairLineEdit : public QLineEdit, public ISettings {
        Q_OBJECT

    public:
        void setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    };
}

#endif //FAIRWIND_FAIRLINEEDIT_HPP
