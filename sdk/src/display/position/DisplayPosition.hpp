//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYPOSITION_HPP
#define FAIRWIND_DISPLAYPOSITION_HPP


#include <include/FairWindSdk/display/DisplayDoubleText.hpp>

class DisplayPosition: public DisplayDoubleText {
    Q_OBJECT

public:
    explicit DisplayPosition(QWidget *parent=0);
    ~DisplayPosition();

public slots:
    void updatePosition();

private:
};


#endif //FAIRWIND_DISPLAYPOSITION_HPP
