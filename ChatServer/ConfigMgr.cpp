#include "ConfigMgr.h"
#include<iostream>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/ini_parser.hpp>



std::string ConfigMgr::getValue(std::string key1, std::string key2)
{
	return _c_msg[key1][key2];
}
ConfigMgr::ConfigMgr(std::string cPath)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(cPath, pt);

	for (auto& iter : pt) {
		_c_msg[iter.first] = iter.second;
	}

	for (auto& iter : _c_msg) {
		std::cout << "[" << iter.first << "]" << std::endl;

		for (auto& key_value : iter.second._key_value) {
			std::cout << key_value.first << " = " << key_value.second << std::endl;
		}
		std::cout << std::endl;
	}

}
