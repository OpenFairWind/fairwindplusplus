//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_ISETTINGS_HPP
#define FAIRWIND_ISETTINGS_HPP

namespace fairwind::ui::settings {

    class ISettings {
    public:
        virtual ~ISettings() = default;

        virtual QImage getIcon() const = 0;
        virtual QString getName() const = 0;
        virtual ISettings *getNewInstance()  = 0;
        virtual QString getClassName() const = 0;
    };

}

#endif //FAIRWIND_ISETTINGS_HPP
