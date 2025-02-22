#include "MsgNode.h"
#include "const.h"
#include <string>
MsgNode::MsgNode(unsigned short msgid, unsigned short len,const char* data)
{
	_data = new char[len + HEAD_TOTAL_LEN + 1];
	memcpy(_data, &msgid, HEAD_ID_LEN);
	memcpy(_data + HEAD_ID_LEN, &len, HEAD_DATA_LEN);
	memcpy(_data + HEAD_TOTAL_LEN, data, len);

	_len = len + HEAD_TOTAL_LEN;
	_msgid = msgid;
}

MsgNode::MsgNode(unsigned short msgid, unsigned short len)
{
	_data = new char[len + 1]; 
	_data[len] = '\0';
	_msgid = msgid;
	_len = len;
}

MsgNode::~MsgNode()
{
	delete[]_data;
	_data = nullptr;
}

