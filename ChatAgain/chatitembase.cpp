#include "chatitembase.h"
#include <QSpacerItem>
#include <QGridLayout>
ChatItemBase::ChatItemBase(MessageRole role, QWidget *parent)
    : QWidget{parent}
    ,_role(role)
{
    _name_lab = new QLabel;
    _name_lab->setObjectName("chat_user_name");
    QFont font = QFont("Microsoft YaHei");
    font.setPointSize(9);
    _name_lab->setFont(font);
    _name_lab->setFixedHeight(20);
    _icon_lab    = new QLabel();
    _icon_lab->setScaledContents(true);
    _icon_lab->setFixedSize(42, 42);
    _bubble       = new QWidget();
    QGridLayout *pGLayout = new QGridLayout();
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setContentsMargins(3,3,3,3);
    QSpacerItem*pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    if(_role == MessageRole::Self)
    {
        _name_lab->setContentsMargins(0,0,8,0);
        _name_lab->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(_name_lab, 0,1, 1,1);
        pGLayout->addWidget(_icon_lab, 0, 2, 2,1, Qt::AlignTop);
        pGLayout->addItem(pSpacer, 1, 0, 1, 1);
        pGLayout->addWidget(_bubble, 1,1, 1,1);
        pGLayout->setColumnStretch(0, 2);
        pGLayout->setColumnStretch(1, 3);
    }else{
        _name_lab->setContentsMargins(8,0,0,0);
        _name_lab->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(_icon_lab, 0, 0, 2,1, Qt::AlignTop);
        pGLayout->addWidget(_name_lab, 0,1, 1,1);
        pGLayout->addWidget(_bubble, 1,1, 1,1);
        pGLayout->addItem(pSpacer, 2, 2, 1, 1);
        pGLayout->setColumnStretch(1, 3);
        pGLayout->setColumnStretch(2, 2);
    }
    this->setLayout(pGLayout);
}

void ChatItemBase::setIcon(const QPixmap &icon)
{
    _icon_lab->setPixmap(icon);
}

void ChatItemBase::setName(const QString &name)
{
    _name_lab->setText(name);
}

void ChatItemBase::setBubble(QWidget *w)
{
    auto lt = this->layout();
    lt->replaceWidget(_bubble,w);
    delete _bubble;
    _bubble = w;
}
