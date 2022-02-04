//
// Created by Raffaele Montella on 11/01/22.
//

#include "PageBase.hpp"

namespace fairwind::apps {
    PageBase::PageBase(QWidget *parent, apps::FairWindApp *fairWindApp) :
            QWidget(parent) {
        m_fairWindApp = fairWindApp;
    }

    FairWindApp *PageBase::getFairWindApp() {
        return m_fairWindApp;
    }

    void PageBase::onCreate() {

    }

    void PageBase::onStart() {

    }

    void PageBase::onResume() {

    }

    void PageBase::onPause() {

    }

    void PageBase::onStop() {

    }

    void PageBase::onDestroy() {

    }

    void PageBase::onConfigChanged() {

    }
}