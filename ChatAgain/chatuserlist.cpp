#include "chatuserlist.h"
#include <QRandomGenerator>
#include "chatuserwid.h"
#include "usermgr.h"

ChatUserList::ChatUserList(QWidget* parent)
    :QListWidget(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->viewport()->installEventFilter(this);



    // 鼠标下滑加载新的聊天记录
    //connect(this, &ChatUserList::sig_loading_chat_user, addChatUserList);
    addChatUserList();
    appendChatList();
}

void ChatUserList::wheelEvent(QWheelEvent *e)
{
    //int ratio = 2; // 比例
    // int numDegrees = e->angleDelta().y() / 8;
    // int numSteps = numDegrees / 15; // 计算滚动步数
    // 设置幅度
    //this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() / ratio);
    // 检查是否到底部
    int maxVal = this->verticalScrollBar()->maximum();
    int currentVal = this->verticalScrollBar()->value();
    if(currentVal >= maxVal){
        emit sig_loading_chat_user();
    }

    QListWidget::wheelEvent(e);
}

void ChatUserList::leaveEvent(QEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListView::leaveEvent(event);
}

void ChatUserList::enterEvent(QEnterEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QListView::enterEvent(event);
}


static std::vector<QString>  strs ={
    "快过年了,不要再讨论什么Go、Python、Java之类的了。"
    "你默默的在家里摆弄你的破烂框架。亲戚朋友吃饭问你收获了什么。你说我做了个框架，把Spring、Django、​Gi​n优点都结合了一遍，亲戚们懵逼了"
    "，你还在心里默默嘲笑他们。笑他们不懂你的轮子、不懂你的算法、不懂你的封装，也笑他们连个复杂点的密码都记不住。"
    "你父母的同事都在说自己的子女年的收获，儿子买了个房，女儿买了个车，姑娘升职加薪了。你的父母默默无言 ，"
    "说我娃搞了个破电脑,开起来嗡嗡响、家里电表走得越来越快了, 你的父母还在想你什么时候能买套房子,什么时候能成个家."
    "却一天到晚想的是怎么封装一个牛逼的中间件.即便网上一大堆开源的. 但是即使这样,你依然坚信这是你做的最牛逼. 这是属于你自己的, 然而并没有什么用。"
    "的领导一直在鞭策你,告诉你好好学习代码才不能落后. 让你多加班,你也很认同,你的信仰就是写好代码,钻研最牛逼的技术.时间轮回,一年又一年,"
    "你还在想着新技术出来了,继续努力学习，而你身边的人在考虑啥时候买第二套房子,什么时候生二胎, 你还在捣鼓你的破代码( ᵒ̴̶̷̤໐ᵒ̴̶̷̤ )。"
    "It's almost the New Year, so don't talk about Go, Python, Java or anything like that."
    "You bring your broken computer home and it doesn't do anything real for you, "
    "your friends have a lot of money in their pockets to eat, drink and have fun, and you silently tinker with your broken frame at home."
    "Relatives and friends ask you what you have gained at dinner. You say that I made a framework that combines the advantages of "
    "Spring, Django, and Gin, and your relatives are confused, and you still laugh at them silently in your heart. (o̴̶̷̤໐o̴̶̷̤)."

};

void ChatUserList::addChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        int left = QRandomGenerator::global()->bounded(strs[str_i].size()-50);
        int right = QRandomGenerator::global()->bounded(strs[str_i].size());

        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->setChatListItemInfo(std::make_shared<FriendInfo>(i
            , names[name_i]
            , names[name_i]
            , heads[head_i]
            , 1,"",""
            , strs[str_i].mid(left, 20)));    // 为聊天条目设置信息

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(chat_user_wid->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, chat_user_wid);
    }
}

// 应该想办法获取到最近的聊天信息，而不是获取好友列表
void ChatUserList::appendChatList()
{
    const auto& fdList = UserMgr::GetInstance()->getFriendList();
    for (auto& iter : fdList) {
        updateChatList(iter.second);
    }
}

void ChatUserList::updateChatList(std::shared_ptr<FriendInfo> friend_info)
{
    if (alreadyInChatList(friend_info->_uid))   return;
    auto* chat_user_wid = new ChatUserWid();
    chat_user_wid->setChatListItemInfo(friend_info);    // 为聊天条目设置信息
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(chat_user_wid->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, chat_user_wid);
}

bool ChatUserList::alreadyInChatList(int friend_uid)
{
    return _chats.count(friend_uid);
}
