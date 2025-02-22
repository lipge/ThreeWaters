#include "bubbleframe.h"
#include <QHBoxLayout>
#include <QPainter>

const int triangle_width = 3;

BubbleFrame::BubbleFrame(MessageRole role, QWidget* parent)
    :QFrame(parent),_margin(3),_role(role)

{
    this->setFrameStyle(QFrame::NoFrame);
    hLayout = new QHBoxLayout;

    if(role == MessageRole::Other)
        hLayout->setContentsMargins(_margin + triangle_width,_margin,_margin,_margin);
    else
        hLayout->setContentsMargins(_margin ,_margin,_margin + triangle_width,_margin);

    this->setLayout(hLayout);
}

void BubbleFrame::setWidget(QWidget *w)
{
    if(hLayout->count() > 0)
        return ;
    else{
        hLayout->addWidget(w);
    }
}

void BubbleFrame::setMargin(int size)
{
    _margin = size;
    if(_role == MessageRole::Other)
        hLayout->setContentsMargins(_margin + triangle_width,_margin,_margin,_margin);
    else
        hLayout->setContentsMargins(_margin ,_margin,_margin + triangle_width,_margin);

}

void BubbleFrame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    if(_role == MessageRole::Other){
        painter.setBrush(Qt::white);
        QRect bk_rect = QRect(triangle_width, 0, this->width() - triangle_width,this->height());
        painter.drawRoundedRect(bk_rect,5,5);
        QPointF points[3] = {
            QPointF(bk_rect.x(), 12),
            QPointF(bk_rect.x(), 10+triangle_width +2),
            QPointF(bk_rect.x()-triangle_width, 10+triangle_width-triangle_width/2),
        };
        painter.drawPolygon(points, 3);
    }
    else{
        painter.setBrush(QColor(158,234,106));// 绿色
        QRect bk_rect = QRect(0,0,this->width() - triangle_width,this->height());
        painter.drawRoundedRect(bk_rect,5,5);

        //画三角
        QPointF points[3] = {
            QPointF(bk_rect.x()+bk_rect.width(), 12),
            QPointF(bk_rect.x()+bk_rect.width(), 12+triangle_width +2),
            QPointF(bk_rect.x()+bk_rect.width()+triangle_width, 10+triangle_width-triangle_width/2),
        };
        painter.drawPolygon(points, 3);
    }
    return QFrame::paintEvent(e);
}
