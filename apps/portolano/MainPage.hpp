//
// Created by Raffaele Montella on 14/01/22.
//

#ifndef PORTOLANO_MAINPAGE_HPP
#define PORTOLANO_MAINPAGE_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include <QSqlQuery>
#include <QGeoCoordinate>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::portolano {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, FairWindApp *fairWindApp = nullptr);

        ~MainPage();

        void onResume();

    public slots:
        void onEditTextChanged(const QString &text);

        void onBoolChanged(int state);

        void onNumberTextChanged(const QString &text);

        void onNumberSelectChanged(double value);

        void updateNavigationPosition(const QJsonObject update);

    private:
        Ui::MainPage *ui;

        QGeoCoordinate mPosition;

        QGeoCoordinate oldPosition;

        double radius;

        const double mile = 1852;

        QGeoCoordinate calculateDerivedPosition(QGeoCoordinate point, double range, double bearing);

        double degreeToRadians(double degree);

        double radiansToDegree(double radians);

        void insertIntoList(QSqlQuery query);

        bool pointIsInCircle(QGeoCoordinate p1, QGeoCoordinate p2);

        double getDistanceBetweenTwoPoints(QGeoCoordinate p1, QGeoCoordinate p2);
    };
} // fairwind::appls::portolano

#endif //PORTOLANO_MAINPAGE_HPP
