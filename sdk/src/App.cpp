//
// Created by Raffaele Montella on 27/03/21.
//

#include <QCryptographicHash>
#include <utility>
#include <FairWindSdk/FairWindApp.hpp>

#include "include/FairWindSdk/App.hpp"
#include "include/FairWindSdk/FairWind.hpp"

fairwind::App::App() {}

/*
 * Public Constructor
 */
fairwind::App::App(const fairwind::App &app) {
    // Retrieve the app's infos from the provided App instance
    this->m_extension = app.m_extension;
    this->m_active = app.m_active;
    this->m_order = app.m_order;
    this->m_name = app.m_name;
    this->m_desc = app.m_desc;
    this->m_icon = app.m_icon;
    this->m_args = app.m_args;
    generateHash();
}

/*
 * Public Constructor
 */
fairwind::App::App(fairwind::apps::FairWindApp *fairWindApp, bool active, int order) {
    // Get the app's infos and store them for future usage
    m_extension = fairWindApp->getId();
    m_route = fairWindApp->getRoute();
    m_args = fairWindApp->getArgs();
    m_name = fairWindApp->getName();
    m_desc = fairWindApp->getDesc();
    m_version = fairWindApp->getVersion();
    m_vendor = fairWindApp->getVendor();
    m_copyright = fairWindApp->getCopyright();
    m_license = fairWindApp->getLicense();
    m_icon = fairWindApp->getIcon();
    m_order = order;
    m_active = active;

    generateHash();
}

/*
 * getExtension
 * Returns the app's extension
 */
QString fairwind::App::getExtension() {
    return m_extension;
}

/*
 * getName
 * Returns the app's name
 */
QString fairwind::App::getName() {
    return m_name;
}

/*
 * getDesc
 * Returns the app's description
 */
QString fairwind::App::getDesc() {
    return m_desc;
}

/*
 * getIcon
 * Returns the app's icon
 */
QImage fairwind::App::getIcon() {
    return m_icon;
}

/*
 * setOrder
 * Sets the app's order
 */
void fairwind::App::setOrder(int order) {
    m_order = order;
}
/*
 * getOrder
 * Returns the app's order
 */
int fairwind::App::getOrder() {
    return m_order;
}

/*
 * setActive
 * Sets the app's active state
 */
void fairwind::App::setActive(bool active) {
    m_active = active;
}

/*
 * getActive
 * Returns the app's active state
 */
bool fairwind::App::getActive() {
    return m_active;
}

/*
 * getHash
 * Returns the app's generated hash
 */
QString fairwind::App::getHash() {
    return m_hash;
}

/*
 * generateHash
 * Generates a new hash value for the app
 */
void fairwind::App::generateHash() {
    QString text = m_extension+"/"+m_route;
    for (QString key: m_args.keys()) {
        text = text + " " + key + "=" + "\"" + m_args[key].toString() + "\"";
    }

    m_hash = QString(QCryptographicHash::hash((text.toUtf8()), QCryptographicHash::Md5).toHex());
}

QString fairwind::App::getRoute() {
    return m_route;
}

/*
 * getArgs
 * Returns the app's args
 */
QMap <QString, QVariant> fairwind::App::getArgs() {
    return m_args;
}

/*
 * getVersion
 * Returns the app's version
 */
QString fairwind::App::getVersion() {
    return m_version;
}

/*
 * getVendor
 * Returns the app's vendor
 */
QString fairwind::App::getVendor() {
    return m_vendor;
}

/*
 * getCopyright
 * Returns the app's copyright
 */
QString fairwind::App::getCopyright() {
    return m_copyright;
}

/*
 * getLicense
 * Returns the app's license
 */
QString fairwind::App::getLicense() {
    return m_license;
}


