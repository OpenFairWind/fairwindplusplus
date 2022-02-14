//
// Created by Raffaele Montella on 11/01/22.
//

#include "PageBase.hpp"

namespace fairwind::apps {
    PageBase::PageBase(QWidget *parent) :
            QWidget(parent) {
        m_fairWindApp = nullptr;
    }

    FairWindApp *PageBase::getFairWindApp() {
        if (m_fairWindApp == nullptr) {
            qDebug() << "Page not already added to an application!";
        }
        return m_fairWindApp;
    }

    void PageBase::setFairWindApp(FairWindApp *fairWindApp) {
        this->m_fairWindApp = fairWindApp;
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

    void PageBase::onShown() {

    }

    void PageBase::onShowing() {

    }

    void PageBase::onAdded() {

    }



    void PageBase::onAdding() {

    }

    void PageBase::onRemoving() {

    }

    void PageBase::onRemoved() {

    }
}