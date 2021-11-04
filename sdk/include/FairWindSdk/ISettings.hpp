//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_ISETTINGS_HPP
#define FAIRWIND_ISETTINGS_HPP

namespace fairwind::ui::settings {
    /*
     * ISettings
     * Interface to build new settings pages for FairWind
     */
    class ISettings {
    public:
        virtual ~ISettings() = default;

        // Returns the settings page's icon
        virtual QImage getIcon() const = 0;

        // Returns the settings page's name
        virtual QString getName() const = 0;

        // Returns a newly created instance
        virtual ISettings *getNewInstance() = 0;

        // Returns the settings page's class name
        virtual QString getClassName() const = 0;
    };
}

#endif //FAIRWIND_ISETTINGS_HPP