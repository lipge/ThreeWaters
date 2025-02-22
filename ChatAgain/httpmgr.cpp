#include "httpmgr.h"

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}
HttpMgr::~HttpMgr()
{
    qDebug() << "HttpMgr Destruct";
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request_POST(url);
    // 设置POST请求格式
    request_POST.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request_POST.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    auto self = shared_from_this();
    // 一行代码实现POST请求：post方法实现发送，返回值接收回包
    QNetworkReply* reply = _manager.post(request_POST, data);

    QObject::connect(reply, &QNetworkReply::finished, [self,reply,req_id,mod](){
        // 错误处理
        if(reply->error() != QNetworkReply::NoError){       // HTTP POST请求失败（有可能是发送失败有可能是其他原因）
            qDebug() << reply->errorString();
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK, mod);
            qDebug()<<"ERR_NETWORK";
            reply->deleteLater();
            return;
        }
        // 请求成功
        QString res = reply->readAll();
        // 发送信号
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}


// http请求完成逻辑
void HttpMgr::slot_http_finish(ReqId req_id, QString res, ErrorCodes err, Modules mod)
{
    qDebug() <<"Http Finish. Mod: "<<mod;
    // 注册
    if(mod == Modules::REGISTERMOD){
        emit sig_reg_mod_finish(req_id,res,err);
    }
    // 重置密码
    if(mod == Modules::RESETMOD){
        emit sig_reset_mod_finish(req_id, res, err);
    }
    // 登录
    if(mod == Modules::LOGINMOD){
        emit sig_login_mod_finish(req_id, res, err);
    }
}
