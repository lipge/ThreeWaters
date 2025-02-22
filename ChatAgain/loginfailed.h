#ifndef LOGINFAILED_H
#define LOGINFAILED_H

#include <QDialog>
#include "global.h"
namespace Ui {
class LoginFailed;
}

class LoginFailed : public QDialog
{
    Q_OBJECT

public:
    explicit LoginFailed(LoginState state, const QPoint& parentPos, QWidget *parent = nullptr);
    ~LoginFailed();
private:
    Ui::LoginFailed *ui;
private slots:


    void on_foget_Btn_clicked();

    void on_return_Btn_clicked();

signals:
    void turn_forget();
};

#endif // LOGINFAILED_H
