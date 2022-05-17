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

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(PageBase *parent = nullptr);

        ~MainPage();

        void onAdded() override;
        void onResume() override;

    public slots:
        void onEditTextChanged(const QString &text);

        void onBoolChanged(int state);

        void onNumberTextChanged(const QString &text);

        void onNumberSelectChanged(double value);

        void updateNavigationPosition(const QJsonObject& update);

    private:
        Ui::MainPage *ui;

        QGeoCoordinate mPreviousNavigationPosition;

        //double mRangeInMeters;

        const double mNm2m = 1852;

        void insertIntoList(QSqlQuery query);

        void spatialQuery(double range);
    };
} // fairwind::appls::portolano

#endif //PORTOLANO_MAINPAGE_HPP
