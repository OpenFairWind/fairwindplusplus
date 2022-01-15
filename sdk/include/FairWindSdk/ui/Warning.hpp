//
// Created by Raffaele Montella on 13/01/22.
//

#ifndef FAIRWIND_WARNING_HPP
#define FAIRWIND_WARNING_HPP

#include <QWidget>
#include <PageBase.hpp>

namespace fairwind::ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Warning; }
    QT_END_NAMESPACE

    class Warning : public PageBase {
    Q_OBJECT

    public:
        explicit Warning(QWidget *parent = nullptr, apps::FairWindApp *appBase = nullptr, QString message = "Warning", QString details = "");

        ~Warning() override;

    public slots:
        void onAccepted();

    private:
        Ui::Warning *ui;
    };
} // fairwind::ui

#endif //FAIRWIND_WARNING_HPP
