/********************************************************************************
** Form generated from reading UI file 'userForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFORM_H
#define UI_USERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userForm
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditFio;
    QLabel *labelPassword;
    QLabel *labelRole;
    QLabel *labelFio;
    QLabel *labelInspection;
    QLabel *labelAccess;
    QLineEdit *lineEditPassword;
    QGroupBox *groupBoxStatus;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *labelStatus;
    QLineEdit *lineEditPassword_2;
    QLabel *labelPassword_2;
    QGroupBox *groupBoxRole;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QComboBox *comboBoxInspection;
    QLineEdit *lineEditName;
    QLabel *labelName;
    QCheckBox *checkBox;

    void setupUi(QDialog *userForm)
    {
        if (userForm->objectName().isEmpty())
            userForm->setObjectName(QString::fromUtf8("userForm"));
        userForm->resize(626, 516);
        userForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"QLineEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 1px solid gray;\n"
"border-radius: 8px;\n"
" min-height: 30px;\n"
"}\n"
"QGroupBox {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 1ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; /* position at the top center */\n"
""
                        "    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"}\n"
"\n"
""));
        layoutWidget = new QWidget(userForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 581, 481));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 8, 1, 1, 1);

        lineEditFio = new QLineEdit(layoutWidget);
        lineEditFio->setObjectName(QString::fromUtf8("lineEditFio"));

        gridLayout->addWidget(lineEditFio, 0, 1, 1, 1);

        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        gridLayout->addWidget(labelPassword, 3, 0, 1, 1);

        labelRole = new QLabel(layoutWidget);
        labelRole->setObjectName(QString::fromUtf8("labelRole"));

        gridLayout->addWidget(labelRole, 6, 0, 1, 1);

        labelFio = new QLabel(layoutWidget);
        labelFio->setObjectName(QString::fromUtf8("labelFio"));

        gridLayout->addWidget(labelFio, 0, 0, 1, 1);

        labelInspection = new QLabel(layoutWidget);
        labelInspection->setObjectName(QString::fromUtf8("labelInspection"));

        gridLayout->addWidget(labelInspection, 1, 0, 1, 1);

        labelAccess = new QLabel(layoutWidget);
        labelAccess->setObjectName(QString::fromUtf8("labelAccess"));

        gridLayout->addWidget(labelAccess, 7, 0, 1, 1);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setToolTipDuration(-2);
        lineEditPassword->setMaxLength(32764);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        lineEditPassword->setCursorPosition(0);

        gridLayout->addWidget(lineEditPassword, 3, 1, 1, 1);

        groupBoxStatus = new QGroupBox(layoutWidget);
        groupBoxStatus->setObjectName(QString::fromUtf8("groupBoxStatus"));
        radioButton_1 = new QRadioButton(groupBoxStatus);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));
        radioButton_1->setGeometry(QRect(10, 20, 341, 22));
        radioButton_2 = new QRadioButton(groupBoxStatus);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 40, 311, 22));
        radioButton_3 = new QRadioButton(groupBoxStatus);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 60, 100, 22));

        gridLayout->addWidget(groupBoxStatus, 5, 1, 1, 1);

        labelStatus = new QLabel(layoutWidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));

        gridLayout->addWidget(labelStatus, 5, 0, 1, 1);

        lineEditPassword_2 = new QLineEdit(layoutWidget);
        lineEditPassword_2->setObjectName(QString::fromUtf8("lineEditPassword_2"));
        lineEditPassword_2->setFrame(true);
        lineEditPassword_2->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPassword_2, 4, 1, 1, 1);

        labelPassword_2 = new QLabel(layoutWidget);
        labelPassword_2->setObjectName(QString::fromUtf8("labelPassword_2"));

        gridLayout->addWidget(labelPassword_2, 4, 0, 1, 1);

        groupBoxRole = new QGroupBox(layoutWidget);
        groupBoxRole->setObjectName(QString::fromUtf8("groupBoxRole"));
        radioButton_4 = new QRadioButton(groupBoxRole);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 20, 341, 22));
        radioButton_5 = new QRadioButton(groupBoxRole);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 40, 311, 22));
        radioButton_6 = new QRadioButton(groupBoxRole);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(10, 60, 191, 22));
        radioButton_7 = new QRadioButton(groupBoxRole);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(10, 80, 161, 22));

        gridLayout->addWidget(groupBoxRole, 6, 1, 1, 1);

        comboBoxInspection = new QComboBox(layoutWidget);
        comboBoxInspection->setObjectName(QString::fromUtf8("comboBoxInspection"));
        comboBoxInspection->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"   background: qlineargradient(\n"
"   x1:0, y1:0, x2:0, y2:1,\n"
"   stop:0 #f9f9f9,\n"
"   stop: 0.5 #c6c6c6,\n"
"   stop: 0.6 #dfdfdf,\n"
"   stop:1 #f9f9f9 );\n"
"   border-style: solid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 8px;\n"
"   color: rgb(0, 93, 168);\n"
"   min-width: 170px;\n"
"   min-height: 30px;\n"
"   padding-left: 15px;\n"
"}\n"
"QComboBox:on {\n"
"   border-radius: 30px;\n"
"   background:transparent;\n"
"}\n"
"QComboBox::drop-down {\n"
"   image: url(:/bwt/downarrow.png);\n"
"   subcontrol-position: center right;\n"
"   margin-right: 10px;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"   padding: 10px 10px 10px 10px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"   color: rgb(0, 93, 168);\n"
"   background: transparent;\n"
"}\n"
"QComboBox QListView::item {\n"
"   background: qradialgradient(\n"
"   cx: 0.5, cy: -1.6, fx: 0.5, fy: 0,\n"
"   radius: 2,\n"
"   stop: 0 #C4C4C4,\n"
"   stop: 1 #DBDBDB );\n"
"   border-style: so"
                        "lid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 20px;\n"
"}"));

        gridLayout->addWidget(comboBoxInspection, 1, 1, 1, 1);

        lineEditName = new QLineEdit(layoutWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 2, 1, 1, 1);

        labelName = new QLabel(layoutWidget);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout->addWidget(labelName, 2, 0, 1, 1);

        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 7, 1, 1, 1);


        retranslateUi(userForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), userForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), userForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(userForm);
    } // setupUi

    void retranslateUi(QDialog *userForm)
    {
        userForm->setWindowTitle(QCoreApplication::translate("userForm", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\263\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        lineEditFio->setPlaceholderText(QCoreApplication::translate("userForm", "\321\204\320\270\320\276", nullptr));
        labelPassword->setText(QCoreApplication::translate("userForm", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelRole->setText(QCoreApplication::translate("userForm", "\320\240\320\276\320\273\321\214", nullptr));
        labelFio->setText(QCoreApplication::translate("userForm", "\320\244\320\230\320\236", nullptr));
        labelInspection->setText(QCoreApplication::translate("userForm", "\320\230\320\275\321\201\320\277\320\265\320\272\321\206\320\270\321\217", nullptr));
        labelAccess->setText(QCoreApplication::translate("userForm", "\320\224\320\276\321\201\321\202\321\203\320\277", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("userForm", "\320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        groupBoxStatus->setTitle(QString());
        radioButton_1->setText(QCoreApplication::translate("userForm", "\320\241\321\202\320\260\321\200\321\210\320\270\320\271 \320\263\320\276\321\201\321\203\320\264\320\260\321\200\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200", nullptr));
        radioButton_2->setText(QCoreApplication::translate("userForm", "\320\223\320\276\321\201\321\203\320\264\320\260\321\200\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200", nullptr));
        radioButton_3->setText(QCoreApplication::translate("userForm", "\320\241\320\265\320\272\321\200\320\265\321\202\320\260\321\200\321\214", nullptr));
        labelStatus->setText(QCoreApplication::translate("userForm", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        lineEditPassword_2->setPlaceholderText(QCoreApplication::translate("userForm", "\320\277\320\260\321\200\320\276\320\273\321\214(\320\277\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214)", nullptr));
        labelPassword_2->setText(QCoreApplication::translate("userForm", "\320\237\320\260\321\200\320\276\320\273\321\214(\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214)", nullptr));
        groupBoxRole->setTitle(QString());
        radioButton_4->setText(QCoreApplication::translate("userForm", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200 \320\261\320\260\320\267\321\213 \320\264\320\260\320\275\320\275\321\213\321\205 \320\220\320\240\320\234", nullptr));
        radioButton_5->setText(QCoreApplication::translate("userForm", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200 \320\234\320\240\320\236", nullptr));
        radioButton_6->setText(QCoreApplication::translate("userForm", "\320\220\320\264\320\274\320\270\321\200\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200 \320\240\320\255\320\223\320\230", nullptr));
        radioButton_7->setText(QCoreApplication::translate("userForm", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        lineEditName->setText(QString());
        lineEditName->setPlaceholderText(QCoreApplication::translate("userForm", "\320\270\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        labelName->setText(QCoreApplication::translate("userForm", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        checkBox->setText(QCoreApplication::translate("userForm", "\320\242\320\276\320\273\321\214\320\272\320\276 \321\207\321\202\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userForm: public Ui_userForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFORM_H
