//
// Created by Raffaele Montella on 10/01/22.
//

#ifndef FAIRWIND_UI_COLOPHONPAGE_HPP
#define FAIRWIND_UI_COLOPHONPAGE_HPP

#include <QWidget>
#include <FairWindSdk/PageBase.hpp>

namespace fairwind::ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Colophon; }
    QT_END_NAMESPACE

    class Colophon : public apps::PageBase {
    Q_OBJECT

    public:
        explicit Colophon(PageBase *parent = nullptr, apps::FairWindApp *appBase = nullptr);

        ~Colophon() override;

    public slots:
        void onAccepted();

    private:
        Ui::Colophon *ui;
    };
} // fairwind::ui

#endif //FAIRWIND_UI_COLOPHONPAGE_HPP
