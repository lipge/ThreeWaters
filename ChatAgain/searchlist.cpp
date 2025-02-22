#include "searchlist.h"
#include <QEvent>
#include <QObject>
#include <QScrollBar>
#include <QWheelEvent>
#include "adduseritem.h"
#include "listItembase.h"
#include "customizeedit.h"
#include <QJsonDocument>
#include "tcpmgr.h"
#include "usermgr.h"

SearchList::SearchList(QWidget *parent)
    :QListWidget(parent),_search_edit(nullptr)
{
    this->viewport()->installEventFilter(this);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    addTipItem();
    _find_dlg = new FindResDlg(this);
    // item点击信号
    connect(this, &QListWidget::itemClicked, this, &SearchList::slot_item_clicked);
    // 搜索框搜索，tcp回包信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_user_search, this, &SearchList::slot_user_search);
}

void SearchList::setSearchEdit(QWidget *edit)
{
    _search_edit = edit;
}

bool SearchList::eventFilter(QObject *object, QEvent *event)
{
    if(object == this->viewport()){
        if(event->type() == QEvent::Enter){
            this->verticalScrollBar()->show();
        }
        else if(event->type() == QEvent::Leave){
            this->verticalScrollBar()->hide();
        }
    }
    // 检查事件是否是鼠标滚轮事件
    if (object == this->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int numDegrees = wheelEvent->angleDelta().y() / 8;
        int numSteps = numDegrees / 15; // 计算滚动步数
        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);
        return true; // 停止事件传递
    }
    return QListWidget::eventFilter(object, event);
}

void SearchList::mousePressEvent(QMouseEvent *event) {
    emit sig_listarea_clicked();
    QListWidget::mousePressEvent(event); // 调用基类实现
}

void SearchList::addTipItem()
{
    // auto *invalid_item = new QWidget();
    // QListWidgetItem *item_tmp = new QListWidgetItem;
    // //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    // item_tmp->setSizeHint(QSize(250,10));
    // this->addItem(item_tmp);
    // invalid_item->setObjectName("invalid_item");
    // this->setItemWidget(item_tmp, invalid_item);
    // item_tmp->setFlags(item_tmp->flags() & ~Qt::ItemIsSelectable);
    auto *add_user_item = new AddUserItem();
    QListWidgetItem *item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(add_user_item->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, add_user_item);
}

void SearchList::slot_item_clicked(QListWidgetItem *item)
{

    QWidget* wid = this->itemWidget(item);
    ListItemBase* customitem = qobject_cast<ListItemBase*>(wid);
    if(customitem->GetItemType() == ListItemType::ADD_USER_TIP_ITEM){

        // 从搜索框edit中获取信息
        auto uid_str = qobject_cast<CustomizeEdit*>(_search_edit)->text();
        if(uid_str == "")return;        // 空字符串直接返回
        qDebug()<<"搜索内容："<<uid_str;

        // 如果搜索的id 或 name 已经是好友则直接return
        if(UserMgr::GetInstance()->alreadyBeFriend(uid_str.toInt())){
            auto fi = UserMgr::GetInstance()->getFriend(uid_str.toInt());
            emit sig_switch_friend_chat_item(fi);
            return;
        }
        if(UserMgr::GetInstance()->alreadyBeFriend(uid_str)){
            auto fi = UserMgr::GetInstance()->getFriend(uid_str.toInt());
            emit sig_switch_friend_chat_item(fi);
            return;
        }
        QJsonObject jsonObj;
        jsonObj["uid"] = uid_str;
        QJsonDocument doc(jsonObj);
        QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
        // 发送搜索框中的信息
        emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_SEARCH_USER_REQ, jsonData);
        return;
    }

    //其他item...
}

void SearchList::slot_user_search(std::shared_ptr<SearchInfo> si)
{
    if(si == nullptr){
        _find_dlg->showDlg(false);      // 搜索失败界面
        return;
    }

    // 如果已经是用户好友...
    //if()

    _find_dlg->setSearchInfo(si);
    _find_dlg->showDlg(true);           // 搜索成功界面
}



