#include "friendinfopage.h"
#include "ui_friendinfopage.h"

FriendInfoPage::FriendInfoPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FriendInfoPage)
{
    ui->setupUi(this);
}

FriendInfoPage::~FriendInfoPage()
{
    delete ui;
}

void FriendInfoPage::setInfo(std::shared_ptr<FriendInfo> fi)
{
    QPixmap head_short(fi->_icon);
    head_short = head_short.scaled(ui->head_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap sex;
    if(fi->_sex)
        sex.load(":/res/male.png");
    else
        sex.load(":/res/female.png");
    sex = sex.scaled(ui->sex_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->REMARK->setText(fi->_back);
    ui->nick_lab->setText(fi->_name);
    ui->remark_lab->setText(fi->_name);
    ui->head_lab->setPixmap(head_short);
//    ui->email_lab->setText(fi->)
    ui->sex_lab->setPixmap(sex);

    _fi = fi;
}


void FriendInfoPage::on_chat_btn_clicked()
{
    emit sig_switch_chat_page(_fi);
}

