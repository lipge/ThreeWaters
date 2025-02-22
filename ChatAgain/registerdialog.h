#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
#include <QTimer>
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();


private slots:
    void on_getButton_clicked();            // 获取验证码按钮点击
    void slot_reg_mod_finish(ReqId id,QString res, ErrorCodes ec);      // 注册请求回包处理槽函数

    void on_confirm_btn_clicked();          // 确认注册
    bool checkUserValid();                  // 检测用户名是否合理
    bool checkEmailValid();                 // 检测邮箱是否合理
    bool checkPassValid();                  // 检测密码是否合理
    bool checkConfirmValid();               // 检测确认密码是否合理
    bool checkVarifyValid();                // 检测验证码是否合理

    void on_return_btn_clicked();           // 注册完成提前返回
    void on_cancel_btn_clicked();           // 取消注册

private:
    void showTip(QString str,bool b_ok);
    void initHttpHandlers();
    void changePage();
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    Ui::RegisterDialog *ui;
    QMap<TipErr, QString> _tip_errs;    // 当有多条错误信息时存入map中管理，用户纠正某个错误后展示剩下的错误信息

    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);

    QTimer* _return_timer;              // 注册成功，设置一个定时器自动返回登录界面
    int _timer_cnt;
signals:
    void sigSwitchLogin();
};

#endif // REGISTERDIALOG_H
