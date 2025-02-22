#include "chatuserwid.h"
#include "ui_chatuserwid.h"

ChatUserWid::ChatUserWid(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}
bool isChineseCharacter(const QChar& ch) {
    // 判断字符是否在基本汉字范围内
    return (ch.unicode() >= 0x4e00 && ch.unicode() <= 0x9fa5) ||
           (ch.unicode() >= 0x3400 && ch.unicode() <= 0x4dbf);
}

QString checkChineseCharacters(const QString& text, int maxLength) {
    float len=0;
    int i=0;
    for (const QChar& ch : text) {
        if (isChineseCharacter(ch)) len+=2;
        else len+=0.9;
        if(len >= float(maxLength)){
            return text.left(i)+"...";
        }
        i++;
    }
    return text;
}

void ChatUserWid::setChatListItemInfo(std::shared_ptr<FriendInfo> info)
{
    _friend_info = info;
    QPixmap headshot(_friend_info->_icon);
    ui->icon_lab->setPixmap(headshot.scaled(ui->icon_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lab->setScaledContents(true);  // 联系人头像
    ui->user_name_lab->setText(_friend_info->_name);      // 联系人昵称

    int maxLength = 15;
    QString truncated = checkChineseCharacters(_friend_info->_last_msg, maxLength);
    ui->user_chat_lab->setText(truncated);
}

std::shared_ptr<FriendInfo> ChatUserWid::getInfo()
{
    return _friend_info;
}

//void ChatUserWid::SetInfo(QString name, QString head, QString msg)
//{
//    QPixmap headshot(head);
//    ui->icon_lab->setPixmap(headshot.scaled(ui->icon_lab->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    ui->icon_lab->setScaledContents(true);  // 联系人头像
//    ui->user_name_lab->setText(name);      // 联系人昵称
//
//    int maxLength = 15;
//    QString truncated = checkChineseCharacters(msg, maxLength);
//    ui->user_chat_lab->setText(truncated);
//}




