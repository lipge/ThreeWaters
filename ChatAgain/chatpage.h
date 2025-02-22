#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include "usermgr.h"

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
    void setPageInfo(std::shared_ptr<FriendInfo> info);
    // ֻ��������Ⱦ�����Ա�����Ϣ���и���
    void appendChatData(std::shared_ptr<TextChatData> data);
protected:
    // void paintEvent(QPaintEvent *event);

private slots:
    void on_send_btn_clicked();

private:
    Ui::ChatPage *ui;
    std::shared_ptr<FriendInfo> _user_info;
};

#endif // CHATPAGE_H
