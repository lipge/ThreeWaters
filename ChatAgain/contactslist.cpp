#include "contactslist.h"
#include "tcpmgr.h"
#include "groupitem.h"
#include "contactitem.h"
#include <QRandomGenerator>
#include <QScrollBar>
#include "usermgr.h"
#include "newfrienditem.h"

ContactsList::ContactsList(QWidget *parent)
    :QListWidget(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    addContacts();// 初始化联系人列表
//    connect(this, &QListWidget::itemClicked, this, &ContactsList::slot_item_clicked);

}

void ContactsList::showRedDot(bool show)
{
    ContactItem* item = qobject_cast<ContactItem*>(this->itemWidget(this->item(1)));
    item->showRedDot(show);
}


void ContactsList::wheelEvent(QWheelEvent *e)
{

    int maxVal = this->verticalScrollBar()->maximum();
    int currentVal = this->verticalScrollBar()->value();
    if(currentVal >= maxVal){
    //    qDebug()<<"Load More";
        emit sig_loading_contacts();
    }
    QListWidget::wheelEvent(e);
}

void ContactsList::leaveEvent(QEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListView::leaveEvent(event);
}

void ContactsList::enterEvent(QEnterEvent *event)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QListView::enterEvent(event);
}

// 初始化联系人列表
void ContactsList::addContacts()
{
    // 添加“新的朋友”组条目
    auto* gitem = new GroupItem(this);
    gitem->setText("新的朋友");
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(gitem->sizeHint());
    // 移除 Qt::ItemIsEnabled 和 Qt::ItemIsSelectable 标志
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    this->addItem(item);
    this->setItemWidget(item, gitem);

    // 添加“新的朋友”可点击条目
    ContactItem* newfditem = new ContactItem;
    newfditem->setInfo("新的朋友", ":/res/newfd.png");
    newfditem->SetItemType(ListItemType::NEW_FRIEND_ITEM);
    item = new QListWidgetItem;

    item->setSizeHint(newfditem->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, newfditem);


    // 添加“已添加”组条目
    gitem = new GroupItem(this);
    gitem->setText("已添加");
    item = new QListWidgetItem;
    item->setSizeHint(gitem->sizeHint());
    // 移除 Qt::ItemIsEnabled 和 Qt::ItemIsSelectable 标志
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    this->addItem(item);
    this->setItemWidget(item, gitem);

    // 添加从数据库中获取的好友
    const auto& fdList = UserMgr::GetInstance()->getFriendList();
    for (auto& iter : fdList) {
        updateContactsList(iter.second->_name, iter.second->_icon);
    }

}

void ContactsList::updateContactsList(const QString &name, const QString &headshort)
{
    qDebug()<<"UpdateContactsList";
    auto *contact = new ContactItem(this);

    contact->setInfo(name, headshort);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(contact->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, contact);
}

void ContactsList::slot_item_clicked(QListWidgetItem* item)
{
    ListItemBase* base = qobject_cast<ListItemBase*>(this->itemWidget(item));

    if(base->GetItemType() == ListItemType::NEW_FRIEND_ITEM){
        qDebug()<<"NEW_FRIEND_ITEM Clicked";
        ContactItem* contact = qobject_cast<ContactItem*>(this->itemWidget(item));
        // 跳转新的朋友界面
        emit sig_switch_newfriend();
        contact->showRedDot(false);
    }

    if(base->GetItemType() != ListItemType::CONTACT_USER_ITEM) return;

    qDebug()<<"Contact Item Clicked";
}
