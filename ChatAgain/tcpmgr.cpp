#include "tcpmgr.h"
#include <QJsonDocument>
#include "usermgr.h"

// TCPMgr的初始化发生很早，当登录界面连接信号时就会初始化
// HttpPOST处理完成且没有错误，可以进行TCP连接时，由LoginDlg发送sig_tcp_connect信号，再回到mgr里执行connectToHost函数
TcpMgr::TcpMgr()
	:_host(""), _port(0), _recv_pending(false), _msg_id(0), _msg_len(0)
{
	// TCP连接完成自动发送信号，执行回调向执行界面跳转逻辑发送信号
	QObject::connect(&_sock, &QTcpSocket::connected, [this]() {
		qDebug() << "TCP Connect Success";
		emit sig_con_success(true);
		});

	// tcp缓冲区有消息可读信号，读取到stream
	QObject::connect(&_sock, &QTcpSocket::readyRead, [this]() {

		_buffer.append(_sock.readAll());

		QDataStream stream(&_buffer, QIODevice::ReadOnly);
		stream.setByteOrder(QDataStream::LittleEndian);
		stream.setVersion(QDataStream::Qt_6_8);
		forever{
			// 无需等待
			if (!_recv_pending) {
				if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
					return; // 数据不够，等待更多数据
				}
				// stream中的数据写入到_msg_id msg_len
				stream >> _msg_id >> _msg_len;
				qDebug() << "Tcp Response Msgid:" << _msg_id << " Msglen: " << _msg_len;

				_buffer.remove(0,sizeof(quint16) * 2);
			}
			if (_buffer.size() < _msg_len) {
				_recv_pending = true;
				return;
			}

            _recv_pending = false;
            // 读取消息体
            QByteArray messageBody = _buffer.mid(0, _msg_len);
            qDebug() << "Receive body msg is " << (QString)messageBody ;
			_buffer.remove(0,_msg_len);
            handleMsg(ReqId(_msg_id),_msg_len,messageBody);
		}

		});

	// 捕获到TCP连接失败 发失败信号false
	QObject::connect(&_sock, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
		[this](QAbstractSocket::SocketError socketError) {
			switch (socketError) {
			case QTcpSocket::ConnectionRefusedError:
				qDebug() << "TCP Connection Refused!";
				break;
			case QTcpSocket::RemoteHostClosedError:
				qDebug() << "TCP Remote Host Closed Connection!";
				break;
			case QTcpSocket::HostNotFoundError:
				qDebug() << "TCP Host Not Found!";
				break;
			case QTcpSocket::SocketTimeoutError:
				qDebug() << "TCP Connection Timeout!";
				break;
			case QTcpSocket::NetworkError:
				qDebug() << "TCP Network Error!";
				break;
			default:
				qDebug() << "TCP Other Error!";
				break;
			}
            emit sig_con_success(false);
        });

	QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);

	initHandlers();
}

// 开始连接
void TcpMgr::slot_tcp_connect(ServerInfo si)
{
	_host = si.Host;
	_port = static_cast<quint16>(si.Port.toInt());
	_sock.connectToHost(_host, _port);                   // 成功会自动发QTcpSocket::connected信号；失败会发QTcpSocket::errorOccurred
}
// 发送消息
void TcpMgr::slot_send_data(ReqId reqid, QByteArray data)
{
    qDebug()<<"Tcp Send";
	uint16_t id = reqid;
	uint16_t len = data.size();
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::LittleEndian);// 使用小端序
	out << id << len;
	block.append(data);
	_sock.write(block);
}

// 初始化回调函数
void TcpMgr::initHandlers()
{
	_handlers.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data) {
		Q_UNUSED(len);

		QJsonParseError error;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
		QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")){
            qDebug() << "json解析失败";
            return;
        }
        if(jsonObj["error"].toInt() != ErrorCodes::SUCCESS){
            qDebug() << "登录失败";
            return;
        }

        // 成功
        auto info = std::make_shared<UserInfo>(jsonObj["uid"].toInt()
                                               ,jsonObj["name"].toString()
                                               ,jsonObj["nick"].toString()
                                               ,jsonObj["icon"].toString()// icon随机设置
                                               ,jsonObj["sex"].toInt());
        UserMgr::GetInstance()->setUserInfo(info);
        if(jsonObj.contains("apply_list")){
            UserMgr::GetInstance()->appendApplyList(jsonObj["apply_list"].toArray());
        }
		if (jsonObj.contains("friend_list")) {
			UserMgr::GetInstance()->appendFriendList(jsonObj["friend_list"].toArray());
		}
		qDebug() << "登录成功，即将跳转聊天界面";
        qDebug() << "Uid: " << jsonObj["uid"].toInt();
		emit sig_switch_chatdlg();
		});

    // 搜索好友回包
	_handlers.insert(ReqId::ID_SEARCH_USER_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
		QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")){
            qDebug() << "json解析失败";
            emit sig_user_search(nullptr);
            return;
        }
        if(jsonObj["error"].toInt() != ErrorCodes::SUCCESS){
            qDebug() << "搜索失败";
            emit sig_user_search(nullptr);
            return;
        }
        auto search_info = std::make_shared<SearchInfo>(jsonObj["uid"].toInt(),
			jsonObj["name"].toString(),
			jsonObj["nick"].toString(),
			jsonObj["desc"].toString(),
			jsonObj["sex"].toInt(),
			jsonObj["icon"].toString());

		emit sig_user_search(search_info);
		});


    // 发送添加好友申请回包
    _handlers.insert(ReqId::ID_ADD_FRIEND_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")){
            qDebug() << "json解析失败";
            return;
        }
        if(jsonObj["error"].toInt() != ErrorCodes::SUCCESS){
            qDebug() << "发送添加好用请求失败";
            return;
        }
        qDebug() << "发送添加好友请求成功";
    });


    // 有新的好友申请，服务器单方面发给你
	_handlers.insert(ReqId::ID_NOTIFY_ADD_FRIEND_REQ, [this](ReqId id, int len, QByteArray data) {
		Q_UNUSED(len);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
		QJsonObject jsonObj = jsonDoc.object();

		if (jsonDoc.isNull() || !jsonObj.contains("error")) {
			qDebug() << "json解析失败";
			return;
		}
		if (jsonObj["error"].toInt() != ErrorCodes::SUCCESS) {
			qDebug() << "好友申请回包请求失败";
			return;
        }
        auto uid = jsonObj["uid"].toInt();
		auto name = jsonObj["applyname"].toString();
		auto desc = jsonObj["desc"].toString();
		auto icon = jsonObj["icon"].toString();
		auto sex = jsonObj["sex"].toInt();
        auto apply_info = std::make_shared<ApplyInfo>(uid, name, desc, icon, "", sex, 1);
        emit sig_friend_apply(apply_info);
		qDebug() << "有新的好友申请";
		});

    // 你同意了对端好友申请，这是服务器给你回包（你是认证信息的发出者）
    _handlers.insert(ReqId::ID_AUTH_FRIEND_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")) {
            qDebug() << "json解析失败";
            return;
        }
        if (jsonObj["error"].toInt() != ErrorCodes::SUCCESS) {
            qDebug() << "同意好友申请失败";
            return;
        }
        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto info = std::make_shared<AuthInfo>(uid, sex, name, nick, icon);
        emit sig_updateContactsList(info);
        qDebug()<<"认证好友成功";
    });

    // 对端同意了你的好友申请，这是服务器单方面的发给你，请求对界面进行更新
    _handlers.insert(ReqId::ID_NOTIFY_AUTH_FRIEND_REQ, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")) {
            qDebug() << "json解析失败";
            return;
        }
        if (jsonObj["error"].toInt() != ErrorCodes::SUCCESS) {
            qDebug() << "对端同意认证回包失败";
            return;
        }
        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto info = std::make_shared<AuthInfo>(uid, sex, name, nick, icon);
        emit sig_updateContactsList(info);
        qDebug()<<"对方同意认证";
    });

    // 发送信息回包
    _handlers.insert(ReqId::ID_TEXT_CHAT_MSG_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")) {
            qDebug() << "json解析失败";
            return;
        }
        if (jsonObj["error"].toInt() != ErrorCodes::SUCCESS) {
            qDebug() << "发送消息失败";
            return;
        }
        qDebug() << "发送消息成功";
        });

    // 收到消息
    _handlers.insert(ReqId::ID_NOTIFY_TEXT_CHAT_MSG_REQ, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonDoc.isNull() || !jsonObj.contains("error")) {
            qDebug() << "json解析失败";
            return;
        }
        if (jsonObj["error"].toInt() != ErrorCodes::SUCCESS) {
            qDebug() << "收到消息失败";
            return;
        }
        auto text_msg = std::make_shared<TextChatMsg>(jsonObj["uid"].toInt()
            , jsonObj["touid"].toInt()
            , jsonObj["text_array"].toArray());
        emit sig_text_chat_msg(text_msg);
        qDebug() << "收到消息";
        });
	
}

// 进来再判断由哪个回调函数处理
void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
	auto find_iter = _handlers.find(id);
	if (find_iter == _handlers.end()) {
		qDebug() << "Handler not Exit";
		return;
	}
	find_iter.value()(id, len, data);
}
