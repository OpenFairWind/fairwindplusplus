//
// Created by Raffaele Montella on 08/01/22.
//

#ifndef FAIRWIND_COLOPHON_HPP
#define FAIRWIND_COLOPHON_HPP

#include <QDialog>

namespace fairwind::ui::colophon {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Colophon; }
    QT_END_NAMESPACE

    class Colophon : public QDialog {
    Q_OBJECT

    public:
        explicit Colophon(QWidget *parent = nullptr);

        ~Colophon() override;

    private:
        Ui::Colophon *ui;
    };
} // fairwind::ui::colophon

#endif //FAIRWIND_COLOPHON_HPP
