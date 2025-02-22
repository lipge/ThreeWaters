#ifndef TCPMGR_H
#define TCPMGR_H
#include <QTcpSocket>
#include <QObject>
#include <functional>
#include "Singleton.h"
#include "userdata.h"

class TcpMgr:public QObject,public Singleton<TcpMgr>,public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
    friend class Singleton<TcpMgr>;

private:
    TcpMgr();
    QTcpSocket _sock;
    QString _host;
    quint16 _port;
    bool _recv_pending;     // 等待接收 没接收全
    quint16 _msg_id;
    quint16 _msg_len;
    QByteArray _buffer;
    QMap<ReqId, std::function<void(ReqId, int len, QByteArray data)>> _handlers;
    void initHandlers();
    void handleMsg(ReqId id,int len,QByteArray data);
public:
    ~TcpMgr(){};
public slots:
    void slot_tcp_connect(ServerInfo si);
    void slot_send_data(ReqId reqid,QByteArray data);
signals:
    void sig_con_success(bool);
    void sig_send_data(ReqId reqid,QByteArray data);
    void sig_switch_chatdlg();
    void sig_login_failed(int);
    // 新的好友申请
    void sig_friend_apply(std::shared_ptr<ApplyInfo>);
    void sig_user_search(std::shared_ptr<SearchInfo>);      // 用户点击搜索框中的添加好友条目，向服务器发送请求，查找信息

    void sig_updateContactsList(std::shared_ptr<AuthInfo>);

    // 收到文本消息发送的信号
    void sig_text_chat_msg(std::shared_ptr<TextChatMsg>);
};



#endif // TCPMGR_H
