//
// Created by Raffaele Montella on 14/01/22.
//

#ifndef FAIRWIND_MAINPAGE_HPP
#define FAIRWIND_MAINPAGE_HPP

#include <QWidget>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/PageBase.hpp>

#include "WebView.hpp"

namespace fairwind::apps::web {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(PageBase *parent = nullptr);

        void onAdded() override;

        ~MainPage();

    public slots:
        void toolButton_home_clicked();

    private:
        Ui::MainPage *ui;
        WebView *m_webView = nullptr;
        QString m_url;
    };
} // fairwind::apps::web

#endif //FAIRWIND_MAINPAGE_HPP
