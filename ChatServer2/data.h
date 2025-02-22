#pragma once
#include <string>
#include <json/value.h>
#include <memory>
struct UserInfo {
	UserInfo() :name(""), pwd(""), uid(0), email(""), nick(""), sex(0), icon("") {}
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
	std::string nick;
	int sex;
	std::string icon;
};

struct ApplyInfo {
	ApplyInfo(int uid, std::string name, std::string desc,
		std::string icon, std::string nick, int sex, int status)
		:_uid(uid), _name(name), _desc(desc),
		_icon(icon), _nick(nick), _sex(sex), _status(status) {
	}
	ApplyInfo() {};
	int _uid;
	std::string _name;
	std::string _desc;
	std::string _icon;
	std::string _nick;
	int _sex;
	int _status;
};

void jsonToinfo(Json::Value& src, std::shared_ptr<UserInfo> dst);

void infoTojson(std::shared_ptr<UserInfo> src, Json::Value& dst);