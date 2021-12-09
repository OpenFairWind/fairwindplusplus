//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_ISETTINGSTAB_HPP
#define FAIRWIND_ISETTINGSTAB_HPP

namespace fairwind::ui::settings {
    /*
     * ISettingsTab
     * Interface to build new settings pages for FairWind
     */
    class ISettingsTab {
    public:
        virtual ~ISettingsTab() = default;

        // Returns the settings page's icon
        virtual QImage getIcon() const = 0;

        // Returns the settings page's name
        virtual QString getName() const = 0;

        // Returns a newly created instance
        virtual ISettingsTab *getNewInstance() = 0;

        // Returns the settings page's class name
        virtual QString getClassName() const = 0;
    };
}

#endif //FAIRWIND_ISETTINGSTAB_HPP