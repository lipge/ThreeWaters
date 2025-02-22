/********************************************************************************
** Form generated from reading UI file 'newfrienditem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFRIENDITEM_H
#define UI_NEWFRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewFriendItem
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *head_lab;
    QWidget *msg_wid;
    QHBoxLayout *horizontalLayout_2;
    QWidget *friend_msg_wid;
    QVBoxLayout *verticalLayout;
    QLabel *name_lab;
    QLabel *desc_lab;
    QPushButton *add_btn;
    QFrame *line;

    void setupUi(QWidget *NewFriendItem)
    {
        if (NewFriendItem->objectName().isEmpty())
            NewFriendItem->setObjectName("NewFriendItem");
        NewFriendItem->resize(566, 83);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewFriendItem->sizePolicy().hasHeightForWidth());
        NewFriendItem->setSizePolicy(sizePolicy);
        NewFriendItem->setMinimumSize(QSize(0, 80));
        NewFriendItem->setMaximumSize(QSize(16777215, 86));
        verticalLayout_2 = new QVBoxLayout(NewFriendItem);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(90, 0, 90, 0);
        widget = new QWidget(NewFriendItem);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 80));
        widget->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 10, 0);
        head_lab = new QLabel(widget);
        head_lab->setObjectName("head_lab");
        head_lab->setMinimumSize(QSize(50, 50));
        head_lab->setMaximumSize(QSize(50, 50));

        horizontalLayout_3->addWidget(head_lab);

        msg_wid = new QWidget(widget);
        msg_wid->setObjectName("msg_wid");
        horizontalLayout_2 = new QHBoxLayout(msg_wid);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 10, 0, 10);
        friend_msg_wid = new QWidget(msg_wid);
        friend_msg_wid->setObjectName("friend_msg_wid");
        verticalLayout = new QVBoxLayout(friend_msg_wid);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        name_lab = new QLabel(friend_msg_wid);
        name_lab->setObjectName("name_lab");
        QFont font;
        font.setBold(false);
        name_lab->setFont(font);

        verticalLayout->addWidget(name_lab);

        desc_lab = new QLabel(friend_msg_wid);
        desc_lab->setObjectName("desc_lab");

        verticalLayout->addWidget(desc_lab);


        horizontalLayout_2->addWidget(friend_msg_wid);


        horizontalLayout_3->addWidget(msg_wid);

        add_btn = new QPushButton(widget);
        add_btn->setObjectName("add_btn");
        add_btn->setMinimumSize(QSize(80, 30));
        add_btn->setMaximumSize(QSize(80, 30));
        add_btn->setFlat(true);

        horizontalLayout_3->addWidget(add_btn);


        verticalLayout_2->addWidget(widget);

        line = new QFrame(NewFriendItem);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);


        retranslateUi(NewFriendItem);

        QMetaObject::connectSlotsByName(NewFriendItem);
    } // setupUi

    void retranslateUi(QWidget *NewFriendItem)
    {
        NewFriendItem->setWindowTitle(QCoreApplication::translate("NewFriendItem", "Form", nullptr));
        head_lab->setText(QCoreApplication::translate("NewFriendItem", "\345\244\264\345\203\217", nullptr));
        name_lab->setText(QCoreApplication::translate("NewFriendItem", "\346\230\265\347\247\260", nullptr));
        desc_lab->setText(QCoreApplication::translate("NewFriendItem", "\345\244\207\346\263\250\344\277\241\346\201\257", nullptr));
        add_btn->setText(QCoreApplication::translate("NewFriendItem", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewFriendItem: public Ui_NewFriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFRIENDITEM_H
