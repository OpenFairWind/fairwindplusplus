//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_GENERIC_HPP
#define FAIRWIND_GENERIC_HPP

#include <QWidget>
#include <FairWindSdk/ISettings.hpp>

namespace Ui {
    class Generic;
}

namespace fairwind::ui::settings::generic {
    class Generic : public QWidget, public ISettings {
        Q_OBJECT

    public:
        explicit Generic(QWidget *parent = 0);

        ~Generic();

        QString getClassName() const override;

        QImage getIcon() const override;

        QString getName() const override;

        ISettings *getNewInstance() override;

    protected :
        void showEvent(QShowEvent *event) override;

    private:
        Ui::Generic *ui;
    };
}

#endif //FAIRWIND_GENERIC_HPP