#ifndef USERMGR_H
#define USERMGR_H
#include"Singleton.h"
#include <QObject>
#include <memory>
#include "userdata.h"
#include <unordered_map>
class UserMgr :public QObject, public Singleton<UserMgr>,
	public std::enable_shared_from_this<UserMgr>
{
	Q_OBJECT

public:
	friend class Singleton<UserMgr>;
	~UserMgr();

	void SetToken(QString token);

	std::shared_ptr<UserInfo> getUserInfo();
	int getUid();
	void setUserInfo(std::shared_ptr<UserInfo> info);

	bool alreadyApply(int uid);
	bool alreadyBeFriend(int uid);
	bool alreadyBeFriend(QString name);
	//    void addFrined(std::shared_ptr<AuthRsp> auth_rsp);
	void addFrined(std::shared_ptr<AuthInfo> auth_info);
	std::shared_ptr<FriendInfo> getFriend(int friend_id);
	std::shared_ptr<FriendInfo> getFriend(QString name);
	void updateApplyList(std::shared_ptr<ApplyInfo>);// 单条数据
	void appendApplyList(QJsonArray array);// 多条json数据
	void appendFriendList(QJsonArray array);// 多条json数据
	std::unordered_map<int, std::shared_ptr<ApplyInfo>>& getApplicationList();
	std::unordered_map<int, std::shared_ptr<FriendInfo>>& getFriendList();
	void appendFriendMesssage(int friend_uid, std::shared_ptr<TextChatData> data);
private:
	//UserMgr() :_name(""), _token(""), _uid() {}
	QString _name;
	QString _token;
	//int _uid;
	std::shared_ptr<UserInfo> _userinfo;
	std::unordered_map<int, std::shared_ptr<ApplyInfo>> _applications;
	std::unordered_map<int, std::shared_ptr<FriendInfo>> _friends;

};

#endif // USERMGR_H
