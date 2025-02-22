#ifndef NEWFRIENDLIST_H
#define NEWFRIENDLIST_H

#include <QListWidget>


class NewFriendList : public QListWidget
{
    Q_OBJECT
public:
    NewFriendList(QWidget* parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent *e) override;
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;

signals:
    void sig_loading_applications();

};

#endif // NEWFRIENDLIST_H
