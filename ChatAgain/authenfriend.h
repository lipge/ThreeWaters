#ifndef AUTHENFRIEND_H
#define AUTHENFRIEND_H

#include <QDialog>
#include "userdata.h"
#include "clickedlabel.h"

namespace Ui {
class AuthenFriend;
}

class AuthenFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenFriend(QWidget *parent = nullptr);
    ~AuthenFriend();

    void initTips();
    void addTips();
    void setAuthInfo(std::shared_ptr<AuthInfo> si);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event) override;

public slots:
    void on_cancle_btn_clicked();
    void slot_addlabel(QString text);// 添加标签

private:
    Ui::AuthenFriend *ui;
    QVector<QString> _tip_data;
    int _lab_x;
    //已经创建好的标签
    QMap<QString, ClickedLabel*> _add_labels;
    void resetLabels();
    std::shared_ptr<AuthInfo> _si;// 好友信息

private slots:
    void showWid(bool willshow);
    void on_confim_btn_clicked();

};

#endif // AUTHENFRIEND_H
