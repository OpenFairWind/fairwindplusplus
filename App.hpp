//
// Created by Raffaele Montella on 27/03/21.
//

#ifndef FAIRWINDS_APP_HPP
#define FAIRWINDS_APP_HPP


#include <string>
#include <QWidget>

class App  {
public:
    App() {
        name="";
        icon="";
        url="";
    }

    App(std::string name, std::string icon, std::string url) {
        this->name=name;
        this->icon=icon;
        this->url=url;
    }
    App(const App &app)  {
        this->name=app.name;
        this->icon=app.icon;
        this->url=app.url;
    }

    std::string name;
    std::string icon;
    std::string url;
};


#endif //FAIRWINDS_APP_HPP
