#ifndef MESSAGEEDIT_H
#define MESSAGEEDIT_H

#include <QTextEdit>
#include "global.h"
class MessageEdit : public QTextEdit
{
public:
    MessageEdit(QWidget* parent = nullptr);
    const QVector<MsgInfo> getMsgList();
//    void clearVector();
protected:
    virtual void dropEvent(QDropEvent *e) override;
private:
    QVector<MsgInfo> _img_list;// 图像信息
//    QVector<MsgInfo> _text_list;// 文本信息
//    QVector<MsgInfo> _msg_list;
};

#endif // MESSAGEEDIT_H
