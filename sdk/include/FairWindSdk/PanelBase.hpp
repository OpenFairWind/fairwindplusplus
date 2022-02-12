//
// Created by Raffaele Montella on 10/02/22.
//

#ifndef FAIRWIND_PANELBASE_HPP
#define FAIRWIND_PANELBASE_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/PageBase.hpp>

namespace fairwind::apps {

    class FAIRWINDSDK_LIB_DECL PanelBase: public PageBase {
        Q_OBJECT


    public:
        PanelBase(PageBase *parent = nullptr);

        virtual void setResults(QVariant results);
        virtual QVariant results();

        int result() const;
        void setResult(int result);

        void onAdded() override;

        ~PanelBase() = default;

    public slots:
        void onAccepted();

        signals:
        void accepted();
        void finished(int result);
        void rejected();

    private:
        int mResult;
    };
};

#endif //FAIRWIND_PANELBASE_HPP
