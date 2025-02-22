/********************************************************************************
** Form generated from reading UI file 'chatview.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATVIEW_H
#define UI_CHATVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatView
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *chat_area;
    QWidget *chat_wid;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;

    void setupUi(QWidget *ChatView)
    {
        if (ChatView->objectName().isEmpty())
            ChatView->setObjectName("ChatView");
        ChatView->resize(606, 534);
        verticalLayout = new QVBoxLayout(ChatView);
        verticalLayout->setObjectName("verticalLayout");
        chat_area = new QScrollArea(ChatView);
        chat_area->setObjectName("chat_area");
        chat_area->setWidgetResizable(true);
        chat_wid = new QWidget();
        chat_wid->setObjectName("chat_wid");
        chat_wid->setGeometry(QRect(0, 0, 586, 514));
        verticalLayout_2 = new QVBoxLayout(chat_wid);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 25, 0);
        widget = new QWidget(chat_wid);
        widget->setObjectName("widget");

        verticalLayout_2->addWidget(widget);

        verticalLayout_2->setStretch(0, 10000);
        chat_area->setWidget(chat_wid);

        verticalLayout->addWidget(chat_area);


        retranslateUi(ChatView);

        QMetaObject::connectSlotsByName(ChatView);
    } // setupUi

    void retranslateUi(QWidget *ChatView)
    {
        ChatView->setWindowTitle(QCoreApplication::translate("ChatView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatView: public Ui_ChatView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATVIEW_H
