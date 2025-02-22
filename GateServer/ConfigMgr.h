#pragma once
#include "const.h"
struct SectionInfo {
	SectionInfo() {}
	~SectionInfo() { _section_datas.clear(); }

	SectionInfo(const SectionInfo& src) {
		_section_datas = src._section_datas;
	}

	SectionInfo& operator=(const SectionInfo& src) {
		if (&src == this) {
			return *this;
		}
		this->_section_datas = src._section_datas;
		return *this;
	}

	std::map<std::string, std::string> _section_datas;
	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		return _section_datas[key];
	}
};

class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();

	}

	// 类本身重载了[]，返回值类型是SectionInfo
	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();		// 返回空Section
		}
		return _config_map[section];
	}

	static ConfigMgr& GetInstance() {
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}

	ConfigMgr(const ConfigMgr& src) {
		_config_map = src._config_map;
	}
	ConfigMgr& operator=(const ConfigMgr& src) {
		if (&src == this) {
			return *this;
		}

		_config_map = src._config_map;
	}


private:
	std::map<std::string, SectionInfo> _config_map;
	ConfigMgr();
	

};

