/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chatpage.h>
#include <clickbtn.h>
#include <contactslist.h>
#include <friendinfopage.h>
#include <newfriendpage.h>
#include <statewidget.h>
#include "chatuserlist.h"
#include "customizeedit.h"
#include "searchlist.h"

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar;
    QVBoxLayout *verticalLayout;
    QLabel *headshot_sidebar;
    QVBoxLayout *verticalLayout_3;
    StateWidget *chat_sidebar;
    StateWidget *contracts_sidebar;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_wid;
    QVBoxLayout *verticalLayout_2;
    QWidget *search_widget;
    QHBoxLayout *horizontalLayout_2;
    CustomizeEdit *search_edit;
    QSpacerItem *horizontalSpacer_5;
    ClickBtn *add_btn;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    ContactsList *con_user_list;
    ChatUserList *chat_user_list;
    SearchList *search_list;
    QStackedWidget *stackedWidget;
    QWidget *default_page;
    ChatPage *chat_page;
    NewFriendPage *newfriend_page;
    FriendInfoPage *friendinfo_page;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(789, 528);
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        side_bar = new QWidget(ChatDialog);
        side_bar->setObjectName("side_bar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(side_bar->sizePolicy().hasHeightForWidth());
        side_bar->setSizePolicy(sizePolicy);
        side_bar->setMinimumSize(QSize(55, 0));
        side_bar->setMaximumSize(QSize(55, 16777215));
        QFont font;
        font.setWeight(QFont::Light);
        side_bar->setFont(font);
        side_bar->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        side_bar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        side_bar->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(side_bar);
        verticalLayout->setSpacing(30);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 40, 0, 0);
        headshot_sidebar = new QLabel(side_bar);
        headshot_sidebar->setObjectName("headshot_sidebar");
        headshot_sidebar->setMinimumSize(QSize(30, 30));
        headshot_sidebar->setMaximumSize(QSize(30, 30));
        headshot_sidebar->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        headshot_sidebar->setPixmap(QPixmap(QString::fromUtf8(":/res/head_5.jpg")));
        headshot_sidebar->setScaledContents(true);
        headshot_sidebar->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headshot_sidebar, 0, Qt::AlignmentFlag::AlignHCenter);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, -1, -1, 0);
        chat_sidebar = new StateWidget(side_bar);
        chat_sidebar->setObjectName("chat_sidebar");
        chat_sidebar->setMinimumSize(QSize(20, 20));
        chat_sidebar->setMaximumSize(QSize(20, 20));

        verticalLayout_3->addWidget(chat_sidebar, 0, Qt::AlignmentFlag::AlignHCenter);

        contracts_sidebar = new StateWidget(side_bar);
        contracts_sidebar->setObjectName("contracts_sidebar");
        contracts_sidebar->setMinimumSize(QSize(25, 25));
        contracts_sidebar->setMaximumSize(QSize(25, 25));

        verticalLayout_3->addWidget(contracts_sidebar, 0, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar);

        chat_user_wid = new QWidget(ChatDialog);
        chat_user_wid->setObjectName("chat_user_wid");
        chat_user_wid->setMaximumSize(QSize(230, 16777215));
        verticalLayout_2 = new QVBoxLayout(chat_user_wid);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        search_widget = new QWidget(chat_user_wid);
        search_widget->setObjectName("search_widget");
        search_widget->setMinimumSize(QSize(0, 50));
        search_widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(search_widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        search_edit = new CustomizeEdit(search_widget);
        search_edit->setObjectName("search_edit");
        search_edit->setMinimumSize(QSize(0, 25));
        search_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(search_edit);

        horizontalSpacer_5 = new QSpacerItem(10, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        add_btn = new ClickBtn(search_widget);
        add_btn->setObjectName("add_btn");
        add_btn->setMaximumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(add_btn);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        line = new QFrame(search_widget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);


        verticalLayout_2->addWidget(search_widget);

        con_user_list = new ContactsList(chat_user_wid);
        con_user_list->setObjectName("con_user_list");
        con_user_list->setStyleSheet(QString::fromUtf8("#con_user_list {\n"
"    background-color: rgb(234,232,231);\n"
"    border: none;\n"
"}\n"
"\n"
""));

        verticalLayout_2->addWidget(con_user_list);

        chat_user_list = new ChatUserList(chat_user_wid);
        chat_user_list->setObjectName("chat_user_list");
        chat_user_list->setStyleSheet(QString::fromUtf8("#con_user_list {\n"
"    background-color: rgb(234,232,231);\n"
"    border: none;\n"
"}\n"
"\n"
""));

        verticalLayout_2->addWidget(chat_user_list);

        search_list = new SearchList(chat_user_wid);
        search_list->setObjectName("search_list");
        search_list->setStyleSheet(QString::fromUtf8("#search_list {\n"
"    background-color: rgb(247,247,248);\n"
"    border: none;\n"
"}\n"
"#search_list::item:selected {\n"
"    background-color: #d3d7d4;\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"#search_list::item:hover {\n"
"    background-color: rgb(206,207,208);\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"#search_list::focus {\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"#invalid_item {\n"
"    background-color: #eaeaea;\n"
"    border: none;\n"
"}\n"
""));

        verticalLayout_2->addWidget(search_list);


        horizontalLayout->addWidget(chat_user_wid);

        stackedWidget = new QStackedWidget(ChatDialog);
        stackedWidget->setObjectName("stackedWidget");
        default_page = new QWidget();
        default_page->setObjectName("default_page");
        stackedWidget->addWidget(default_page);
        chat_page = new ChatPage();
        chat_page->setObjectName("chat_page");
        stackedWidget->addWidget(chat_page);
        newfriend_page = new NewFriendPage();
        newfriend_page->setObjectName("newfriend_page");
        stackedWidget->addWidget(newfriend_page);
        friendinfo_page = new FriendInfoPage();
        friendinfo_page->setObjectName("friendinfo_page");
        stackedWidget->addWidget(friendinfo_page);

        horizontalLayout->addWidget(stackedWidget);

        QWidget::setTabOrder(chat_user_list, search_edit);
        QWidget::setTabOrder(search_edit, add_btn);

        retranslateUi(ChatDialog);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        headshot_sidebar->setText(QString());
        add_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
