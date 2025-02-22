/********************************************************************************
** Form generated from reading UI file 'contactitem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTITEM_H
#define UI_CONTACTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContactItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *icon_lab;
    QLabel *dot_lab;
    QLabel *name_lab;

    void setupUi(QWidget *ContactItem)
    {
        if (ContactItem->objectName().isEmpty())
            ContactItem->setObjectName("ContactItem");
        ContactItem->resize(322, 70);
        ContactItem->setMinimumSize(QSize(0, 70));
        ContactItem->setMaximumSize(QSize(16777215, 70));
        ContactItem->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(ContactItem);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        widget = new QWidget(ContactItem);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(50, 50));
        widget->setMaximumSize(QSize(50, 50));
        icon_lab = new QLabel(widget);
        icon_lab->setObjectName("icon_lab");
        icon_lab->setGeometry(QRect(10, 0, 35, 35));
        icon_lab->setMinimumSize(QSize(35, 35));
        icon_lab->setMaximumSize(QSize(35, 35));
        dot_lab = new QLabel(widget);
        dot_lab->setObjectName("dot_lab");
        dot_lab->setGeometry(QRect(18, -4, 30, 30));
        dot_lab->setMinimumSize(QSize(30, 30));
        dot_lab->setMaximumSize(QSize(30, 30));
        dot_lab->setStyleSheet(QString::fromUtf8(""));
        dot_lab->setPixmap(QPixmap(QString::fromUtf8(":/res/red_point.png")));

        horizontalLayout->addWidget(widget, 0, Qt::AlignmentFlag::AlignVCenter);

        name_lab = new QLabel(ContactItem);
        name_lab->setObjectName("name_lab");

        horizontalLayout->addWidget(name_lab);


        retranslateUi(ContactItem);

        QMetaObject::connectSlotsByName(ContactItem);
    } // setupUi

    void retranslateUi(QWidget *ContactItem)
    {
        ContactItem->setWindowTitle(QCoreApplication::translate("ContactItem", "Form", nullptr));
        icon_lab->setText(QCoreApplication::translate("ContactItem", "\345\244\264\345\203\217", nullptr));
        dot_lab->setText(QString());
        name_lab->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ContactItem: public Ui_ContactItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTITEM_H
