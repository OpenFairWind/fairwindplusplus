//
// Created by Raffaele Montella on 14/01/22.
//

#ifndef PORTOLANO_MAINPAGE_HPP
#define PORTOLANO_MAINPAGE_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include <QSqlQuery>

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

        ~MainPage() ;

    public slots:
        void onEditTextChanged(const QString &text);

        void onBoolChanged(int state);

        void onNumberTextChanged(const QString &text);

        void onNumberSelectChanged(double value);

        void updateNavigationPosition(const QJsonObject update);

    private:
        Ui::MainPage *ui;

        QJsonObject mConfig;

        QJsonObject mPosition;

        double radius;

        QJsonObject calculateDerivedPosition(QJsonObject point, double range, double bearing);

        double degreeToRadians(double degree);

        double radiansToDegree(double radians);

        void insertIntoList(QSqlQuery query);

        bool pointIsInCircle(QJsonObject p1, QJsonObject p2);

        double getDistanceBetweenTwoPoints(QJsonObject p1, QJsonObject p2);
    };
} // fairwind::appls::portolano

#endif //PORTOLANO_MAINPAGE_HPP
