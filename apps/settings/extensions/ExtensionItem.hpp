//
// Created by Raffaele Montella on 23/01/22.
//

#ifndef FAIRWIND_EXTENSIONITEM_HPP
#define FAIRWIND_EXTENSIONITEM_HPP

#include <QWidget>
#include <QListWidgetItem>
#include <FairWindSdk/IFairWindApp.hpp>

namespace fairwind::apps::settings::extensions {
    QT_BEGIN_NAMESPACE
    namespace Ui { class ExtensionItem; }
    QT_END_NAMESPACE

    class ExtensionItem : public QWidget {
    Q_OBJECT

    public:
        explicit ExtensionItem(QWidget *parent = nullptr, IFairWindApp *fairWindApp = nullptr);

        ~ExtensionItem() override;

        IFairWindApp *getFairWindApp();

    private:
        Ui::ExtensionItem *ui;
        IFairWindApp *mFairWindApp;
    };
} // fairwind::apps::settings::extensions

#endif //FAIRWIND_EXTENSIONITEM_HPP
