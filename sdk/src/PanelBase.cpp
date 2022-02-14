//
// Created by Raffaele Montella on 10/02/22.
//

#include <QDialog>
#include "PanelBase.hpp"

namespace fairwind::apps {
    PanelBase::PanelBase(PageBase *parent):
            PageBase(parent) {

        mResult = QDialog::Rejected;
    }

    QVariant PanelBase::results() {
        return QVariant();
    }

    void PanelBase::setResults(QVariant results) {

    }

    int PanelBase::result() const {
        return mResult;
    }

    void PanelBase::setResult(int result) {
        mResult = result;
    }

    void PanelBase::onAdded() {
        PageBase::onAdded();
    }

    void PanelBase::onAccepted() {
        getFairWindApp()->remove((PageBase *)this);
    }
}