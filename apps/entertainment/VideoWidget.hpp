//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_VIDEOWIDGET_HPP
#define FAIRWIND_VIDEOWIDGET_HPP

#include <QVideoWidget>

namespace fairwind::apps::entertainment {
    class VideoWidget : public QVideoWidget
    {
        Q_OBJECT

    public:
        explicit VideoWidget(QWidget *parent = nullptr);

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void mouseDoubleClickEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
    };
}


#endif //FAIRWIND_VIDEOWIDGET_HPP
