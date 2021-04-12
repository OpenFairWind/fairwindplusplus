//
// Created by Raffaele Montella on 12/04/21.
//

#include "BottomBarIcon.hpp"

#include <utility>

BottomBarIcon::BottomBarIcon() {
    name = "";
    icon = "";
    func = nullptr;
}

BottomBarIcon::BottomBarIcon(QString name, QString icon) {
    this->name = std::move(name);
    this->icon = std::move(icon);
    this->func = nullptr;
}

BottomBarIcon::BottomBarIcon(const BottomBarIcon &bottomBarIcon) {
    this->name = bottomBarIcon.name;
    this->icon = bottomBarIcon.icon;
    this->func = bottomBarIcon.func;
}

BottomBarIcon::BottomBarIcon(QString name, QString icon, BottomBarIconFn func) {
    this->name = std::move(name);
    this->icon = std::move(icon);
    this->func = func;
}

QString BottomBarIcon::getName() {
    return name;
}

QString BottomBarIcon::getIcon() {
    return icon;
}

BottomBarIconFn BottomBarIcon::getFunc() {
    return func;
}
