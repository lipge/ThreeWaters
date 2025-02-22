/********************************************************************************
** Form generated from reading UI file 'loginfailed.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFAILED_H
#define UI_LOGINFAILED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginFailed
{
public:
    QPushButton *return_Btn;
    QPushButton *foget_Btn;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *LoginFailed)
    {
        if (LoginFailed->objectName().isEmpty())
            LoginFailed->setObjectName("LoginFailed");
        LoginFailed->resize(260, 160);
        LoginFailed->setMaximumSize(QSize(260, 160));
        return_Btn = new QPushButton(LoginFailed);
        return_Btn->setObjectName("return_Btn");
        return_Btn->setGeometry(QRect(160, 110, 80, 30));
        return_Btn->setMinimumSize(QSize(0, 30));
        return_Btn->setMaximumSize(QSize(16777215, 30));
        foget_Btn = new QPushButton(LoginFailed);
        foget_Btn->setObjectName("foget_Btn");
        foget_Btn->setGeometry(QRect(60, 110, 80, 30));
        foget_Btn->setMinimumSize(QSize(0, 30));
        foget_Btn->setMaximumSize(QSize(16777215, 30));
        label = new QLabel(LoginFailed);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 53, 15));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(LoginFailed);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 201, 16));
        label_2->setFont(font);

        retranslateUi(LoginFailed);

        QMetaObject::connectSlotsByName(LoginFailed);
    } // setupUi

    void retranslateUi(QDialog *LoginFailed)
    {
        LoginFailed->setWindowTitle(QCoreApplication::translate("LoginFailed", "Dialog", nullptr));
        return_Btn->setText(QCoreApplication::translate("LoginFailed", "\351\207\215\346\226\260\347\231\273\345\275\225", nullptr));
        foget_Btn->setText(QCoreApplication::translate("LoginFailed", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("LoginFailed", "\347\231\273\345\275\225\345\244\261\350\264\245", nullptr));
        label_2->setText(QCoreApplication::translate("LoginFailed", "\351\202\256\347\256\261\346\210\226\345\257\206\347\240\201\351\224\231\350\257\257\357\274\214\350\257\267\351\207\215\346\226\260\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginFailed: public Ui_LoginFailed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFAILED_H
