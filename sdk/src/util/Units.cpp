//
// Created by Raffaele Montella on 02/06/21.
//

#include "include/FairWindSdk/util/Units.hpp"

/*
 * Units - Public Constructor
 */
fairwind::Units::Units() {
    mConverters["K"]["F"] = [](double value) { return value * 1.8 - 459.67; };
    mConverters["K"]["C"] = [](double value) { return value - 273.15; };
    mConverters["rad"]["deg"] = [](double value) { return value * 57.2958; };
    mConverters["m/s"]["kn"] = [](double value) { return value * 1.94384; };
    mConverters["m"]["m"] = [](double value) { return value; };
    mConverters["v"]["v"] = [](double value) { return value; };
    mConverters["l"]["l"] = [](double value) { return value; };
    mConverters["A"]["A"] = [](double value) { return value; };

    mLabels["F"] = "°F";
    mLabels["C"] = "°C";
    mLabels["deg"] = "°";
    mLabels["kn"] = "kn";
    mLabels["m"] = "m";
    mLabels["A"] = "A";
    mLabels["v"] = "v";
    mLabels["l"] = "l";
}

/*
 * getInstance
 * Returns the existent instance, if any, otherwise creates a new one a returns it
 */
fairwind::Units *fairwind::Units::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new Units();
    }
    return m_instance;
}

/*
 * convert
 * Converts a value from a unit to another
 */
double fairwind::Units::convert(const QString &srcUnit, const QString &unit, double value) {
    if (mConverters.contains(srcUnit) && mConverters[srcUnit].contains(unit)) {
        return mConverters[srcUnit][unit](value);
    }
    return value;
}

/*
 * getLabel
 * Returns the unit's label
 */
QString fairwind::Units::getLabel(const QString &unit) {
    if (mLabels.contains(unit)) {
        return mLabels[unit];
    }
    return unit;
}