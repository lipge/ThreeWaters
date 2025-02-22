#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include "global.h"
namespace Ui {
class LoginDialog;
class LoginFailed;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    Ui::LoginFailed *_log_failed;

    bool checkEmailValid();
    bool checkPwdValid();
    bool setLoginBtnEnable();

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    void initHttpHandlers();
    int _uid;
    QString _token;
signals:
    void SwitchRegister();
    void SwitchReset();
    void SwitchChat();
    void sig_connect_tcp(ServerInfo);
private slots:
    void on_login_Button_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool success);
//    void slot_switch_chat
    void on_register_Button_clicked();
};

#endif // LOGINDIALOG_H
