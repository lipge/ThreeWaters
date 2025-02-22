#include "data.h"

void jsonToinfo(Json::Value& src, std::shared_ptr<UserInfo> dst) {
	dst->uid = src["uid"].asInt();
	dst->email = src["email"].asString();
	dst->name = src["name"].asString();
	dst->nick = src["nick"].asString();
//	dst->desc = src["desc"].asString();
	dst->sex = src["sex"].asInt();
	dst->icon = src["icon"].asString();
	dst->pwd = src["pwd"].asString();//8
}

void infoTojson(std::shared_ptr<UserInfo> src, Json::Value& dst) {
	dst["uid"] = src->uid;
	dst["pwd"] = src->pwd;
	dst["name"] = src->name;
	dst["email"] = src->email;
	dst["nick"] = src->nick;
//	dst["desc"] = src->desc;
	dst["sex"] = src->sex;
	dst["icon"] = src->icon;//8
}
