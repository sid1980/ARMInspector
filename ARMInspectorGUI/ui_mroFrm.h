/********************************************************************************
** Form generated from reading UI file 'mroFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MROFRM_H
#define UI_MROFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_mroFrm
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *mroFrm)
    {
        if (mroFrm->objectName().isEmpty())
            mroFrm->setObjectName(QString::fromUtf8("mroFrm"));
        mroFrm->resize(400, 300);
        gridLayout_2 = new QGridLayout(mroFrm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(mroFrm);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 3);

        pushButton = new QPushButton(mroFrm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(mroFrm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(mroFrm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(mroFrm);

        QMetaObject::connectSlotsByName(mroFrm);
    } // setupUi

    void retranslateUi(QDialog *mroFrm)
    {
        mroFrm->setWindowTitle(QCoreApplication::translate("mroFrm", "mroFrm", nullptr));
        pushButton->setText(QCoreApplication::translate("mroFrm", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("mroFrm", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("mroFrm", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mroFrm: public Ui_mroFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MROFRM_H
