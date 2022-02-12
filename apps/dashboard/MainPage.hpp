//
// Created by Raffaele Montella on 11/01/22.
//

#ifndef FAIRWIND_MAINPAGE_HPP
#define FAIRWIND_MAINPAGE_HPP

#include <QWidget>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/PageBase.hpp>

namespace fairwind::apps::dashboard {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(PageBase *parent = nullptr);

        ~MainPage() ;

        void onAdded() override;

    private:
        Ui::MainPage *ui;

    };
} // fairwind::apps::Dashboard

#endif //FAIRWIND_MAINPAGE_HPP
