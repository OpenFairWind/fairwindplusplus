//
// Created by Raffaele Montella on 28/03/21.
//

#ifndef FAIRWIND_WEBPOPUPWINDOW_HPP
#define FAIRWIND_WEBPOPUPWINDOW_HPP


#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QWebEngineProfile;
class QWebEngineView;
QT_END_NAMESPACE

class WebView;

class WebPopupWindow : public QWidget
{
Q_OBJECT

public:
    WebPopupWindow(QWebEngineProfile *profile);
    WebView *view() const;

private slots:
    void handleGeometryChangeRequested(const QRect &newGeometry);

private:
    QLineEdit *m_urlLineEdit;
    QAction *m_favAction;
    WebView *m_view;
};


#endif //FAIRWIND_WEBPOPUPWINDOW_HPP
