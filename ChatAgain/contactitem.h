#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QWidget>
#include "listitembase.h"
#include "usermgr.h"

namespace Ui {
class ContactItem;
}

class ContactItem : public ListItemBase
{
    Q_OBJECT

public:
    explicit ContactItem(QWidget *parent = nullptr);
    ~ContactItem();
    void showRedDot(bool show = true);
    void setInfo(QString name,QString icon);
    std::shared_ptr<FriendInfo> getInfo();
private:
    Ui::ContactItem *ui;
    std::shared_ptr<FriendInfo> _info;
};

#endif // CONTACTITEM_H
