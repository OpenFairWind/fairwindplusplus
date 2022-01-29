//
// Created by Ciro De Vita on 28/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_DISPLAYS_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_DISPLAYS_HPP

#include <QWidget>
#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IFairWindApp.hpp>

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Displays; }
    QT_END_NAMESPACE

class Displays : public QWidget, fairwind::ui::settings::ISettings {
    Q_OBJECT

    public:
        explicit Displays(QWidget *parent = nullptr);

        ~Displays() override;

        void setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) override;

        ISettings* getNewInstance() override;

        QString getClassName() override;

    private:
        Ui::Displays *ui;
    };
} // fairwind::apps::settings::browser

#endif //FAIRWIND_APPS_SETTINGS_BROWSER_DISPLAYS_HPP
