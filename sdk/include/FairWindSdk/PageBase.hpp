//
// Created by Raffaele Montella on 11/01/22.
//

#ifndef FAIRWIND_PAGEBASE_HPP
#define FAIRWIND_PAGEBASE_HPP

#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindApp.hpp>


namespace fairwind {
    class FAIRWINDSDK_LIB_DECL PageBase: public QWidget {
    Q_OBJECT

    public:
            PageBase(QWidget *parent = nullptr, apps::FairWindApp *fairWindApp = nullptr);
            ~PageBase() = default;

            apps::FairWindApp *getFairWindApp();

    private:
            apps::FairWindApp *m_fairWindApp;
    };
};


#endif //FAIRWIND_PAGEBASE_HPP
