/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QTableView *tableView;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_addUser;
    QPushButton *pushButton_editUser;
    QPushButton *pushButton_deleteUser;
    QPushButton *pushButton_changePassword;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QString::fromUtf8("dialog"));
        dialog->resize(718, 701);
        dialog->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 150px;\n"
"max-width: 150px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}\n"
"QTableView {\n"
"         Color: white; /* text color in the table */\n"
"         Gridline-color: black; /*The inner frame color*/\n"
"         Background-color: rgb(108, 108, 108); /* background color in the table*/\n"
"    alternate-background-color: rgb(64, 64, 64);\n"
"         Selection-color: white; /* The text color of the selected area*/\n"
"         Selection-background-color: rgb(77, 77, 77); /*The background color of the selected area*/\n"
"    border: 2px groove gray;\n"
"    border-radius: 0px;\n"
"    padding: 2px 4px;\n"
"}\n"
"\n"
"QMessageBox QPu"
                        "shButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 50px;\n"
"max-width: 50px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}\n"
""));
        tableView = new QTableView(dialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 691, 641));
        layoutWidget = new QWidget(dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 670, 668, 23));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_addUser = new QPushButton(layoutWidget);
        pushButton_addUser->setObjectName(QString::fromUtf8("pushButton_addUser"));

        gridLayout->addWidget(pushButton_addUser, 0, 0, 1, 1);

        pushButton_editUser = new QPushButton(layoutWidget);
        pushButton_editUser->setObjectName(QString::fromUtf8("pushButton_editUser"));

        gridLayout->addWidget(pushButton_editUser, 0, 1, 1, 1);

        pushButton_deleteUser = new QPushButton(layoutWidget);
        pushButton_deleteUser->setObjectName(QString::fromUtf8("pushButton_deleteUser"));

        gridLayout->addWidget(pushButton_deleteUser, 0, 2, 1, 1);

        pushButton_changePassword = new QPushButton(layoutWidget);
        pushButton_changePassword->setObjectName(QString::fromUtf8("pushButton_changePassword"));
        pushButton_changePassword->setFocusPolicy(Qt::NoFocus);
        pushButton_changePassword->setContextMenuPolicy(Qt::PreventContextMenu);

        gridLayout->addWidget(pushButton_changePassword, 0, 3, 1, 1);


        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QCoreApplication::translate("dialog", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271 \320\220\320\240\320\234", nullptr));
        pushButton_addUser->setText(QCoreApplication::translate("dialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_editUser->setText(QCoreApplication::translate("dialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 ", nullptr));
        pushButton_deleteUser->setText(QCoreApplication::translate("dialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButton_changePassword->setText(QCoreApplication::translate("dialog", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
