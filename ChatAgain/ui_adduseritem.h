/********************************************************************************
** Form generated from reading UI file 'adduseritem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSERITEM_H
#define UI_ADDUSERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddUserItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *addIcon;
    QLabel *tipMsg;
    QLabel *rightIcon;

    void setupUi(QWidget *AddUserItem)
    {
        if (AddUserItem->objectName().isEmpty())
            AddUserItem->setObjectName("AddUserItem");
        AddUserItem->resize(200, 60);
        AddUserItem->setMinimumSize(QSize(200, 60));
        AddUserItem->setMaximumSize(QSize(200, 60));
        horizontalLayout = new QHBoxLayout(AddUserItem);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 0, 0, 0);
        addIcon = new QLabel(AddUserItem);
        addIcon->setObjectName("addIcon");
        addIcon->setPixmap(QPixmap(QString::fromUtf8(":/res/addtip.png")));

        horizontalLayout->addWidget(addIcon, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        tipMsg = new QLabel(AddUserItem);
        tipMsg->setObjectName("tipMsg");
        QFont font;
        font.setPointSize(11);
        tipMsg->setFont(font);

        horizontalLayout->addWidget(tipMsg, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        rightIcon = new QLabel(AddUserItem);
        rightIcon->setObjectName("rightIcon");
        rightIcon->setMinimumSize(QSize(20, 60));
        rightIcon->setMaximumSize(QSize(20, 60));
        QFont font1;
        font1.setPointSize(1);
        rightIcon->setFont(font1);
        rightIcon->setPixmap(QPixmap(QString::fromUtf8(":/res/right_tip.png")));
        rightIcon->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(rightIcon, 0, Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 1);

        retranslateUi(AddUserItem);

        QMetaObject::connectSlotsByName(AddUserItem);
    } // setupUi

    void retranslateUi(QWidget *AddUserItem)
    {
        AddUserItem->setWindowTitle(QCoreApplication::translate("AddUserItem", "Form", nullptr));
        addIcon->setText(QString());
        tipMsg->setText(QCoreApplication::translate("AddUserItem", "\346\220\234\347\264\242\357\274\232", nullptr));
        rightIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddUserItem: public Ui_AddUserItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSERITEM_H
