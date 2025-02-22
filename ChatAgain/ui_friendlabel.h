/********************************************************************************
** Form generated from reading UI file 'friendlabel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLABEL_H
#define UI_FRIENDLABEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendLabel
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *tip_lab;
    QPushButton *close_btn;

    void setupUi(QWidget *FriendLabel)
    {
        if (FriendLabel->objectName().isEmpty())
            FriendLabel->setObjectName("FriendLabel");
        FriendLabel->resize(135, 30);
        FriendLabel->setMinimumSize(QSize(0, 30));
        FriendLabel->setMaximumSize(QSize(16777215, 30));
        FriendLabel->setStyleSheet(QString::fromUtf8("#FriendLabel{\n"
"	background: #daf6e7;\n"
"	color: #48bf56;\n"
"	border-radius: 10px\n"
"}"));
        horizontalLayout = new QHBoxLayout(FriendLabel);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 0, 0, 0);
        tip_lab = new QLabel(FriendLabel);
        tip_lab->setObjectName("tip_lab");
        tip_lab->setMinimumSize(QSize(0, 30));
        tip_lab->setMaximumSize(QSize(16777215, 30));
        tip_lab->setStyleSheet(QString::fromUtf8("    background: #daf6e7;\n"
"    color: #48bf56;\n"
"    border-radius: 10px;"));
        tip_lab->setScaledContents(false);
        tip_lab->setWordWrap(false);

        horizontalLayout->addWidget(tip_lab);

        close_btn = new QPushButton(FriendLabel);
        close_btn->setObjectName("close_btn");
        close_btn->setMinimumSize(QSize(20, 20));
        close_btn->setMaximumSize(QSize(20, 20));
        close_btn->setStyleSheet(QString::fromUtf8("    background: #daf6e7;\n"
"    color: #48bf56;\n"
"    border-radius: 10px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/tipclose.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        close_btn->setIcon(icon);
        close_btn->setAutoDefault(false);
        close_btn->setFlat(true);

        horizontalLayout->addWidget(close_btn, 0, Qt::AlignmentFlag::AlignLeft);


        retranslateUi(FriendLabel);

        close_btn->setDefault(false);


        QMetaObject::connectSlotsByName(FriendLabel);
    } // setupUi

    void retranslateUi(QWidget *FriendLabel)
    {
        FriendLabel->setWindowTitle(QCoreApplication::translate("FriendLabel", "Form", nullptr));
        tip_lab->setText(QCoreApplication::translate("FriendLabel", "6666", nullptr));
        close_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendLabel: public Ui_FriendLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLABEL_H
