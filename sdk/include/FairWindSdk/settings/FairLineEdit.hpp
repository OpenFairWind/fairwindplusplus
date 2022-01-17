//
// Created by debian on 12/1/21.
//

#ifndef FAIRWIND_FAIRLINEEDIT_HPP
#define FAIRWIND_FAIRLINEEDIT_HPP

#include <FairWindSdk/FairWindSDK.hpp>

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <QLineEdit>

namespace fairwind::ui::settings {
    /*
     * FairLineEdit
     * This widget is an editable line of text
     */
    class FAIRWINDSDK_LIB_DECL FairLineEdit : public QLineEdit, public ISettings {
    Q_OBJECT

    public:
        void setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    };
}

#endif //FAIRWIND_FAIRLINEEDIT_HPP
