#include "clickedoncelabel.h"

ClickedOnceLabel::ClickedOnceLabel(QWidget *parent)
    :QLabel(parent)
{
    setCursor(Qt::PointingHandCursor);// 设置小手光标
}

void ClickedOnceLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug()<<this->text();
    emit clicked(this->text());
    QLabel::mouseReleaseEvent(ev);
}
