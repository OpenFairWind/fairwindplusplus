//
// Created by Raffaele Montella on 11/01/22.
//

#include "PageBase.hpp"

fairwind::PageBase::PageBase(QWidget *parent, apps::FairWindApp *fairWindApp):
        QWidget(parent) {
    m_fairWindApp=fairWindApp;
}

fairwind::apps::FairWindApp *fairwind::PageBase::getFairWindApp() {
    return m_fairWindApp;
}
