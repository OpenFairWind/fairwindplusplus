//
// Created by Raffaele Montella on 02/06/21.
//

#ifndef FAIRWIND_IDISPLAY_HPP
#define FAIRWIND_IDISPLAY_HPP

namespace fairwind::displays {
    /*
     * IDisplay
     * Interface to build new widgets containing useful infos in FairWind
     */
    class IDisplay {
    public:
        virtual ~IDisplay() = default;

        // Returns the display's icon
        virtual QImage getIcon() const = 0;

        // Initialisation method
        virtual void onInit(QMap <QString, QVariant> params) = 0;

        // Returns a newly created instance
        virtual IDisplay *getNewInstance() = 0;

        // Method called when the display's settings are launched by the user
        virtual QWidget *onSettings() = 0;

        // Returns the display's class name
        virtual QString getClassName() const = 0;

        //virtual bool smaller() = 0;
        //virtual bool bigger() = 0;
    };
}

#endif //FAIRWIND_IDISPLAY_HPP