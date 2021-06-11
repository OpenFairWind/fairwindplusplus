//
// Created by Raffaele Montella on 10/06/21.
//

#ifndef FAIRWIND_LAYOUTBASE_HPP
#define FAIRWIND_LAYOUTBASE_HPP


#include <QString>
#include <QMap>
#include <QLayout>

#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IDisplay.hpp>


namespace fairwind::layouts {
    class FAIRWINDSDK_LIB_DECL LayoutBase {

    public:
        LayoutBase();
        ~LayoutBase();

        void setUI(QString key, QLayout *layout);
        void addDisplay(QString key, displays::IDisplay *display);


    private:
        QMap<QString, QLayout *> mLayouts;
    };
}


#endif //FAIRWIND_LAYOUTBASE_HPP
