#ifndef CHATITEMBASE_H
#define CHATITEMBASE_H

#include <QWidget>
#include "global.h"
#include <QLabel>

class Bubble;

class ChatItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemBase(MessageRole role, QWidget *parent = nullptr);
    void setIcon(const QPixmap &icon);
    void setName(const QString &name);
    void setBubble(QWidget* w);
private:
    MessageRole _role;
    QWidget* _bubble;
    QLabel* _name_lab;
    QLabel* _icon_lab;


signals:


};

#endif // CHATITEMBASE_H
