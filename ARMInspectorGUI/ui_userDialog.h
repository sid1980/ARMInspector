/********************************************************************************
** Form generated from reading UI file 'userDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERDIALOG_H
#define UI_USERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_userDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label;
    QLineEdit *lineEdit_inspection_3;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *lineEdit_fio;
    QLabel *label_inspection;
    QLabel *label_2;
    QLabel *label_fio;
    QLineEdit *lineEdit_inspection;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QCheckBox *checkBox;
    QLabel *label_4;
    QLineEdit *lineEdit_inspection_2;

    void setupUi(QDialog *userDialog)
    {
        if (userDialog->objectName().isEmpty())
            userDialog->setObjectName(QString::fromUtf8("userDialog"));
        userDialog->resize(481, 453);
        gridLayout_2 = new QGridLayout(userDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(userDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 7, 2, 1, 1);

        groupBox = new QGroupBox(userDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 23, 217, 17));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 59, 170, 17));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 95, 78, 17));

        gridLayout->addWidget(groupBox, 4, 1, 1, 2);

        label = new QLabel(userDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lineEdit_inspection_3 = new QLineEdit(userDialog);
        lineEdit_inspection_3->setObjectName(QString::fromUtf8("lineEdit_inspection_3"));

        gridLayout->addWidget(lineEdit_inspection_3, 3, 1, 1, 2);

        label_3 = new QLabel(userDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_5 = new QLabel(userDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        lineEdit_fio = new QLineEdit(userDialog);
        lineEdit_fio->setObjectName(QString::fromUtf8("lineEdit_fio"));

        gridLayout->addWidget(lineEdit_fio, 0, 1, 1, 2);

        label_inspection = new QLabel(userDialog);
        label_inspection->setObjectName(QString::fromUtf8("label_inspection"));

        gridLayout->addWidget(label_inspection, 1, 0, 1, 1);

        label_2 = new QLabel(userDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_fio = new QLabel(userDialog);
        label_fio->setObjectName(QString::fromUtf8("label_fio"));
        label_fio->setMaximumSize(QSize(208, 16777215));

        gridLayout->addWidget(label_fio, 0, 0, 1, 1);

        lineEdit_inspection = new QLineEdit(userDialog);
        lineEdit_inspection->setObjectName(QString::fromUtf8("lineEdit_inspection"));

        gridLayout->addWidget(lineEdit_inspection, 1, 1, 1, 2);

        groupBox_2 = new QGroupBox(userDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 10, 221, 20));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 30, 221, 20));
        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(10, 50, 221, 20));
        radioButton_7 = new QRadioButton(groupBox_2);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(10, 70, 221, 20));

        gridLayout->addWidget(groupBox_2, 5, 1, 1, 2);

        checkBox = new QCheckBox(userDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 6, 1, 1, 1);

        label_4 = new QLabel(userDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        lineEdit_inspection_2 = new QLineEdit(userDialog);
        lineEdit_inspection_2->setObjectName(QString::fromUtf8("lineEdit_inspection_2"));

        gridLayout->addWidget(lineEdit_inspection_2, 2, 1, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(userDialog);

        QMetaObject::connectSlotsByName(userDialog);
    } // setupUi

    void retranslateUi(QDialog *userDialog)
    {
        userDialog->setWindowTitle(QCoreApplication::translate("userDialog", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265", nullptr));
        pushButton->setText(QCoreApplication::translate("userDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        groupBox->setTitle(QString());
        radioButton->setText(QCoreApplication::translate("userDialog", "\320\241\321\202\320\260\321\200\321\210\320\270\320\271 \320\263\320\276\321\201\321\203\320\264\320\260\321\200\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200", nullptr));
        radioButton_2->setText(QCoreApplication::translate("userDialog", "\320\223\320\276\321\201\321\203\320\264\320\260\321\200\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200", nullptr));
        radioButton_3->setText(QCoreApplication::translate("userDialog", "\320\241\320\265\320\272\321\200\320\265\321\202\320\260\321\200\321\214", nullptr));
        label->setText(QCoreApplication::translate("userDialog", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("userDialog", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        label_5->setText(QCoreApplication::translate("userDialog", "\320\224\320\276\321\201\321\202\321\203\320\277", nullptr));
        label_inspection->setText(QCoreApplication::translate("userDialog", "\320\230\320\275\321\201\320\277\320\265\320\272\321\206\320\270\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("userDialog", "\320\237\320\260\321\200\320\276\320\273\321\214(\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214)", nullptr));
        label_fio->setText(QCoreApplication::translate("userDialog", "\320\244\320\230\320\236", nullptr));
        groupBox_2->setTitle(QString());
        radioButton_4->setText(QCoreApplication::translate("userDialog", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200", nullptr));
        radioButton_5->setText(QCoreApplication::translate("userDialog", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200 \320\234\320\240\320\236", nullptr));
        radioButton_6->setText(QCoreApplication::translate("userDialog", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200 \320\240\320\255\320\223\320\230", nullptr));
        radioButton_7->setText(QCoreApplication::translate("userDialog", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        checkBox->setText(QCoreApplication::translate("userDialog", "\320\242\320\276\320\273\321\214\320\272\320\276 \321\207\321\202\320\265\320\275\320\270\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("userDialog", "\320\240\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userDialog: public Ui_userDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERDIALOG_H
