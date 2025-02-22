#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QMouseEvent>
#include <QRandomGenerator>
#include "customizeedit.h"
#include "searchlist.h"
#include "tcpmgr.h"
#include "usermgr.h"
#include "newfriendpage.h"
#include "chatuserwid.h"
#include "contactitem.h"
#include "friendinfopage.h"

ChatDialog::ChatDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::ChatDialog)
	, _mode(ChatUIMode::ChatMode)
	, _b_loading(false)
	, has_clicked_chat(false)
	, has_clicked_contact(false)
{
	last_chat_page = ui->default_page;
	last_contact_page = ui->default_page;
	ui->setupUi(this);
	ui->add_btn->SetState("normal", "hover", "press");
	// 搜索栏图标
	QAction* searchAction = new QAction(this);
	searchAction->setIcon(QIcon(":/res/search.png"));
	ui->search_edit->addAction(searchAction, QLineEdit::LeadingPosition);

	// 搜索栏占位文字
	ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));
	ui->search_edit->setClearButtonEnabled(true);                   // 添加手动清除功能按钮
	connect(ui->search_edit, &CustomizeEdit::focusIn, [this]() { ShowSearch(true); });        // 焦点进入
	connect(ui->search_edit, &CustomizeEdit::focusOut, [this]() { ShowSearch(false); });      // 失去焦点
	connect(ui->search_list, &SearchList::sig_listarea_clicked, [this]() {                   // 点击了搜索列表区域
		this->ui->search_edit->setFocus();
		});


	// 侧边栏
	ui->chat_sidebar->setPixmap(":/res/chat_icon.png", ":/res/chat_icon_hover.png", ":/res/chat_icon_press.png");
	ui->contracts_sidebar->setPixmap(":/res/contact_list.png", ":/res/contact_list_hover.png", ":/res/contact_list_press.png");
	_sidebar_wids.append(ui->chat_sidebar);
	_sidebar_wids.append(ui->contracts_sidebar);
	connect(ui->chat_sidebar, &StateWidget::clicked, this, &ChatDialog::slot_switch_chat);
	connect(ui->contracts_sidebar, &StateWidget::clicked, this, &ChatDialog::slot_switch_contracts_list);

	// 设置初始状态
	ShowSearch(false);  // 搜索框接口，隐藏搜索框
	ui->chat_sidebar->setSelected();
	ui->search_list->setSearchEdit(ui->search_edit);// 设置搜索列表绑定的搜索框
    ui->stackedWidget->setCurrentWidget(ui->default_page);

    QPixmap headshot(UserMgr::GetInstance()->getUserInfo()->_icon);
    headshot = headshot.scaled(ui->headshot_sidebar->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->headshot_sidebar->setPixmap(headshot);      // 加载用户头像

	// 新的朋友申请，新朋友界面插入好友条目，并让联系人列表中“新的朋友”条目展示红点
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_friend_apply, this, &ChatDialog::slot_friend_apply);
	// 用户点击了新的朋友界面中“申请条目”的“添加”按钮，要将此联系人更新至用户好友列表，以及聊天记录列表
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_updateContactsList, this, &ChatDialog::slot_friend_authen);
	// 搜索的用户信息已经是好友，跳转聊天界面
	connect(ui->search_list, &SearchList::sig_switch_friend_chat_item, this, &ChatDialog::slot_switch_chat_page);
	// 点击了聊天记录，跳转与该用户的聊天界面
	connect(ui->chat_user_list, &QListWidget::itemClicked, this, &ChatDialog::slot_chat_item_clicked);
	// 点击了联系人条目，跳转好友详情界面
	connect(ui->con_user_list, &QListWidget::itemClicked, this, &ChatDialog::slot_switch_friend_page);
	// 在好友详情界面点击了发送消息按钮，跳转聊天界面
	connect(ui->friendinfo_page, &FriendInfoPage::sig_switch_chat_page, this, &ChatDialog::slot_switch_chat_page);
	// 好友发来消息
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_text_chat_msg, this, &ChatDialog::slot_text_chat_msg);
}

ChatDialog::~ChatDialog()
{
	delete ui;
	qDebug() << "ChatDialog destruct";
}

void ChatDialog::mousePressEvent(QMouseEvent* event)
{
	// 获取鼠标点击位置所在的widget
	QWidget* clickedWidget = QApplication::widgetAt(event->globalPosition().toPoint());
	// 获取search_edit的action列表，删除行为是第二个被添加所以是actions[1]
	QList<QAction*> actions = ui->search_edit->actions();
	if (clickedWidget == ui->search_edit) {
		//    actions[1]->setIcon(QIcon(":/res/close_search.png"));
	}
	else {
		ui->search_edit->clear();
		ui->search_edit->clearFocus();
		ShowSearch(false);
		//    update();
	}

	QWidget::mousePressEvent(event);
}

void ChatDialog::ShowSearch(bool b_show)
{
	if (b_show) {

		ui->chat_user_list->hide();
		ui->con_user_list->hide();
		ui->search_list->show();
	}
	else {
		if (_mode == ChatUIMode::ChatMode) {
			ui->chat_user_list->show();
			ui->con_user_list->hide();
		}
		else if (_mode == ChatUIMode::ContactMode) {
			ui->chat_user_list->hide();
			ui->con_user_list->show();
		}

		ui->search_list->hide();
	}
}

void ChatDialog::slot_switch_chat()
{
	for (auto& it : _sidebar_wids) {
		if (it == ui->chat_sidebar) continue;
		it->clearState();
	}
	if (has_clicked_chat) {
		ui->stackedWidget->setCurrentWidget(ui->chat_page);
	}
	else
		ui->stackedWidget->setCurrentWidget(ui->default_page);
	ui->con_user_list->hide();
	ui->chat_user_list->show();
	_mode = ChatUIMode::ChatMode;
}

void ChatDialog::slot_switch_contracts_list()
{
	for (auto& it : _sidebar_wids) {
		if (it == ui->contracts_sidebar) continue;
		it->clearState();
	}
	if (has_clicked_contact) {
		ui->stackedWidget->setCurrentWidget(last_contact_page);
	}
	else
		ui->stackedWidget->setCurrentWidget(ui->default_page);
	ui->con_user_list->show();
	ui->chat_user_list->hide();
	_mode = ChatUIMode::ContactMode;
}

void ChatDialog::slot_friend_apply(std::shared_ptr<ApplyInfo> info)
{
	if (UserMgr::GetInstance()->alreadyApply(info->_uid))return;

	UserMgr::GetInstance()->updateApplyList(info);
	ui->newfriend_page->addNewApplication(info);
	//
	ui->con_user_list->showRedDot(true);
}

void ChatDialog::slot_friend_authen(std::shared_ptr<AuthInfo> info)
{

	UserMgr::GetInstance()->addFrined(info);
	ui->con_user_list->updateContactsList(info->_name, info->_icon);
	ui->chat_user_list->updateChatList(std::make_shared<FriendInfo>(info));
}

void ChatDialog::slot_switch_chat_page(std::shared_ptr<FriendInfo> fi)
{
	ui->chat_page->setPageInfo(fi);         // 设置信息
	ui->stackedWidget->setCurrentWidget(ui->chat_page);                 // 展示界面
	ui->con_user_list->hide();                                          // 隐藏联系人列表
	ui->search_list->hide();                                            // 隐藏搜索列表
	ui->chat_user_list->show();                                         // 展示聊天列表
	_mode = ChatUIMode::ChatMode;                                       // 更改模式
}

// 点击聊条记录列表条目时触发
void ChatDialog::slot_chat_item_clicked(QListWidgetItem* chat_item)
{
	has_clicked_chat = true;
	auto itemwid = ui->chat_user_list->itemWidget(chat_item);
	ChatUserWid* chat_wid = qobject_cast<ChatUserWid*>(itemwid);
	if (chat_wid == nullptr || chat_wid->GetItemType() != ListItemType::CHAT_USER_ITEM)return;
	auto info = chat_wid->getInfo();
	ui->chat_page->setPageInfo(info);
	ui->stackedWidget->setCurrentWidget(ui->chat_page);

	//	last_page = ui->chat_page;
}

// 点击联系人列表条目时触发
void ChatDialog::slot_switch_friend_page(QListWidgetItem* friend_item)
{

	auto itemwid = ui->con_user_list->itemWidget(friend_item);
	ContactItem* friend_wid = qobject_cast<ContactItem*>(itemwid);
	if (friend_wid == nullptr) return;
	if (friend_wid->GetItemType() == ListItemType::NEW_FRIEND_ITEM) {
		ui->stackedWidget->setCurrentWidget(ui->newfriend_page);    // 跳转新的朋友界面
		friend_wid->showRedDot(false);

		has_clicked_contact = true;
		last_contact_page = ui->newfriend_page;
		return;
	}

	if (friend_wid->GetItemType() != ListItemType::CONTACT_USER_ITEM)return;
	has_clicked_contact = true;
	auto info = friend_wid->getInfo();
	ui->friendinfo_page->setInfo(info);
	ui->stackedWidget->setCurrentWidget(ui->friendinfo_page);


	has_clicked_contact = true;
	last_contact_page = ui->friendinfo_page;
}

void ChatDialog::slot_text_chat_msg(std::shared_ptr<TextChatMsg> text_msg)
{
	for (auto& it : text_msg->_chat_msgs) {
        UserMgr::GetInstance()->appendFriendMesssage(text_msg->_from_uid, it);		// 存到背地
		ui->chat_page->appendChatData(it);											// 更新界面
	}
}

