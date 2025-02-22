#include "newfrienditem.h"
#include "ui_newfrienditem.h"


NewFriendItem::NewFriendItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewFriendItem)
{
    ui->setupUi(this);
}

NewFriendItem::~NewFriendItem()
{
    delete ui;
}

void NewFriendItem::setInfo(std::shared_ptr<ApplyInfo> info)
{
    QPixmap headshot(info->_icon);
    ui->head_lab->setPixmap(headshot.scaled(ui->head_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->head_lab->setScaledContents(true);  // 联系人头像
    ui->name_lab->setText(info->_name);      // 联系人昵称
    ui->desc_lab->setText(info->_desc);

    _app_info = info;
}

void NewFriendItem::slot_changeBtn()
{
    ui->add_btn->setEnabled(false);// 使按钮失效
    ui->add_btn->setText("已添加");
}

void NewFriendItem::on_add_btn_clicked()
{
    emit addBtnClicked();
}

