/********************************************************************************
** Form generated from reading UI file 'newfriendpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFRIENDPAGE_H
#define UI_NEWFRIENDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <newfriendlist.h>

QT_BEGIN_NAMESPACE

class Ui_NewFriendPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *title_wid;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *title_lab;
    QWidget *app_wid;
    QVBoxLayout *verticalLayout_2;
    NewFriendList *applications_list;

    void setupUi(QWidget *NewFriendPage)
    {
        if (NewFriendPage->objectName().isEmpty())
            NewFriendPage->setObjectName("NewFriendPage");
        NewFriendPage->resize(515, 557);
        verticalLayout = new QVBoxLayout(NewFriendPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        title_wid = new QWidget(NewFriendPage);
        title_wid->setObjectName("title_wid");
        title_wid->setMinimumSize(QSize(0, 50));
        title_wid->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(title_wid);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        title_lab = new QLabel(title_wid);
        title_lab->setObjectName("title_lab");
        title_lab->setMinimumSize(QSize(0, 50));
        title_lab->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(12);
        title_lab->setFont(font);

        horizontalLayout->addWidget(title_lab);


        verticalLayout->addWidget(title_wid);

        app_wid = new QWidget(NewFriendPage);
        app_wid->setObjectName("app_wid");
        verticalLayout_2 = new QVBoxLayout(app_wid);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        applications_list = new NewFriendList(app_wid);
        applications_list->setObjectName("applications_list");
        applications_list->setStyleSheet(QString::fromUtf8("#applications_list {\n"
"    background-color: rgb(245,245,245);\n"
"    border: none;\n"
"}\n"
"\n"
"#applications_list::item:selected {\n"
"    background-color: transparentt;\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"\n"
"#applications_list::item:hover {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"\n"
"#applications_list::item:focus {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));

        verticalLayout_2->addWidget(applications_list);


        verticalLayout->addWidget(app_wid);


        retranslateUi(NewFriendPage);

        QMetaObject::connectSlotsByName(NewFriendPage);
    } // setupUi

    void retranslateUi(QWidget *NewFriendPage)
    {
        NewFriendPage->setWindowTitle(QCoreApplication::translate("NewFriendPage", "Form", nullptr));
        title_lab->setText(QCoreApplication::translate("NewFriendPage", "\346\226\260\347\232\204\346\234\213\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewFriendPage: public Ui_NewFriendPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFRIENDPAGE_H
