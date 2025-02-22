#include "newfriendpage.h"
#include "ui_newfriendpage.h"
#include "tcpmgr.h"
#include "usermgr.h"
#include "authenfriend.h"
#include <QRandomGenerator>

NewFriendPage::NewFriendPage(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::NewFriendPage)
{
	ui->setupUi(this);
	initApplication();
}

NewFriendPage::~NewFriendPage()
{
	delete ui;
}

void NewFriendPage::initApplication()
{
	auto& app = UserMgr::GetInstance()->getApplicationList();
	for (auto& iter : app) {
		addNewApplication(iter.second);
	}
}
void NewFriendPage::addNewApplication(std::shared_ptr<ApplyInfo> info)
{
	auto* contact = new NewFriendItem(this);

	contact->setInfo(info);
	QListWidgetItem* item = new QListWidgetItem;
	// 移除 Qt::ItemIsEnabled 和 Qt::ItemIsSelectable 标志
	item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

	item->setSizeHint(contact->sizeHint());
	ui->applications_list->addItem(item);
	ui->applications_list->setItemWidget(item, contact);

	// 连接item发出的更新联系人列表的信号
	connect(contact, &NewFriendItem::addBtnClicked, this, [this, info]() {
		AuthenFriend* authpage = new AuthenFriend(this);
		std::shared_ptr<AuthInfo> toinfo = std::make_shared<AuthInfo>(info->_uid
			, info->_sex
			, info->_name
			, info->_nick
			, info->_icon
		);
		authpage->setAuthInfo(toinfo);
		authpage->show();
		});
	// Tcp处理完回包，得到同意添加结果后更改按钮状态
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_updateContactsList, contact, &NewFriendItem::slot_changeBtn);

	// 存一下好友申请信息
	_friend_items[info->_uid] = contact;

}



void NewFriendPage::showAuthenPage()
{

}
