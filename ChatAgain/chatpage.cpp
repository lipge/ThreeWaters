#include "chatpage.h"
#include "ui_chatpage.h"
#include "chatitembase.h"
#include "TextBubble.h"
#include "PictureBubble.h"
#include "messageedit.h"
#include "usermgr.h"
#include <QJsonArray>
#include <QJsonObject>
#include "tcpmgr.h"
#include <QJsonDocument>
#include <Quuid>

ChatPage::ChatPage(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::ChatPage)
{
	ui->setupUi(this);
	QString emoji_normal = ":/res/smile.png";
	QString emoji_hover = ":/res/smile_hover.png";
	QString emoji_press = ":/res/smile_press.png";
	QString file_normal = ":/res/filedir.png";
	QString file_hover = ":/res/filedir_hover.png";
	QString file_press = ":/res/filedir_press.png";
	ui->emoji_lab->SetState(emoji_normal, emoji_hover, emoji_press);
	ui->file_lab->SetState(file_normal, file_hover, file_press);
	ui->send_btn->SetState("normal", "hover", "press");
	ui->recv_btn->SetState("normal", "hover", "press");

}

ChatPage::~ChatPage()
{
	delete ui;
}

void ChatPage::setPageInfo(std::shared_ptr<FriendInfo> info)
{
	_user_info = info;
	ui->contact_lab->setText(info->_name);
	ui->chat_data_list->rmAllItem();
	for (auto& iter : info->_chat_msgs) {
		appendChatData(iter);
	}
}
// 只做界面渲染，不对本地信息进行更改
void ChatPage::appendChatData(std::shared_ptr<TextChatData> data)
{
	auto info = UserMgr::GetInstance()->getUserInfo();		// 自己的信息
	if (data->_from_uid == info->_uid) {
		ChatItemBase* base = new ChatItemBase(MessageRole::Self);
		base->setName(info->_name);
		base->setIcon((QPixmap)info->_icon);
		QWidget* bubble = new TextBubble(MessageRole::Self, data->_msg_content);
		base->setBubble(bubble);
		ui->chat_data_list->appendChatItem(base);
	}
	else {
		auto info = UserMgr::GetInstance()->getFriend(data->_from_uid);
		if (info == nullptr)return;
		ChatItemBase* base = new ChatItemBase(MessageRole::Other);
		base->setName(info->_name);
		base->setIcon((QPixmap)info->_icon);
		QWidget* bubble = new TextBubble(MessageRole::Other, data->_msg_content);
		base->setBubble(bubble);
		ui->chat_data_list->appendChatItem(base);
	}
}

void ChatPage::on_send_btn_clicked()
{
	auto fi = UserMgr::GetInstance()->getFriend(_user_info->_uid);
	MessageEdit* pTextEdit = ui->input_edit;
	MessageRole role = MessageRole::Self;
	QString userName = UserMgr::GetInstance()->getUserInfo()->_name;
	QString userIcon = ":/res/head_1.jpg";
	const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
	if (msgList.isEmpty())return;								// 为空直接返回

	QJsonArray textArry;
	QJsonObject textObj;
	int textSize = 0;
	for (int i = 0; i < msgList.size(); ++i)
	{
		QString type = msgList[i].msgFlag;
		ChatItemBase* pChatItem = new ChatItemBase(role);
		pChatItem->setName(userName);
		pChatItem->setIcon(QPixmap(userIcon));
		QWidget* pBubble = nullptr;

		if (type == "text") {
			pBubble = new TextBubble(role, msgList[i].content);
			QUuid uuid = QUuid::createUuid();

			if (textSize + msgList[i].content.size()> 1024) {

				textObj["uid"] = UserMgr::GetInstance()->getUid();
				textObj["touid"] = fi->_uid;
				textObj["text_array"] = textArry;
				QJsonDocument doc(textObj);
                QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
				TcpMgr::GetInstance()->sig_send_data(ID_TEXT_CHAT_MSG_REQ, jsonData);
				textArry = QJsonArray();
				textSize = 0;
			}

			textSize += msgList[i].content.size();

			QJsonObject tempObj;
			QByteArray utf8Message = msgList[i].content.toUtf8();
			tempObj["content"] = QString::fromUtf8(utf8Message);
			tempObj["msgid"] = uuid.toString();
			textArry.append(tempObj);
		}
		else if (type == "image")
			pBubble = new PictureBubble(QPixmap(msgList[i].content), role);
		else if (type == "file") {}
		if (pBubble != nullptr)
		{
			pChatItem->setBubble(pBubble);
			ui->chat_data_list->appendChatItem(pChatItem);
		}
		auto data = std::make_shared<TextChatData>("text", msgList[i].content, UserMgr::GetInstance()->getUid(), _user_info->_uid);
		fi->_chat_msgs.push_back(data);// 自己本地存一下


	}
	ui->input_edit->clear();
	//    ui->input_edit->clearVector();


	textObj["uid"] = UserMgr::GetInstance()->getUid();
	textObj["touid"] = fi->_uid;
	textObj["text_array"] = textArry;
	QJsonDocument doc(textObj);
	QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
	TcpMgr::GetInstance()->sig_send_data(ID_TEXT_CHAT_MSG_REQ, jsonData);
}

