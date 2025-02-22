#include "chatview.h"
#include "ui_chatview.h"
#include <QVBoxLayout>
#include <QScrollBar>

ChatView::ChatView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatView)
{
//
    ui->setupUi(this);
    ui->chat_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //把垂直ScrollBar放到上边 而不是原来的并排
    QHBoxLayout *pHLayout_2 = new QHBoxLayout();
    // 获取原来的滚动条
    QScrollBar *pVScrollBar = ui->chat_area->verticalScrollBar();
    pHLayout_2->addWidget(pVScrollBar, 0, Qt::AlignRight);
    pHLayout_2->setContentsMargins(0,0,0,0);
    ui->chat_area->setLayout(pHLayout_2);
    pVScrollBar->setHidden(true);
    ui->chat_area->setWidgetResizable(true);
}

ChatView::~ChatView()
{
    delete ui;
}

void ChatView::appendChatItem(QWidget *item)
{
    auto vl = qobject_cast<QVBoxLayout*>(ui->chat_wid->layout());// 获取布局
    vl->insertWidget(vl->count()-1,item);
}

void ChatView::rmAllItem()
{
    auto vl = qobject_cast<QVBoxLayout*>(ui->chat_wid->layout());// 获取布局
    int cnt = vl->count();
    for(int i = 0; i<cnt-1; i++){
        auto item = vl->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        // 删除布局项
        delete item;
    }
}

void ChatView::enterEvent(QEnterEvent *event)
{
    ui->chat_area->verticalScrollBar()->setHidden(ui->chat_area->verticalScrollBar()->maximum() == 0);
    QWidget::enterEvent(event);
}

void ChatView::leaveEvent(QEvent *event)
{
    ui->chat_area->verticalScrollBar()->setHidden(true);
    QWidget::leaveEvent(event);
}
