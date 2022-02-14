//
// Created by Raffaele Montella on 13/01/22.
//

#ifndef FAIRWIND_UI_WARNING_HPP
#define FAIRWIND_UI_WARNING_HPP

#include <QWidget>
#include <FairWindSdk/PanelBase.hpp>

namespace fairwind::ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Warning; }
    QT_END_NAMESPACE

    class Warning : public apps::PanelBase {
    Q_OBJECT

    public:
        explicit Warning(PageBase *parent = nullptr, const QString &message = "Warning", const QString &details = "");

        ~Warning() override;

    private:
        Ui::Warning *ui;
    };
} // fairwind::ui

#endif //FAIRWIND_UI_WARNING_HPP
