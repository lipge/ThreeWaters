#include "loginfailed.h"
#include "ui_loginfailed.h"

LoginFailed::LoginFailed(LoginState state, const QPoint& parentPos, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginFailed)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint);

    if(state == LoginState::RPCFailed || state == LoginState::PostFailed || state == LoginState::TCPFailed){
        ui->foget_Btn->close();
        ui->label->setText(tr("提示"));
        ui->label_2->setText(tr("登录失败,请稍后重试"));
    }
    // 计算 failed 窗口的位置，使其在当前窗口中央
    int x = parentPos.x() - (this->width() / 2);
    int y = parentPos.y() - (this->height() / 2);
    this->move(x,y);
}

LoginFailed::~LoginFailed()
{
    delete ui;
}





void LoginFailed::on_foget_Btn_clicked()
{
    emit turn_forget();
    this->close();
}


void LoginFailed::on_return_Btn_clicked()
{
    this->close();
}

