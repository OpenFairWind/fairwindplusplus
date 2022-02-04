//
// Created by Raffaele Montella on 13/01/22.
//

#ifndef FAIRWIND_MAINPAGE_HPP
#define FAIRWIND_MAINPAGE_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/PageBase.hpp>

#include "WebView.hpp"

namespace it::gov::guardiacostiera::gc1530 {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, fairwind::apps::FairWindApp *fairWindApp = nullptr);

        ~MainPage();

    public slots:
        void toolButton_home_clicked();

    private:
        Ui::MainPage *ui;
        WebView *m_webView = nullptr;
    };
} // it::gov::guardiacostiera::gc1530

#endif //FAIRWIND_MAINPAGE_HPP
