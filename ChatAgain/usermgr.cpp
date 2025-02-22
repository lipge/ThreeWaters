#include "usermgr.h"

UserMgr::~UserMgr()
{

}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

std::shared_ptr<UserInfo> UserMgr::getUserInfo()
{
    return _userinfo;
}

int UserMgr::getUid()
{
    return _userinfo->_uid;
}

void UserMgr::setUserInfo(std::shared_ptr<UserInfo> info)
{
    _userinfo = info;
}

bool UserMgr::alreadyApply(int uid)
{
    return _applications.count(uid);
}

bool UserMgr::alreadyBeFriend(int uid)
{
    return _friends.count(uid);
}
bool UserMgr::alreadyBeFriend(QString name)
{
    for(auto& iter : _friends){
        if(iter.second->_name == name || iter.second->_nick == name){
            return true;
        }
    }
    return false;
}
void UserMgr::addFrined(std::shared_ptr<AuthInfo> auth_info)
{
    if (alreadyBeFriend(auth_info->_uid)) return;
    _friends[auth_info->_uid] = std::make_shared<FriendInfo>(auth_info);
}

std::shared_ptr<FriendInfo> UserMgr::getFriend(int friend_id)
{
    return _friends[friend_id];
}
std::shared_ptr<FriendInfo> UserMgr::getFriend(QString name)
{
    for(auto& iter : _friends){
        if(iter.second->_name == name || iter.second->_nick == name){
            return _friends[iter.first];
        }
    }
    return nullptr;
}


void UserMgr::updateApplyList(std::shared_ptr<ApplyInfo> info)
{
    _applications[info->_uid] = info;
}

void UserMgr::appendApplyList(QJsonArray array)
{
    for(const QJsonValue &value : array){
        auto uid = value["uid"].toInt();
        auto name = value["name"].toString();
        auto nick = value["nick"].toString();
        auto icon = value["icon"].toString();
        auto sex = value["sex"].toInt();
        auto status = value["status"].toInt();
        auto info = std::make_shared<ApplyInfo>(uid, name, nick, icon, nick, sex, status);
        _applications[uid] = info;
    }
}

void UserMgr::appendFriendList(QJsonArray array)
{
    for(const QJsonValue &value : array){
        auto uid = value["uid"].toInt();
        auto name = value["name"].toString();
        auto nick = value["nick"].toString();
        auto icon = value["icon"].toString();
        auto sex = value["sex"].toInt();
        auto info = std::make_shared<FriendInfo>(uid, name, nick, icon, sex, "", "");
        _friends[uid] = info;
    }
}

std::unordered_map<int, std::shared_ptr<ApplyInfo>>& UserMgr::getApplicationList()
{
    return _applications;
}

std::unordered_map<int, std::shared_ptr<FriendInfo>>& UserMgr::getFriendList()
{
    return _friends;
}

void UserMgr::appendFriendMesssage(int friend_uid, std::shared_ptr<TextChatData> data)
{
    auto fi = _friends[friend_uid];
    fi->_chat_msgs.push_back(data);// 自己本地存一下
}


