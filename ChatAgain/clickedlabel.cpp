#include "ClickedLabel.h"
#include <QLabel>
#include <QMouseEvent>
ClickedLabel::ClickedLabel(QWidget *parent)
    :QLabel(parent)
    ,_need_selected(true)
{
    this->setCursor(Qt::PointingHandCursor);

}

ClickedLabel::~ClickedLabel()
{

}

void ClickedLabel::SetState()
{
    this->setStyleSheet("color: blue");
    _state=ClickLbState::PlainText;
}

void ClickedLabel::SetState(QString normal, QString selected, QString normal_hover, QString select_hover)
{
    // 加载图片
    _normal_pix.load(normal);
    _normal_hover_pix.load(normal_hover);
    _selected_pix.load(selected);
    _selected_hover_pix.load(select_hover);
    // 设置合适大小
    _normal_pix = _normal_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _selected_pix = _selected_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _normal_hover_pix = _normal_hover_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _selected_hover_pix = _selected_hover_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    // 设置初始状态
    _state = ClickLbState::Normal;
    this->setPixmap(_normal_pix);
    repolish(this);
}
void ClickedLabel::SetState(QString normal,QString hover, QString press)
{
    _need_selected = false;
    // 加载图片
    _normal_pix.load(normal);
    _normal_hover_pix.load(hover);
    _selected_pix.load(press);
    _selected_hover_pix.load(press);
    // 设置合适大小
    _normal_pix = _normal_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _selected_pix = _selected_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _normal_hover_pix = _normal_hover_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    _selected_hover_pix = _selected_hover_pix.scaled(this->size()/1.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    // 设置初始状态
    _state = ClickLbState::Normal;
    this->setPixmap(_normal_pix);
    repolish(this);
}
void ClickedLabel::enterEvent(QEnterEvent *event)
{

    if(_state == ClickLbState::Normal){
        this->setPixmap(_normal_hover_pix);

    }
    else if(_state == ClickLbState::Selected){
        this->setPixmap(_selected_hover_pix);

    }
    QWidget::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event)
{

    if(_state == ClickLbState::Normal){
        this->setPixmap(_normal_pix);
    }
    else if(_state == ClickLbState::Selected){
        this->setPixmap(_selected_pix);
    }
    QWidget::leaveEvent(event);

}

void ClickedLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton){
        return;
    }
    if(_state == ClickLbState::Normal){
        this->setPixmap(_selected_hover_pix);
        if(_need_selected)  // 需要转换状态的话
            _state=ClickLbState::Selected;
    }
    else if(_state == ClickLbState::Selected){
        this->setPixmap(_normal_hover_pix);
        if(_need_selected)  // 需要转换状态的话
            _state=ClickLbState::Normal;
    }
    emit clicked();
    QLabel::mousePressEvent(ev);
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton){
        return;
    }
    if(_state == ClickLbState::Normal){
        this->setPixmap(_normal_hover_pix);
    }
    else if(_state == ClickLbState::Selected){
    //    this->setPixmap(_normal_hover_pix);
    }
    emit clicked();
    QLabel::mousePressEvent(ev);
}

ClickLbState ClickedLabel::GetState()
{
    return _state;
}
