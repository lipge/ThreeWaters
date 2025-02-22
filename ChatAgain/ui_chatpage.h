/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chatview.h>
#include <clickbtn.h>
#include <clickedlabel.h>
#include <messageedit.h>

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *chat_data_wid;
    QVBoxLayout *verticalLayout_3;
    QWidget *contact_wid;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QLabel *contact_lab;
    ChatView *chat_data_list;
    QWidget *tool_wid;
    QHBoxLayout *horizontalLayout_3;
    ClickedLabel *emoji_lab;
    QSpacerItem *horizontalSpacer_2;
    ClickedLabel *file_lab;
    QSpacerItem *horizontalSpacer_3;
    QLabel *history_lab;
    QSpacerItem *horizontalSpacer;
    QLabel *video_lab;
    QWidget *input_wid;
    QVBoxLayout *verticalLayout_4;
    MessageEdit *input_edit;
    QWidget *recv_wid;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    ClickBtn *recv_btn;
    QSpacerItem *horizontalSpacer_5;
    ClickBtn *send_btn;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName("ChatPage");
        ChatPage->resize(600, 628);
        horizontalLayout = new QHBoxLayout(ChatPage);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        chat_data_wid = new QWidget(ChatPage);
        chat_data_wid->setObjectName("chat_data_wid");
        chat_data_wid->setMaximumSize(QSize(1080, 16777215));
        verticalLayout_3 = new QVBoxLayout(chat_data_wid);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        contact_wid = new QWidget(chat_data_wid);
        contact_wid->setObjectName("contact_wid");
        contact_wid->setMinimumSize(QSize(0, 50));
        contact_wid->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_5 = new QHBoxLayout(contact_wid);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        contact_lab = new QLabel(contact_wid);
        contact_lab->setObjectName("contact_lab");
        contact_lab->setMinimumSize(QSize(0, 40));
        contact_lab->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setPointSize(13);
        font.setWeight(QFont::Medium);
        contact_lab->setFont(font);

        horizontalLayout_5->addWidget(contact_lab, 0, Qt::AlignmentFlag::AlignVCenter);


        verticalLayout_3->addWidget(contact_wid);

        chat_data_list = new ChatView(chat_data_wid);
        chat_data_list->setObjectName("chat_data_list");

        verticalLayout_3->addWidget(chat_data_list);

        tool_wid = new QWidget(chat_data_wid);
        tool_wid->setObjectName("tool_wid");
        tool_wid->setMinimumSize(QSize(0, 30));
        tool_wid->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(tool_wid);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, 0, 0, 0);
        emoji_lab = new ClickedLabel(tool_wid);
        emoji_lab->setObjectName("emoji_lab");
        emoji_lab->setMinimumSize(QSize(20, 20));
        emoji_lab->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setWeight(QFont::DemiBold);
        emoji_lab->setFont(font1);

        horizontalLayout_3->addWidget(emoji_lab);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        file_lab = new ClickedLabel(tool_wid);
        file_lab->setObjectName("file_lab");
        file_lab->setMinimumSize(QSize(30, 30));
        file_lab->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(file_lab);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        history_lab = new QLabel(tool_wid);
        history_lab->setObjectName("history_lab");
        history_lab->setMinimumSize(QSize(30, 30));
        history_lab->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(history_lab);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        video_lab = new QLabel(tool_wid);
        video_lab->setObjectName("video_lab");
        video_lab->setMinimumSize(QSize(30, 30));
        video_lab->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(video_lab);


        verticalLayout_3->addWidget(tool_wid);

        input_wid = new QWidget(chat_data_wid);
        input_wid->setObjectName("input_wid");
        input_wid->setMinimumSize(QSize(0, 100));
        input_wid->setMaximumSize(QSize(16777215, 100));
        input_wid->setSizeIncrement(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(input_wid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        input_edit = new MessageEdit(input_wid);
        input_edit->setObjectName("input_edit");
        input_edit->setLineWidth(0);

        verticalLayout_4->addWidget(input_edit);


        verticalLayout_3->addWidget(input_wid);

        recv_wid = new QWidget(chat_data_wid);
        recv_wid->setObjectName("recv_wid");
        recv_wid->setMinimumSize(QSize(0, 60));
        recv_wid->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(recv_wid);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        recv_btn = new ClickBtn(recv_wid);
        recv_btn->setObjectName("recv_btn");
        recv_btn->setMinimumSize(QSize(100, 30));
        recv_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(recv_btn);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        send_btn = new ClickBtn(recv_wid);
        send_btn->setObjectName("send_btn");
        send_btn->setMinimumSize(QSize(100, 30));
        send_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(send_btn);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_3->addWidget(recv_wid);


        horizontalLayout->addWidget(chat_data_wid);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        contact_lab->setText(QCoreApplication::translate("ChatPage", "\350\201\224\347\263\273\344\272\272", nullptr));
        emoji_lab->setText(QString());
        file_lab->setText(QString());
        history_lab->setText(QString());
        video_lab->setText(QString());
        recv_btn->setText(QCoreApplication::translate("ChatPage", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatPage", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
