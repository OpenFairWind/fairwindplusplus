//
// Created by Raffaele Montella on 28/03/21.
//

#ifndef FAIRWINDS_WEBVIEW_HPP
#define FAIRWINDS_WEBVIEW_HPP

#include <QIcon>
#include <QWebEngineView>

//class WebPage;

namespace it::gov::guardiacostiera::gc1530 {
    class WebView : public QWebEngineView {
    Q_OBJECT

    public:
        WebView(QWidget *parent = nullptr);


        int loadProgress() const;

        bool isWebActionEnabled(QWebEnginePage::WebAction webAction) const;

        QIcon favIcon() const;

    public slots:

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

        QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

    signals:

        void webActionEnabledChanged(QWebEnginePage::WebAction webAction, bool enabled);

        void favIconChanged(const QIcon &icon);

        void devToolsRequested(QWebEnginePage *source);


    private:
        void createWebActionTrigger(QWebEnginePage *page, QWebEnginePage::WebAction);

    private:
        int m_loadProgress;
    };
}


#endif //FAIRWINDS_WEBVIEW_HPP
