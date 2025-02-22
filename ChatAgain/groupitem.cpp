#include "groupitem.h"
#include "ui_groupitem.h"

GroupItem::GroupItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::GroupItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::GROUP_TIP_ITEM);
//    ui->label->setScaledContents(true);  // 联系人头像

}

GroupItem::~GroupItem()
{
    delete ui;
}

void GroupItem::setText(QString text)
{
    ui->label->setText(text);
}
