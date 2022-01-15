//
// Created by Raffaele Montella on 10/01/22.
//

#ifndef FAIRWIND_COLOPHONPAGE_HPP
#define FAIRWIND_COLOPHONPAGE_HPP

#include <QWidget>
#include <PageBase.hpp>

namespace fairwind::ui {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Colophon; }
    QT_END_NAMESPACE

    class Colophon : public PageBase {
    Q_OBJECT

    public:
        explicit Colophon(QWidget *parent = nullptr, apps::FairWindApp *appBase = nullptr);

        ~Colophon() override;

    public slots:
        void onAccepted();

    private:
        Ui::Colophon *ui;
    };
} // fairwind::apps::imsf

#endif //FAIRWIND_COLOPHONPAGE_HPP
