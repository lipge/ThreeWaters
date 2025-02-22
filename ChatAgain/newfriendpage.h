#ifndef NEWFRIENDPAGE_H
#define NEWFRIENDPAGE_H

#include <QWidget>
// #include "userdata.h"
#include "newfrienditem.h"
#include <unordered_map>

namespace Ui {
class NewFriendPage;
}

class NewFriendPage : public QWidget
{
    Q_OBJECT

public:
    explicit NewFriendPage(QWidget *parent = nullptr);
    ~NewFriendPage();

    void addNewApplication(std::shared_ptr<ApplyInfo> info);
private:
    Ui::NewFriendPage *ui;
    std::unordered_map<int, NewFriendItem*> _friend_items;
    void initApplication();
private slots:
    void showAuthenPage();

signals:
    void updateContactsList(QString name, QString icon);
};

#endif // NEWFRIENDPAGE_H
