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
    /*
     * Units
     * This class provides the most basic units and a quick way to convert and switch between them
     */
    class FAIRWINDSDK_LIB_DECL Units : public QObject {
        Q_OBJECT
    public:
        static Units *getInstance();
        double convert(const QString& srcUnit, const QString& unit, double value);
        QString getLabel(const QString &unit);

    private:
        Units();

        inline static Units *m_instance = nullptr;

        QMap <QString, QMap<QString, std::function<double(double)>>> mConverters;
        QMap <QString, QString> mLabels;
    };
}

#endif //FAIRWIND_UNITS_HPP