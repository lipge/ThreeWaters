/********************************************************************************
** Form generated from reading UI file 'requestaddfriendsdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REQUESTADDFRIENDSDLG_H
#define UI_REQUESTADDFRIENDSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickbtn.h>
#include <clickedoncelabel.h>
#include <customizeedit.h>

QT_BEGIN_NAMESPACE

class Ui_RequestAddFriendsDlg
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *apply_lab;
    QWidget *apply_wid;
    QVBoxLayout *verticalLayout_3;
    QLabel *whoIm_lab;
    QLineEdit *whoIm_edit;
    QLabel *remark_lab;
    QLineEdit *remark_edit;
    QLabel *group_lab;
    QWidget *lab_group_wid;
    QVBoxLayout *verticalLayout_4;
    QWidget *labinput_wid;
    QVBoxLayout *verticalLayout_7;
    CustomizeEdit *labinput_edit;
    QWidget *show_wid;
    QVBoxLayout *verticalLayout_5;
    ClickedOnceLabel *show_lab;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *lab_list;
    QWidget *more_lb_wid;
    QVBoxLayout *verticalLayout_6;
    ClickedOnceLabel *more_lab;
    QWidget *return_wid;
    QHBoxLayout *horizontalLayout;
    ClickBtn *confim_btn;
    ClickBtn *cancle_btn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *RequestAddFriendsDlg)
    {
        if (RequestAddFriendsDlg->objectName().isEmpty())
            RequestAddFriendsDlg->setObjectName("RequestAddFriendsDlg");
        RequestAddFriendsDlg->resize(360, 616);
        RequestAddFriendsDlg->setMinimumSize(QSize(360, 616));
        RequestAddFriendsDlg->setMaximumSize(QSize(360, 616));
        verticalLayout = new QVBoxLayout(RequestAddFriendsDlg);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(RequestAddFriendsDlg);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(360, 500));
        scrollArea->setMaximumSize(QSize(360, 16777215));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollContents = new QWidget();
        scrollContents->setObjectName("scrollContents");
        scrollContents->setGeometry(QRect(0, 0, 360, 498));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollContents->sizePolicy().hasHeightForWidth());
        scrollContents->setSizePolicy(sizePolicy1);
        scrollContents->setMinimumSize(QSize(360, 0));
        scrollContents->setMaximumSize(QSize(360, 16777215));
        verticalLayout_2 = new QVBoxLayout(scrollContents);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        apply_lab = new QLabel(scrollContents);
        apply_lab->setObjectName("apply_lab");
        apply_lab->setMinimumSize(QSize(0, 30));
        apply_lab->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setPointSize(11);
        apply_lab->setFont(font);
        apply_lab->setAlignment(Qt::AlignmentFlag::AlignCenter);
        apply_lab->setWordWrap(true);

        verticalLayout_2->addWidget(apply_lab);

        apply_wid = new QWidget(scrollContents);
        apply_wid->setObjectName("apply_wid");
        apply_wid->setMaximumSize(QSize(360, 16777215));
        apply_wid->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(apply_wid);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 0, 0, 20);
        whoIm_lab = new QLabel(apply_wid);
        whoIm_lab->setObjectName("whoIm_lab");
        whoIm_lab->setMinimumSize(QSize(0, 25));
        whoIm_lab->setMaximumSize(QSize(16777215, 25));
        whoIm_lab->setFont(font);
        whoIm_lab->setMargin(5);

        verticalLayout_3->addWidget(whoIm_lab, 0, Qt::AlignmentFlag::AlignLeft);

        whoIm_edit = new QLineEdit(apply_wid);
        whoIm_edit->setObjectName("whoIm_edit");
        whoIm_edit->setMinimumSize(QSize(0, 36));
        whoIm_edit->setMaximumSize(QSize(330, 30));
        QFont font1;
        font1.setPointSize(10);
        whoIm_edit->setFont(font1);
        whoIm_edit->setStyleSheet(QString::fromUtf8("#whoIm_edit{\n"
"    border: 2px;\n"
"}\n"
""));
        whoIm_edit->setMaxLength(21);
        whoIm_edit->setCursorPosition(2);

        verticalLayout_3->addWidget(whoIm_edit);

        remark_lab = new QLabel(apply_wid);
        remark_lab->setObjectName("remark_lab");
        remark_lab->setMinimumSize(QSize(0, 25));
        remark_lab->setMaximumSize(QSize(16777215, 25));
        remark_lab->setFont(font);
        remark_lab->setMargin(5);

        verticalLayout_3->addWidget(remark_lab, 0, Qt::AlignmentFlag::AlignLeft);

        remark_edit = new QLineEdit(apply_wid);
        remark_edit->setObjectName("remark_edit");
        remark_edit->setMinimumSize(QSize(0, 36));
        remark_edit->setMaximumSize(QSize(330, 30));
        remark_edit->setFont(font);
        remark_edit->setStyleSheet(QString::fromUtf8("#remark_edit{\n"
"	border:2px;\n"
"}"));
        remark_edit->setMaxLength(21);

        verticalLayout_3->addWidget(remark_edit);

        group_lab = new QLabel(apply_wid);
        group_lab->setObjectName("group_lab");
        group_lab->setMinimumSize(QSize(0, 25));
        group_lab->setMaximumSize(QSize(16777215, 25));
        group_lab->setFont(font);
        group_lab->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        group_lab->setMargin(5);

        verticalLayout_3->addWidget(group_lab);

        lab_group_wid = new QWidget(apply_wid);
        lab_group_wid->setObjectName("lab_group_wid");
        lab_group_wid->setMinimumSize(QSize(0, 40));
        lab_group_wid->setMaximumSize(QSize(330, 70));
        verticalLayout_4 = new QVBoxLayout(lab_group_wid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        labinput_wid = new QWidget(lab_group_wid);
        labinput_wid->setObjectName("labinput_wid");
        labinput_wid->setMinimumSize(QSize(0, 40));
        labinput_wid->setMaximumSize(QSize(16777215, 40));
        labinput_wid->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_7 = new QVBoxLayout(labinput_wid);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        labinput_edit = new CustomizeEdit(labinput_wid);
        labinput_edit->setObjectName("labinput_edit");
        labinput_edit->setMinimumSize(QSize(0, 40));
        labinput_edit->setMaximumSize(QSize(16777215, 40));
        labinput_edit->setFont(font1);
        labinput_edit->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        labinput_edit->setStyleSheet(QString::fromUtf8("\n"
"	border:2px;\n"
""));
        labinput_edit->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_7->addWidget(labinput_edit);


        verticalLayout_4->addWidget(labinput_wid);

        show_wid = new QWidget(lab_group_wid);
        show_wid->setObjectName("show_wid");
        show_wid->setMinimumSize(QSize(0, 30));
        show_wid->setMaximumSize(QSize(16777215, 30));
        show_wid->setStyleSheet(QString::fromUtf8("\n"
"	background:#d3eaf8;\n"
""));
        verticalLayout_5 = new QVBoxLayout(show_wid);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        show_lab = new ClickedOnceLabel(show_wid);
        show_lab->setObjectName("show_lab");
        show_lab->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        show_lab->setAutoFillBackground(false);
        show_lab->setStyleSheet(QString::fromUtf8(""));
        show_lab->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_5->addWidget(show_lab);


        verticalLayout_4->addWidget(show_wid);


        verticalLayout_3->addWidget(lab_group_wid, 0, Qt::AlignmentFlag::AlignTop);

        widget = new QWidget(apply_wid);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lab_list = new QWidget(widget);
        lab_list->setObjectName("lab_list");
        lab_list->setMinimumSize(QSize(287, 50));
        lab_list->setMaximumSize(QSize(287, 16777215));

        horizontalLayout_2->addWidget(lab_list);

        more_lb_wid = new QWidget(widget);
        more_lb_wid->setObjectName("more_lb_wid");
        more_lb_wid->setMinimumSize(QSize(30, 0));
        more_lb_wid->setMaximumSize(QSize(30, 16777215));
        verticalLayout_6 = new QVBoxLayout(more_lb_wid);
        verticalLayout_6->setObjectName("verticalLayout_6");
        more_lab = new ClickedOnceLabel(more_lb_wid);
        more_lab->setObjectName("more_lab");
        more_lab->setMinimumSize(QSize(25, 25));
        more_lab->setMaximumSize(QSize(25, 25));

        verticalLayout_6->addWidget(more_lab, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        horizontalLayout_2->addWidget(more_lb_wid);


        verticalLayout_3->addWidget(widget);


        verticalLayout_2->addWidget(apply_wid);

        scrollArea->setWidget(scrollContents);

        verticalLayout->addWidget(scrollArea);

        return_wid = new QWidget(RequestAddFriendsDlg);
        return_wid->setObjectName("return_wid");
        return_wid->setMinimumSize(QSize(0, 0));
        return_wid->setMaximumSize(QSize(360, 16777215));
        horizontalLayout = new QHBoxLayout(return_wid);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 20, 0, 20);
        confim_btn = new ClickBtn(return_wid);
        confim_btn->setObjectName("confim_btn");
        confim_btn->setMinimumSize(QSize(100, 30));
        confim_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(confim_btn);

        cancle_btn = new ClickBtn(return_wid);
        cancle_btn->setObjectName("cancle_btn");
        cancle_btn->setMinimumSize(QSize(100, 30));
        cancle_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(cancle_btn);


        verticalLayout->addWidget(return_wid);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(RequestAddFriendsDlg);

        QMetaObject::connectSlotsByName(RequestAddFriendsDlg);
    } // setupUi

    void retranslateUi(QDialog *RequestAddFriendsDlg)
    {
        RequestAddFriendsDlg->setWindowTitle(QCoreApplication::translate("RequestAddFriendsDlg", "Dialog", nullptr));
        apply_lab->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\347\224\263\350\257\267\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        whoIm_lab->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\345\217\221\351\200\201\346\267\273\345\212\240\346\234\213\345\217\213\347\224\263\350\257\267", nullptr));
        whoIm_edit->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\346\210\221\346\230\257", nullptr));
        remark_lab->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\345\244\207\346\263\250\345\220\215", nullptr));
        group_lab->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\346\240\207\347\255\276", nullptr));
        show_lab->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\346\267\273\345\212\240\346\240\207\347\255\276\357\274\232 ", nullptr));
        more_lab->setText(QString());
        confim_btn->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\347\241\256\350\256\244", nullptr));
        cancle_btn->setText(QCoreApplication::translate("RequestAddFriendsDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RequestAddFriendsDlg: public Ui_RequestAddFriendsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REQUESTADDFRIENDSDLG_H
