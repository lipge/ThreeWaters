#ifndef CHATUSERLIST_H
#define CHATUSERLIST_H
#include <QListWidget>
#include <QWheelEvent>
#include <QScrollBar>
#include "userdata.h"

class ChatUserList:public QListWidget
{
    Q_OBJECT
public:
    ChatUserList(QWidget* parent=nullptr);
    void addChatUserList();
    void appendChatList();
    void updateChatList(std::shared_ptr<FriendInfo> friend_info);
    bool alreadyInChatList(int friend_uid);
protected:
//    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;

private:
    std::unordered_map<int, std::shared_ptr<FriendInfo>> _chats;
//    std::unordered_map<int, std::shared_ptr<FriendInfo>> _chats;
signals:
    // 加载新的聊天记录
    void sig_loading_chat_user();
};

#endif // CHATUSERLIST_H
