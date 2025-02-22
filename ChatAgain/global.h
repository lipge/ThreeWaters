#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include "QStyle"
#include <QByteArray>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDir>
#include <QSettings>

// 测试数据
const std::vector<QString> names = {
    "lipge",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};
const std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};

// 刷新qss
extern std::function<void(QWidget*)> repolish;
// 简单对密码加密 使用异或运算
extern std::function<QString(QString)> xorString;

enum ReqId{
    ID_GET_VARIFY_CODE = 1001,      // 获取验证码
    ID_REG_USER = 1002,             // 用户注册
    ID_RESET_PWD = 1003,
    ID_LOGIN_USER = 1004,
    ID_CHAT_LOGIN = 1005,
    ID_CHAT_LOGIN_RSP = 1006,        // 登录聊天服务器回包

    ID_SEARCH_USER_REQ = 1007, //用户搜索请求
    ID_SEARCH_USER_RSP = 1008, //搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  //添加好友申请
    ID_ADD_FRIEND_RSP = 1010, //申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知用户添加好友申请

    ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  //认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
    ID_TEXT_CHAT_MSG_REQ  = 1017,  //文本聊天信息请求
    ID_TEXT_CHAT_MSG_RSP  = 1018,  //文本聊天信息回复
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知用户文本聊天信息
};

enum Modules{
    REGISTERMOD = 0,
    RESETMOD = 1,
    LOGINMOD = 2
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,               // json解析失败
    ERR_NETWORK = 2,
};




enum TipErr{
    TIP_SUCCESS = 0,
    TIP_USER_ERR = 1,
    TIP_EMAIL_ERR = 2,
    TIP_PWD_ERR = 3,
    TIP_CONFIRM_ERR = 4,
    TIP_PWD_CONFIRM_ERR = 5,
    TIP_VARIFY_ERR = 6,
};
enum ClickLbState{
    Normal = 0,
    Selected = 1,
    PlainText = 2,
};
// enum ClickBtnState{
//     Normal = 0,
//     Selected = 1,
//     PlainText = 2,
// };
struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};
// Myself
enum LoginState{
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    PostFailed = 1003, // 本地网络错误，导致Post请求没发出去
    TCPFailed = 1003, // TCP连接错误
    PasswdErr = 1006,    //密码错误
    EmailNotMatch = 1007,  //邮箱不匹配
};

enum ChatUIMode{
    ChatMode,
    ContactMode
};

// QListWidgetItem类型
enum ListItemType{
    CHAT_USER_ITEM,     // 聊天记录
    CONTACT_USER_ITEM,  // 联系人条目
    SEARCH_USER_ITEM,   // 搜索好友条目
    ADD_USER_TIP_ITEM,  // 添加好友提示
    INVALID_ITEM,       // 不可点击
    GROUP_TIP_ITEM,     // 分组提示

    NEW_FRIEND_ITEM,    // 新的朋友条目
};

enum MessageRole{
    Self,
    Other,
};
struct MsgInfo{
    QString msgFlag;//"text,image,file"
    QString content;//表示文件和图像的url,文本信息
    QPixmap pixmap;//文件和图片的缩略图
};

extern QString gate_url_prefix;

#endif // GLOBAL_H
