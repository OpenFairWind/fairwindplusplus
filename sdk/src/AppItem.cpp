//
// Created by Raffaele Montella on 27/03/21.
//

#include <QCryptographicHash>
#include <utility>
#include <FairWindSdk/FairWindApp.hpp>

#include "include/FairWindSdk/AppItem.hpp"
#include "include/FairWindSdk/FairWind.hpp"

namespace fairwind {
    AppItem::AppItem() {}

/*
 * Public Constructor
 */
    AppItem::AppItem(const fairwind::AppItem &app) {
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
    AppItem::AppItem(fairwind::apps::FairWindApp *fairWindApp, bool active, int order) {
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
    QString AppItem::getExtension() {
        return m_extension;
    }

    /*
     * getName
     * Returns the app's name
     */
    QString AppItem::getName() {
        return m_name;
    }

    /*
     * getDesc
     * Returns the app's description
     */
    QString AppItem::getDesc() {
        return m_desc;
    }

    /*
     * getIcon
     * Returns the app's icon
     */
    QImage AppItem::getIcon() {
        return m_icon;
    }

    /*
     * setOrder
     * Sets the app's order
     */
    void AppItem::setOrder(int order) {
        m_order = order;
    }

    /*
     * getOrder
     * Returns the app's order
     */
    int AppItem::getOrder() {
        return m_order;
    }

    /*
     * setActive
     * Sets the app's active state
     */
    void AppItem::setActive(bool active) {
        m_active = active;
    }

    /*
     * getActive
     * Returns the app's active state
     */
    bool AppItem::getActive() {
        return m_active;
    }

    /*
     * getHash
     * Returns the app's generated hash
     */
    QString AppItem::getHash() {
        return m_hash;
    }

    /*
     * generateHash
     * Generates a new hash value for the app
     */
    void AppItem::generateHash() {
        QString text = m_extension + "/" + m_route;
        for (const QString& key: m_args.keys()) {
            text = text + " " + key + "=" + "\"" + m_args[key].toString() + "\"";
        }

        m_hash = QString(QCryptographicHash::hash((text.toUtf8()), QCryptographicHash::Md5).toHex());
    }

    QString AppItem::getRoute() {
        return m_route;
    }

    /*
     * getArgs
     * Returns the app's args
     */
    QMap<QString, QVariant> AppItem::getArgs() {
        return m_args;
    }

    /*
     * getVersion
     * Returns the app's version
     */
    QString AppItem::getVersion() {
        return m_version;
    }

    /*
     * getVendor
     * Returns the app's vendor
     */
    QString AppItem::getVendor() {
        return m_vendor;
    }

    /*
     * getCopyright
     * Returns the app's copyright
     */
    QString AppItem::getCopyright() {
        return m_copyright;
    }

    /*
     * getLicense
     * Returns the app's license
     */
    QString AppItem::getLicense() {
        return m_license;
    }

    bool AppItem::operator<(const AppItem &o) const {
        return std::tie(m_order) < std::tie(o.m_order);
    }

}
