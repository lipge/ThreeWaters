/********************************************************************************
** Form generated from reading UI file 'friendinfopage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDINFOPAGE_H
#define UI_FRIENDINFOPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendInfoPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QWidget *head_wid;
    QGridLayout *gridLayout_3;
    QLabel *head_lab;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QLabel *remark_lab;
    QLabel *sex_lab;
    QLabel *q1;
    QLabel *nick_lab;
    QLabel *q2;
    QLabel *email_lab;
    QWidget *widget_7;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QFrame *line;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *q5;
    QLabel *REMARK;
    QFrame *line_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *q3;
    QLabel *q4;
    QFrame *line_3;
    QWidget *switch_wid;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *chat_btn;
    QPushButton *phone_btn;
    QPushButton *video_btn;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FriendInfoPage)
    {
        if (FriendInfoPage->objectName().isEmpty())
            FriendInfoPage->setObjectName("FriendInfoPage");
        FriendInfoPage->resize(623, 504);
        verticalLayout = new QVBoxLayout(FriendInfoPage);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(150, 100, 150, 150);
        widget_2 = new QWidget(FriendInfoPage);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 5, 0, 5);
        head_wid = new QWidget(widget_2);
        head_wid->setObjectName("head_wid");
        head_wid->setMinimumSize(QSize(100, 100));
        head_wid->setMaximumSize(QSize(100, 100));
        gridLayout_3 = new QGridLayout(head_wid);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        head_lab = new QLabel(head_wid);
        head_lab->setObjectName("head_lab");

        gridLayout_3->addWidget(head_lab, 0, 0, 1, 1);


        horizontalLayout->addWidget(head_wid);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName("widget_6");
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        remark_lab = new QLabel(widget_6);
        remark_lab->setObjectName("remark_lab");

        gridLayout->addWidget(remark_lab, 0, 0, 1, 2, Qt::AlignmentFlag::AlignLeft);

        sex_lab = new QLabel(widget_6);
        sex_lab->setObjectName("sex_lab");

        gridLayout->addWidget(sex_lab, 0, 2, 1, 1);

        q1 = new QLabel(widget_6);
        q1->setObjectName("q1");

        gridLayout->addWidget(q1, 1, 0, 1, 1);

        nick_lab = new QLabel(widget_6);
        nick_lab->setObjectName("nick_lab");

        gridLayout->addWidget(nick_lab, 1, 1, 1, 2, Qt::AlignmentFlag::AlignLeft);

        q2 = new QLabel(widget_6);
        q2->setObjectName("q2");

        gridLayout->addWidget(q2, 2, 0, 1, 1);

        email_lab = new QLabel(widget_6);
        email_lab->setObjectName("email_lab");

        gridLayout->addWidget(email_lab, 2, 2, 1, 1, Qt::AlignmentFlag::AlignLeft);


        horizontalLayout->addWidget(widget_6);

        widget_7 = new QWidget(widget_2);
        widget_7->setObjectName("widget_7");
        widget_7->setMinimumSize(QSize(50, 0));
        widget_7->setMaximumSize(QSize(50, 16777215));
        gridLayout_2 = new QGridLayout(widget_7);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget_7);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(25, 25));
        pushButton->setMaximumSize(QSize(25, 25));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget_7);


        verticalLayout->addWidget(widget_2);

        line = new QFrame(FriendInfoPage);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        widget = new QWidget(FriendInfoPage);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 5, 0, 5);
        q5 = new QLabel(widget);
        q5->setObjectName("q5");
        QFont font;
        font.setPointSize(10);
        font.setWeight(QFont::Thin);
        font.setKerning(true);
        q5->setFont(font);

        horizontalLayout_2->addWidget(q5);

        REMARK = new QLabel(widget);
        REMARK->setObjectName("REMARK");
        QFont font1;
        font1.setPointSize(10);
        REMARK->setFont(font1);

        horizontalLayout_2->addWidget(REMARK);


        verticalLayout->addWidget(widget);

        line_2 = new QFrame(FriendInfoPage);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        widget_3 = new QWidget(FriendInfoPage);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 5, 0, 5);
        q3 = new QLabel(widget_3);
        q3->setObjectName("q3");
        QFont font2;
        font2.setPointSize(10);
        font2.setWeight(QFont::Thin);
        q3->setFont(font2);

        horizontalLayout_3->addWidget(q3);

        q4 = new QLabel(widget_3);
        q4->setObjectName("q4");
        q4->setFont(font1);

        horizontalLayout_3->addWidget(q4);


        verticalLayout->addWidget(widget_3);

        line_3 = new QFrame(FriendInfoPage);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        switch_wid = new QWidget(FriendInfoPage);
        switch_wid->setObjectName("switch_wid");
        horizontalLayout_4 = new QHBoxLayout(switch_wid);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 20, 0, 0);
        chat_btn = new QPushButton(switch_wid);
        chat_btn->setObjectName("chat_btn");
        chat_btn->setMinimumSize(QSize(70, 50));
        chat_btn->setMaximumSize(QSize(70, 50));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSend));
        chat_btn->setIcon(icon);

        horizontalLayout_4->addWidget(chat_btn);

        phone_btn = new QPushButton(switch_wid);
        phone_btn->setObjectName("phone_btn");
        phone_btn->setMinimumSize(QSize(70, 50));
        phone_btn->setMaximumSize(QSize(70, 50));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::CallStart));
        phone_btn->setIcon(icon1);

        horizontalLayout_4->addWidget(phone_btn);

        video_btn = new QPushButton(switch_wid);
        video_btn->setObjectName("video_btn");
        video_btn->setMinimumSize(QSize(70, 50));
        video_btn->setMaximumSize(QSize(70, 50));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::CameraVideo));
        video_btn->setIcon(icon2);

        horizontalLayout_4->addWidget(video_btn);


        verticalLayout->addWidget(switch_wid);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(FriendInfoPage);

        QMetaObject::connectSlotsByName(FriendInfoPage);
    } // setupUi

    void retranslateUi(QWidget *FriendInfoPage)
    {
        FriendInfoPage->setWindowTitle(QCoreApplication::translate("FriendInfoPage", "Form", nullptr));
        head_lab->setText(QCoreApplication::translate("FriendInfoPage", "\345\244\264\345\203\217", nullptr));
        remark_lab->setText(QCoreApplication::translate("FriendInfoPage", "\345\244\207\346\263\250", nullptr));
        sex_lab->setText(QCoreApplication::translate("FriendInfoPage", "\346\200\247\345\210\253", nullptr));
        q1->setText(QCoreApplication::translate("FriendInfoPage", "\346\230\265\347\247\260\357\274\232", nullptr));
        nick_lab->setText(QCoreApplication::translate("FriendInfoPage", "TextLabel", nullptr));
        q2->setText(QCoreApplication::translate("FriendInfoPage", "\351\202\256\347\256\261\357\274\232", nullptr));
        email_lab->setText(QCoreApplication::translate("FriendInfoPage", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("FriendInfoPage", "\302\267\302\267\302\267", nullptr));
        q5->setText(QCoreApplication::translate("FriendInfoPage", "\345\244\207\346\263\250", nullptr));
        REMARK->setText(QCoreApplication::translate("FriendInfoPage", "TextLabel", nullptr));
        q3->setText(QCoreApplication::translate("FriendInfoPage", "\346\235\245\346\272\220", nullptr));
        q4->setText(QCoreApplication::translate("FriendInfoPage", "\351\200\232\350\277\207\346\220\234\347\264\242uuid\346\267\273\345\212\240", nullptr));
        chat_btn->setText(QString());
        phone_btn->setText(QString());
        video_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendInfoPage: public Ui_FriendInfoPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFOPAGE_H
