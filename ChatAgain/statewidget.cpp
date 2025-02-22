#include "statewidget.h"
#include <QPainter>

StateWidget::StateWidget(QWidget *parent)
    :QWidget(parent),_is_selected(false)
{
    setCursor(Qt::PointingHandCursor); // 设置光标为小手
}

void StateWidget::setPixmap(const QString &normal, const QString &hover, const QString &press)
{
    _normal = QPixmap(normal).scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _hover = QPixmap(hover).scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _press = QPixmap(press).scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _current = _normal;
    update();
}

void StateWidget::mousePressEvent(QMouseEvent *event)
{
    _is_selected = true;
    _current = _press;
    update();
    emit clicked();
    QWidget::mousePressEvent(event);
}

void StateWidget::enterEvent(QEnterEvent *event)
{
    if(_is_selected) return;
    _current = _hover;
    update();
    QWidget::enterEvent(event);
}

void StateWidget::leaveEvent(QEvent *event)
{
    if(_is_selected) return;
    _current = _normal;
    update();
    QWidget::leaveEvent(event);
}

void StateWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,_current);
    QWidget::paintEvent(event);
}

void StateWidget::clearState()
{
    _current = _normal;
    _is_selected = false;
    update();
}

void StateWidget::setSelected()
{
    _current = _press;
    _is_selected = true;
    update();
}
