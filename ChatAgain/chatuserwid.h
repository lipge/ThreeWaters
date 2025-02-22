#ifndef CHATUSERWID_H
#define CHATUSERWID_H

#include "listitembase.h"
#include "userdata.h"

namespace Ui {
class ChatUserWid;
}

class ChatUserWid : public ListItemBase
{
    Q_OBJECT

public:
    explicit ChatUserWid(QWidget *parent = nullptr);
    ~ChatUserWid();

//    QSize sizeHint();
    void setChatListItemInfo(std::shared_ptr<FriendInfo> info);
    std::shared_ptr<FriendInfo> getInfo();

    // ≤‚ ‘”√
    //void SetInfo(QString name, QString head, QString msg);
private:
    Ui::ChatUserWid *ui;
    std::shared_ptr<FriendInfo> _friend_info;
};

#endif // CHATUSERWID_H
