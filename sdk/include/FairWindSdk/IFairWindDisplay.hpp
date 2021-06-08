//
// Created by Raffaele Montella on 02/06/21.
//

#ifndef FAIRWIND_IFAIRWINDDISPLAY_HPP
#define FAIRWIND_IFAIRWINDDISPLAY_HPP

namespace fairwind::displays {

    class IFairWindDisplay {
    public:
        virtual ~IFairWindDisplay() = default;

        virtual QImage getIcon() const = 0;
        virtual void onInit(QMap<QString, QVariant> params) = 0;
        virtual IFairWindDisplay *getNewInstance()  = 0;
        virtual QWidget *onSettings() = 0;
        virtual QString getClassName() const = 0;

        virtual bool smaller() = 0;
        virtual bool bigger() = 0;
    };

}

#endif //FAIRWIND_IFAIRWINDDISPLAY_HPP
