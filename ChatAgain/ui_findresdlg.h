/********************************************************************************
** Form generated from reading UI file 'findresdlg.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDRESDLG_H
#define UI_FINDRESDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickbtn.h>

QT_BEGIN_NAMESPACE

class Ui_FindResDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stack_wid;
    QWidget *success_page;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *headshot_lab;
    QSpacerItem *horizontalSpacer;
    QLabel *name_lab;
    QLabel *desc_lab;
    QLabel *sex_lab;
    QLabel *label_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    ClickBtn *addto_contracts_btn;
    QWidget *failed_page;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    ClickBtn *notfound_btn;

    void setupUi(QDialog *FindResDlg)
    {
        if (FindResDlg->objectName().isEmpty())
            FindResDlg->setObjectName("FindResDlg");
        FindResDlg->resize(280, 186);
        QFont font;
        font.setHintingPreference(QFont::PreferDefaultHinting);
        FindResDlg->setFont(font);
        verticalLayout_2 = new QVBoxLayout(FindResDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        stack_wid = new QStackedWidget(FindResDlg);
        stack_wid->setObjectName("stack_wid");
        success_page = new QWidget();
        success_page->setObjectName("success_page");
        success_page->setMinimumSize(QSize(280, 186));
        success_page->setMaximumSize(QSize(280, 186));
        verticalLayout_3 = new QVBoxLayout(success_page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        widget_2 = new QWidget(success_page);
        widget_2->setObjectName("widget_2");
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        headshot_lab = new QLabel(widget_2);
        headshot_lab->setObjectName("headshot_lab");
        headshot_lab->setMinimumSize(QSize(60, 60));
        headshot_lab->setMaximumSize(QSize(60, 60));

        gridLayout->addWidget(headshot_lab, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        name_lab = new QLabel(widget_2);
        name_lab->setObjectName("name_lab");
        QFont font1;
        font1.setPointSize(12);
        font1.setHintingPreference(QFont::PreferDefaultHinting);
        name_lab->setFont(font1);

        gridLayout->addWidget(name_lab, 0, 1, 1, 1);

        desc_lab = new QLabel(widget_2);
        desc_lab->setObjectName("desc_lab");

        gridLayout->addWidget(desc_lab, 1, 1, 1, 1);

        sex_lab = new QLabel(widget_2);
        sex_lab->setObjectName("sex_lab");
        sex_lab->setMinimumSize(QSize(20, 20));
        sex_lab->setMaximumSize(QSize(20, 20));
        sex_lab->setPixmap(QPixmap(QString::fromUtf8(":/res/male.png")));
        sex_lab->setScaledContents(true);

        gridLayout->addWidget(sex_lab, 0, 2, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 2, 1, 1);


        verticalLayout_3->addWidget(widget_2);

        widget = new QWidget(success_page);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        addto_contracts_btn = new ClickBtn(widget);
        addto_contracts_btn->setObjectName("addto_contracts_btn");
        addto_contracts_btn->setMinimumSize(QSize(110, 35));
        addto_contracts_btn->setMaximumSize(QSize(110, 35));

        horizontalLayout_2->addWidget(addto_contracts_btn);


        verticalLayout_3->addWidget(widget);

        stack_wid->addWidget(success_page);
        failed_page = new QWidget();
        failed_page->setObjectName("failed_page");
        failed_page->setMinimumSize(QSize(260, 160));
        failed_page->setMaximumSize(QSize(260, 160));
        verticalLayout = new QVBoxLayout(failed_page);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label = new QLabel(failed_page);
        label->setObjectName("label");
        label->setMinimumSize(QSize(200, 100));
        label->setMaximumSize(QSize(200, 100));
        QFont font2;
        font2.setPointSize(11);
        font2.setHintingPreference(QFont::PreferDefaultHinting);
        label->setFont(font2);
        label->setWordWrap(true);

        verticalLayout->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter);

        notfound_btn = new ClickBtn(failed_page);
        notfound_btn->setObjectName("notfound_btn");
        notfound_btn->setMinimumSize(QSize(100, 30));
        notfound_btn->setMaximumSize(QSize(100, 30));
        QFont font3;
        font3.setPointSize(9);
        font3.setHintingPreference(QFont::PreferDefaultHinting);
        notfound_btn->setFont(font3);

        verticalLayout->addWidget(notfound_btn, 0, Qt::AlignmentFlag::AlignHCenter);

        stack_wid->addWidget(failed_page);

        verticalLayout_2->addWidget(stack_wid);


        retranslateUi(FindResDlg);

        stack_wid->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FindResDlg);
    } // setupUi

    void retranslateUi(QDialog *FindResDlg)
    {
        FindResDlg->setWindowTitle(QCoreApplication::translate("FindResDlg", "Dialog", nullptr));
        headshot_lab->setText(QCoreApplication::translate("FindResDlg", "Pixmap", nullptr));
        name_lab->setText(QCoreApplication::translate("FindResDlg", "name", nullptr));
        desc_lab->setText(QCoreApplication::translate("FindResDlg", "dsc", nullptr));
        sex_lab->setText(QString());
        label_4->setText(QCoreApplication::translate("FindResDlg", "dsc", nullptr));
        addto_contracts_btn->setText(QCoreApplication::translate("FindResDlg", "\346\267\273\345\212\240\345\210\260\351\200\232\350\256\257\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("FindResDlg", "\346\227\240\346\263\225\346\211\276\345\210\260\350\257\245\347\224\250\346\210\267\357\274\214\350\257\267\346\243\200\346\237\245\344\275\240\345\241\253\345\206\231\347\232\204\350\264\246\345\217\267\346\230\257\345\220\246\346\255\243\347\241\256\343\200\202", nullptr));
        notfound_btn->setText(QCoreApplication::translate("FindResDlg", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindResDlg: public Ui_FindResDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDRESDLG_H
