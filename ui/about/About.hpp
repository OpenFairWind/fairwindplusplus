//
// Created by Raffaele Montella on 08/01/22.
//

#ifndef FAIRWIND_ABOUT_HPP
#define FAIRWIND_ABOUT_HPP

#include <QWidget>

namespace fairwind::ui::about {
    QT_BEGIN_NAMESPACE
    namespace Ui { class About; }
    QT_END_NAMESPACE

    class About : public QWidget {
    Q_OBJECT

    public:
        explicit About(QWidget *parent = nullptr, QWidget *currenWidget = nullptr);

        ~About() override;

        QWidget *getCurrentWidget();

    public slots:
        void onAccepted();

    signals:
        void accepted(About *);

    private:
        Ui::About *ui;
        QWidget *m_currentWidget;
    };
} // fairwind::ui::about

#endif //FAIRWIND_ABOUT_HPP
