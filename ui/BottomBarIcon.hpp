//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_BOTTOMBARICON_HPP
#define FAIRWIND_BOTTOMBARICON_HPP


#include <QString>
#include <QObject>

namespace Ui {
    class BottomBarIcon;
}

class BottomBar;

typedef  void (BottomBar::*BottomBarIconFn)(void);

class BottomBarIcon: public QObject {
    Q_OBJECT

public:
    BottomBarIcon();

    BottomBarIcon(QString name, QString icon);

    BottomBarIcon(const BottomBarIcon &bottomBarIcon) ;


    BottomBarIcon(QString name, QString icon, BottomBarIconFn func);

    QString getName();
    QString getIcon();
    BottomBarIconFn getFunc();

private:
    QString name;
    QString icon;
    BottomBarIconFn func = nullptr;
};


#endif //FAIRWIND_BOTTOMBARICON_HPP
