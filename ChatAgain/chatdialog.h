#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include "statewidget.h"
#include "userdata.h"
#include <QListWidgetItem>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

private:
    Ui::ChatDialog *ui;
    void mousePressEvent(QMouseEvent *event) override;
    void ShowSearch(bool b_show);
    ChatUIMode _mode;
    bool _b_loading;
    QVector<StateWidget*> _sidebar_wids;
    bool has_clicked_chat;
    bool has_clicked_contact;
    QWidget* last_chat_page;
    QWidget* last_contact_page;
private slots:
//    void slot_loading_chat_user();
    void slot_switch_chat();
    void slot_switch_contracts_list();
    void slot_friend_apply(std::shared_ptr<ApplyInfo>);
    void slot_friend_authen(std::shared_ptr<AuthInfo>);
    void slot_switch_chat_page(std::shared_ptr<FriendInfo>);
    void slot_chat_item_clicked(QListWidgetItem* chat_item);
    // 跳转好友详情界面 或者 新的朋友界面
    void slot_switch_friend_page(QListWidgetItem* friend_item);
    // 好友发来文本信息
    void slot_text_chat_msg(std::shared_ptr<TextChatMsg> text_msg);
};

#endif // CHATDIALOG_H
