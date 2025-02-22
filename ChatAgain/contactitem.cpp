#include "contactitem.h"
#include "ui_contactitem.h"

ContactItem::ContactItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ContactItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CONTACT_USER_ITEM);
    ui->dot_lab->raise();// 提升至最前
    showRedDot(false);
}

ContactItem::~ContactItem()
{
    delete ui;
}

void ContactItem::showRedDot(bool show)
{
    if(show){
        ui->dot_lab->show();
    }
    else{
        ui->dot_lab->hide();
    }
}

void ContactItem::setInfo(QString name, QString icon)
{
    QPixmap headshot(icon);
    ui->icon_lab->setPixmap(headshot.scaled(ui->icon_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lab->setScaledContents(true);  // 联系人头像
    ui->name_lab->setText(name);      // 联系人昵称

    _info = UserMgr::GetInstance()->getFriend(name);
}

std::shared_ptr<FriendInfo> ContactItem::getInfo()
{
    return _info;
}
