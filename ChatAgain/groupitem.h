#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>
#include "listitembase.h"

namespace Ui {
class GroupItem;
}

class GroupItem : public ListItemBase
{
    Q_OBJECT

public:
    explicit GroupItem(QWidget *parent = nullptr);
    ~GroupItem();
    void setText(QString text);
private:
    Ui::GroupItem *ui;
};

#endif // GROUPITEM_H
