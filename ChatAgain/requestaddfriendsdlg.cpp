#include "requestaddfriendsdlg.h"
#include "ui_requestaddfriendsdlg.h"
#include "friendlabel.h"
#include "usermgr.h"
#include "customizeedit.h"
#include <QScrollBar>
#include <QJsonDocument>
#include "tcpmgr.h"
/**
 * @brief 申请添加好友界面
 * 用户搜索框搜索成功后点击“添加到通讯录”按钮跳转该界面
 */

RequestAddFriendsDlg::RequestAddFriendsDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RequestAddFriendsDlg)
    , _lab_x(2)
{
    ui->setupUi(this);
//    setWindowFlags()
    this->setModal(true);
    ui->whoIm_edit->setPlaceholderText(UserMgr::GetInstance()->getUserInfo()->_name);
    ui->labinput_edit->setPlaceholderText("搜索、添加标签");

    //_tip_cur_point = QPoint(5, 5);
    // 测试数据
    _tip_data = { "同学","家人","菜鸟教程","C++ Primer","Rust 程序设计",
                 "父与子学Python","nodejs开发指南","go 语言开发指南",
                 "游戏伙伴","金融投资","微信读书","拼多多拼友" };
    // 标签输入框更改时，同步至展示标签
    connect(ui->labinput_edit, &QLineEdit::textChanged, this, [this](QString text){ui->show_lab->setText(text);});
    // 重写标签输入框焦点策略
    connect(ui->labinput_edit, &CustomizeEdit::focusIn, this, [this](){showWid(true);});
    connect(ui->labinput_edit, &CustomizeEdit::focusOut, this, [this](){showWid(false);});
    // 添加标签
    connect(ui->show_lab, &ClickedOnceLabel::clicked, this, &RequestAddFriendsDlg::slot_addlabel);


    ui->scrollArea->installEventFilter(this);
    ui->show_wid->hide();
}

RequestAddFriendsDlg::~RequestAddFriendsDlg()
{
    delete ui;
}

void RequestAddFriendsDlg::initTips()
{

}

void RequestAddFriendsDlg::addTips()
{

}

void RequestAddFriendsDlg::setSearchInfo(std::shared_ptr<SearchInfo> si)
{
    auto self = UserMgr::GetInstance()->getUserInfo()->_name;
    qDebug()<<"发送好友申请时，申请人名称："<<self;
    ui->whoIm_edit->setText("我是" + self);
    ui->remark_edit->setText(si->_name);
    _si = si;
}



void RequestAddFriendsDlg::slot_addlabel(QString text)
{
    qDebug()<<text;
    FriendLabel* fd = new FriendLabel(ui->labinput_wid);
    // 删除标签
    connect(fd, &FriendLabel::sig_close, [this](FriendLabel* fd){_lab_x -= fd->Width()+5;});
    fd->setText(text);
    fd->move(_lab_x, 2);
    fd->show();
    _lab_x += fd->Width()+5;

    ui->labinput_edit->move(_lab_x, 0);
}



void RequestAddFriendsDlg::showWid(bool willshow)
{
    if(willshow){
        ui->show_lab->setText(ui->labinput_edit->text());
        ui->show_wid->show();
    }
    else{
    //    ui->show_lab->clear();
        ui->show_wid->hide();
    }
}


bool RequestAddFriendsDlg::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->scrollArea){
        if(event->type() == QEvent::Enter){
            ui->scrollArea->verticalScrollBar()->show();
        }
        else if(event->type() == QEvent::Leave){
            ui->scrollArea->verticalScrollBar()->hide();
        }
    }
    return QDialog::eventFilter(object, event);
}

void RequestAddFriendsDlg::on_cancle_btn_clicked()
{
    this->close();
}

void RequestAddFriendsDlg::on_confim_btn_clicked()
{
    auto info = UserMgr::GetInstance()->getUserInfo();
    auto uid = info->_uid;
    auto name = info->_name;
    auto desc = ui->whoIm_edit->text();


    QJsonObject jsonObj;
    jsonObj["uid"] = uid;
    jsonObj["touid"] = _si->_uid;
    jsonObj["applyname"] = name;
    jsonObj["desc"] = desc;
    qDebug() << "申请人id" << uid;
    qDebug() << "对方id" << _si->_uid;
    QJsonDocument doc(jsonObj);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
    // 发送申请添加好友信息
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_ADD_FRIEND_REQ, jsonData);

    this->close();
}

