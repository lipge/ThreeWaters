/********************************************************************************
** Form generated from reading UI file 'groupitem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPITEM_H
#define UI_GROUPITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *GroupItem)
    {
        if (GroupItem->objectName().isEmpty())
            GroupItem->setObjectName("GroupItem");
        GroupItem->setEnabled(false);
        GroupItem->resize(427, 60);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GroupItem->sizePolicy().hasHeightForWidth());
        GroupItem->setSizePolicy(sizePolicy);
        GroupItem->setMinimumSize(QSize(0, 60));
        GroupItem->setMaximumSize(QSize(16777214, 60));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        GroupItem->setFont(font);
        GroupItem->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(GroupItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(15, 10, 0, 0);
        label = new QLabel(GroupItem);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(label, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);


        retranslateUi(GroupItem);

        QMetaObject::connectSlotsByName(GroupItem);
    } // setupUi

    void retranslateUi(QWidget *GroupItem)
    {
        GroupItem->setWindowTitle(QCoreApplication::translate("GroupItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("GroupItem", "\346\226\260\347\232\204\346\234\213\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupItem: public Ui_GroupItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPITEM_H
