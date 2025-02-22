#pragma once
#include"Singleton.h"
#include<string>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/ini_parser.hpp>
#include<iostream>
#include<unordered_map>

class Value:public  boost::property_tree::ptree
{
public:

	std::string operator[](const std::string& key) {
		return _key_value[key];
	}
	boost::property_tree::ptree& operator=(boost::property_tree::ptree& msg) {
		for (auto& iter : msg) {
			_key_value[iter.first] = iter.second.get_value<std::string>();
		}
		return *this;
	}
	std::unordered_map<std::string, std::string> _key_value;

};

class ConfigMgr
{
public:
	static ConfigMgr& GetInstance() {
		static ConfigMgr instance;
		return instance;
	}
	Value operator[](const std::string& key) {
		return _c_msg[key];
	}
	std::string getValue(std::string key1, std::string key2);
private:
	ConfigMgr(std::string cPath = "config.ini");
	std::unordered_map<std::string, Value> _c_msg;
};

