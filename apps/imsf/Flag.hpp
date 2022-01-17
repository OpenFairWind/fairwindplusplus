//
// Created by Raffaele Montella on 10/01/22.
//

#ifndef FAIRWIND_FLAG_HPP
#define FAIRWIND_FLAG_HPP

#include <QWidget>
#include <QJsonValueRef>

namespace fairwind::apps::imsf {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Flag; }
    QT_END_NAMESPACE

    class Flag : public QWidget {
    Q_OBJECT

    public:
        explicit Flag(QWidget *parent, QJsonObject jsonObject);

        ~Flag() override;

    private:
        Ui::Flag *ui;
    };
} // fairwind::apps::imsf

#endif //FAIRWIND_FLAG_HPP
