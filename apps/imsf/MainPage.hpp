//
// Created by Raffaele Montella on 10/01/22.
//

#ifndef FAIRWIND_MAINPAGE_HPP
#define FAIRWIND_MAINPAGE_HPP

#include <QWidget>
#include <FairWindSdk/PageBase.hpp>
#include "Flag.hpp"

namespace fairwind::apps::imsf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, fairwind::apps::IFairWindApp *fairWindApp = nullptr);

        ~MainPage();



    private:
        Ui::MainPage *ui;

        QJsonObject m_jsonObject;

    };
} // fairwind::apps::imsf

#endif //FAIRWIND_MAINPAGE_HPP
