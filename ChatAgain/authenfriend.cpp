#include "authenfriend.h"
#include "ui_authenfriend.h"
#include "usermgr.h"
#include "friendlabel.h"
#include <QScrollBar>
#include "tcpmgr.h"
#include <QJsonDocument>

AuthenFriend::AuthenFriend(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthenFriend)
    , _lab_x(2)
{
    ui->setupUi(this);
    //    setWindowFlags()
    this->setModal(true);

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
    connect(ui->show_lab, &ClickedOnceLabel::clicked, this, &AuthenFriend::slot_addlabel);


    ui->scrollArea->installEventFilter(this);
    ui->show_wid->hide();
}

AuthenFriend::~AuthenFriend()
{
    delete ui;
}

void AuthenFriend::initTips()
{

}

void AuthenFriend::addTips()
{

}

void AuthenFriend::setAuthInfo(std::shared_ptr<AuthInfo> si)
{
    _si = si;
    ui->remark_edit->setText(si->_name);
}

void AuthenFriend::slot_addlabel(QString text)
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



void AuthenFriend::showWid(bool willshow)
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


bool AuthenFriend::eventFilter(QObject *object, QEvent *event)
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

void AuthenFriend::on_cancle_btn_clicked()
{
    this->close();
}
void AuthenFriend::on_confim_btn_clicked()
{
    QJsonObject jsonObj;
    jsonObj["uid"] = UserMgr::GetInstance()->getUserInfo()->_uid;
    jsonObj["touid"] = _si->_uid;
    jsonObj["remark"] = ui->remark_edit->text();// 给对方的备注

    QJsonDocument doc(jsonObj);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
    emit TcpMgr::GetInstance()->sig_send_data(ID_AUTH_FRIEND_REQ, jsonData);

    this->close();
}

