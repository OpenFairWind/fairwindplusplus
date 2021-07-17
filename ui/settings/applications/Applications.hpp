//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_APPLICATIONS_HPP
#define FAIRWIND_APPLICATIONS_HPP

#include <QWidget>
#include <FairWindSdk/ISettings.hpp>

namespace Ui {
    class Applications;
}

namespace fairwind::ui::settings::applications {

    class Applications : public QWidget, public ISettings {
        Q_OBJECT

    public:
        explicit Applications(QWidget *parent = 0);

        ~Applications();

        QString getClassName() const override;
        QImage getIcon() const override;
        QString getName() const override;
        ISettings *getNewInstance() override;

    protected :
        void showEvent(QShowEvent *event) override;

    private:
        Ui::Applications *ui;
    };
}


#endif //FAIRWIND_APPLICATIONS_HPP
