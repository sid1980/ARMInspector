/********************************************************************************
** Form generated from reading UI file 'nsiFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSIFRM_H
#define UI_NSIFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_nsiFrm
{
public:
    QTableView *tableView;

    void setupUi(QDialog *nsiFrm)
    {
        if (nsiFrm->objectName().isEmpty())
            nsiFrm->setObjectName(QString::fromUtf8("nsiFrm"));
        nsiFrm->resize(400, 300);
        tableView = new QTableView(nsiFrm);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(60, 40, 256, 192));

        retranslateUi(nsiFrm);

        QMetaObject::connectSlotsByName(nsiFrm);
    } // setupUi

    void retranslateUi(QDialog *nsiFrm)
    {
        nsiFrm->setWindowTitle(QCoreApplication::translate("nsiFrm", "nsiFrm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nsiFrm: public Ui_nsiFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSIFRM_H
