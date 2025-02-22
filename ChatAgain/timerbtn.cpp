#include "timerbtn.h"
#include <QMouseEvent>

TimerBtn::TimerBtn(QWidget *parent)
    :QPushButton(parent),_cnt(10)
{
    _timer = new QTimer(this);

    // 定时器启动时触发此回调
    connect(_timer,&QTimer::timeout,[this](){
        _cnt--;
        if(_cnt<=0){
            _timer->stop();
            _cnt=10;
            this->setText("获取");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(_cnt));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        this->setEnabled(false);
        this->setText(QString::number(_cnt));
        _timer->start(1000);
    }
    QPushButton::mouseReleaseEvent(e);
    emit clicked(true);
}
