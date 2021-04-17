//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_BOTTOMBAR_HPP
#define FAIRWIND_BOTTOMBAR_HPP

#include <QWidget>

namespace Ui {
    class BottomBar;
}

class BottomBar : public QWidget {
    Q_OBJECT
public:
    explicit BottomBar(QWidget *parent = 0);
    ~BottomBar();

public slots:
    void settings_clicked();
    void apps_clicked();

signals:
    void setApps();
    void setSettings();


private:
    Ui::BottomBar *ui;


};

#endif //FAIRWIND_BOTTOMBAR_HPP
