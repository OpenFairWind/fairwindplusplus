//
// Created by Ciro Giuseppe De Vita on 08/02/2022.
//

#ifndef __APPNAME___RESULTITEM_HPP
#define __APPNAME___RESULTITEM_HPP

#include <QWidget>
#include <QJsonObject>

namespace __namespace__ {
    QT_BEGIN_NAMESPACE
    namespace Ui { class ResultItem; }
    QT_END_NAMESPACE

    class ResultItem : public QWidget {
    Q_OBJECT

    public:
        explicit ResultItem(QWidget *parent = nullptr, QJsonObject feature = QJsonObject());

        ~ResultItem() override;

    private:
        Ui::ResultItem *ui;
    };
} // __namespace__

#endif //__APPNAME___RESULTITEM_HPP