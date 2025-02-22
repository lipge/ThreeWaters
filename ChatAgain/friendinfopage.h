#ifndef FRIENDINFOPAGE_H
#define FRIENDINFOPAGE_H

#include <QWidget>
#include "usermgr.h"

namespace Ui {
	class FriendInfoPage;
}

class FriendInfoPage : public QWidget
{
	Q_OBJECT

public:
	explicit FriendInfoPage(QWidget* parent = nullptr);
	~FriendInfoPage();
	void setInfo(std::shared_ptr<FriendInfo> fi);
//	std::shared_ptr<FriendInfo> getInfo();
private slots:

    void on_chat_btn_clicked();
signals:
    void sig_switch_chat_page(std::shared_ptr<FriendInfo>);
private:
	Ui::FriendInfoPage* ui;
    std::shared_ptr<FriendInfo> _fi;
};

#endif // FRIENDINFOPAGE_H
