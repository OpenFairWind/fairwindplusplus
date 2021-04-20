//
// Created by Raffaele Montella on 27/03/21.
//

#include <QCryptographicHash>
#include <utility>
#include "include/FairWindSdk/App.hpp"
#include "include/FairWindSdk/FairWind.hpp"

fairwind::App::App() {

}

fairwind::App::App(const fairwind::App &app) {
    this->m_extension = app.m_extension;
    this->m_active = app.m_active;
    this->m_order = app.m_order;
    this->m_name = app.m_name;
    this->m_desc = app.m_desc;
    this->m_icon = app.m_icon;
    this->m_args = app.m_args;
    generateHash();
}



fairwind::App::App(fairwind::apps::IFairWindApp *fairWindApp, QMap<QString, QString> args, bool active, int order) {
    m_extension=fairWindApp->getId();
    m_name=fairWindApp->getName();
    m_desc=fairWindApp->getDesc();
    m_icon=fairWindApp->getIcon();
    m_order=order;
    m_active=active;
    m_args=std::move(args);
    if (m_args.find("Name")!=m_args.end()) {
        m_name=m_args["Name"];
    }
    if (m_args.find("Description")!=m_args.end()) {
        m_desc=m_args["Description"];
    }
    if (m_args.find("Icon")!=m_args.end()) {
        m_icon = QImage(m_args["Icon"]);
    }
    generateHash();
}

QString fairwind::App::getExtension() {
    return m_extension;
}

QString fairwind::App::getName() {
    return m_name;
}

QImage fairwind::App::getIcon() {
    return m_icon;
}

void fairwind::App::setOrder(int order) {
    m_order=order;
}

int fairwind::App::getOrder() {
    return m_order;
}

void fairwind::App::setActive(bool active) {
    m_active = active;
}

bool fairwind::App::getActive() {
    return m_active;
}

QString fairwind::App::getHash() {
    return m_hash;
}

void fairwind::App::generateHash() {
    QString text=m_extension;
    for(QString key:m_args.keys()) {
        text=text+" "+key+"="+"\""+m_args[key]+"\"";
    }

    m_hash = QString(QCryptographicHash::hash((text.toUtf8()),QCryptographicHash::Md5).toHex());

}

QMap<QString, QString> fairwind::App::getArgs() {
    return m_args;
}
