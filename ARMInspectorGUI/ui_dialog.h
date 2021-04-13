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

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *pushButton_addUser;
    QPushButton *pushButton_editUser;
    QPushButton *pushButton_deleteUser;
    QPushButton *pushButton_changePassword;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QString::fromUtf8("dialog"));
        dialog->resize(718, 701);
        gridLayout_2 = new QGridLayout(dialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(dialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 4);

        pushButton_addUser = new QPushButton(dialog);
        pushButton_addUser->setObjectName(QString::fromUtf8("pushButton_addUser"));

        gridLayout->addWidget(pushButton_addUser, 1, 0, 1, 1);

        pushButton_editUser = new QPushButton(dialog);
        pushButton_editUser->setObjectName(QString::fromUtf8("pushButton_editUser"));

        gridLayout->addWidget(pushButton_editUser, 1, 1, 1, 1);

        pushButton_deleteUser = new QPushButton(dialog);
        pushButton_deleteUser->setObjectName(QString::fromUtf8("pushButton_deleteUser"));

        gridLayout->addWidget(pushButton_deleteUser, 1, 2, 1, 1);

        pushButton_changePassword = new QPushButton(dialog);
        pushButton_changePassword->setObjectName(QString::fromUtf8("pushButton_changePassword"));
        pushButton_changePassword->setFocusPolicy(Qt::NoFocus);
        pushButton_changePassword->setContextMenuPolicy(Qt::PreventContextMenu);

        gridLayout->addWidget(pushButton_changePassword, 1, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


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
