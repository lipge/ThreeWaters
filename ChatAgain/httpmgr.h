#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "Singleton.h"
#include "global.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

class HttpMgr :public QObject							// 继承QObject连接信号跟槽
	, public Singleton<HttpMgr>							// 继承单例模板类，实现单例模式
	, public std::enable_shared_from_this<HttpMgr>		// 使能shared_from_this
{
	Q_OBJECT

public:
	~HttpMgr();
	// 外部发送http请求接口
	void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
	friend class Singleton<HttpMgr>;
	HttpMgr();
	QNetworkAccessManager _manager;
private slots:
	void slot_http_finish(ReqId req_id, QString s, ErrorCodes ec, Modules mod);

signals:
	void sig_http_finish(ReqId req_id, QString s, ErrorCodes ec, Modules mod);
	void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
	void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
	void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);

};

#endif // HTTPMGR_H
