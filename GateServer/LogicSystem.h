#pragma once
#include "const.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)>HttpHandler;

class LogicSystem :
    public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    ~LogicSystem();
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);           // ����Get����
    bool HandlePost(std::string, std::shared_ptr<HttpConnection>);           // ����Get����
    void RegGet(std::string url, HttpHandler reg_handler);                      // ע�ᴦ��Get����
    void RegPost(std::string url, HttpHandler reg_handler);

private:
    LogicSystem();
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;

};

