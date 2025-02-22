#ifndef SEARCHLIST_H
#define SEARCHLIST_H

#include <QListWidget>
#include "findresdlg.h"

class SearchList : public QListWidget
{
    Q_OBJECT
public:
    SearchList(QWidget *parent = nullptr);
    void setSearchEdit(QWidget* edit);
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void addTipItem();
    FindResDlg* _find_dlg;
signals:
    void sig_listarea_clicked();
    void sig_switch_friend_chat_item(std::shared_ptr<FriendInfo>);
private slots:
    void slot_item_clicked(QListWidgetItem* item);
    void slot_user_search(std::shared_ptr<SearchInfo> search_info);
private:
    QWidget* _search_edit;
};

#endif // SEARCHLIST_H
