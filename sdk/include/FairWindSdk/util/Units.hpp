//
// Created by Raffaele Montella on 02/06/21.
//

#ifndef FAIRWIND_UNITS_HPP
#define FAIRWIND_UNITS_HPP

#include <QString>
#include <QMap>
#include <QObject>

#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL Units : public QObject {
        Q_OBJECT

    public:
        static Units *getInstance();
        double convert(const QString& srcUnit, const QString& unit, double value);

    private:
        double kelvin2celsius(double kelvin) { return kelvin - 273.1; }

        double kelvin2fahrenheit(double fahrenheit) { return fahrenheit * 1.8 - 459.67; }

        Units();

        inline static Units *m_instance = nullptr;

        QMap <QString, QMap<QString, std::function<double(double)>>> mConverters;

    };
}


#endif //FAIRWIND_UNITS_HPP
