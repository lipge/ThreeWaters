#pragma once
#include"const.h"
class MsgNode
{
public:
	MsgNode(unsigned short msgid, unsigned short len, const char* data);
	MsgNode(unsigned short msgid, unsigned short len);
	~MsgNode();

	char* _data;
	unsigned short _len;
	unsigned short _msgid;
};

