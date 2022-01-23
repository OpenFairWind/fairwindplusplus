//
// Created by Raffaele Montella on 23/01/22.
//

#ifndef FAIRWIND_EXTENSIONS_HPP
#define FAIRWIND_EXTENSIONS_HPP

#include <QWidget>
#include <FairWindSdk/ISettingsTab.hpp>
#include "../browser/Browser.hpp"

namespace fairwind::apps::settings::extensions {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Extensions; }
    QT_END_NAMESPACE

    class Extensions : public QWidget, public ui::settings::ISettingsTab {
    Q_OBJECT

    public:
        explicit Extensions(QWidget *parent = nullptr);

        ~Extensions() override;

        QString getClassName() const override;

        QImage getIcon() const override;

        QString getName() const override;

        ISettingsTab *getNewInstance() override;

    protected :
        void showEvent(QShowEvent *event) override;

    private
        slots:
        void onCurrentRowChanged( int currentRow );

    private:
        Ui::Extensions *ui;

        browser::Browser *mBrowser;
        QString mExtensionId;
    };
} // fairwind::apps::settings::extensions

#endif //FAIRWIND_EXTENSIONS_HPP
