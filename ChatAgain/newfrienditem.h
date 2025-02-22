#ifndef NEWFRIENDITEM_H
#define NEWFRIENDITEM_H

#include <QWidget>
#include <memory.h>
#include "userdata.h"

namespace Ui {
class NewFriendItem;
}

class NewFriendItem : public QWidget
{
    Q_OBJECT

public:
    explicit NewFriendItem(QWidget *parent = nullptr);
    ~NewFriendItem();
    void setInfo(std::shared_ptr<ApplyInfo> info);
private:
    Ui::NewFriendItem *ui;
    std::shared_ptr<ApplyInfo> _app_info;

public slots:
    void slot_changeBtn();

private slots:
    void on_add_btn_clicked();
signals:
    void updateContactsList(QString name, QString headshort);
    void addBtnClicked();
};

#endif // NEWFRIENDITEM_H
