//
// Created by Raffaele Montella on 02/06/21.
//

#ifndef FAIRWIND_IDISPLAY_HPP
#define FAIRWIND_IDISPLAY_HPP

namespace fairwind::displays {

    class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual QImage getIcon() const = 0;
        virtual void onInit(QMap<QString, QVariant> params) = 0;
        virtual IDisplay *getNewInstance()  = 0;
        virtual QWidget *onSettings() = 0;
        virtual QString getClassName() const = 0;

        //virtual bool smaller() = 0;
        //virtual bool bigger() = 0;
    };

}

#endif //FAIRWIND_IDISPLAY_HPP
