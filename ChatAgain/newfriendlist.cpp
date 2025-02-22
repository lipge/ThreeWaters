#include "newfriendlist.h"
#include <QScrollBar>


NewFriendList::NewFriendList(QWidget* parent)
    :QListWidget(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

 //   addItems();// 添加联系人


}
void NewFriendList::wheelEvent(QWheelEvent *e)
{

    int maxVal = this->verticalScrollBar()->maximum();
    int currentVal = this->verticalScrollBar()->value();
    if(currentVal >= maxVal){
        emit sig_loading_applications();
    }
    QListWidget::wheelEvent(e);
}

void NewFriendList::leaveEvent(QEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListView::leaveEvent(event);
}

void NewFriendList::enterEvent(QEnterEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QListView::enterEvent(event);
}




