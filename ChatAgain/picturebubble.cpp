#include "picturebubble.h"
#include <QLabel>
const int WIDTH = 160;
const int HEIGHT = 160;

PictureBubble::PictureBubble(const QPixmap &picture, MessageRole role, QWidget *parent)
    :BubbleFrame(role,parent)
{
    setMargin(0);
    QLabel *lb = new QLabel();
    lb->setScaledContents(true);
    QPixmap pix = picture.scaled(QSize(WIDTH, HEIGHT), Qt::KeepAspectRatio);
    lb->setPixmap(pix);
    this->setWidget(lb);
    int left_margin = this->layout()->contentsMargins().left();
    int right_margin = this->layout()->contentsMargins().right();
    int v_margin = this->layout()->contentsMargins().bottom();
    setFixedSize(pix.width()+left_margin + right_margin, pix.height() + v_margin *2);
}
