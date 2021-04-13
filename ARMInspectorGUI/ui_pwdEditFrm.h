/********************************************************************************
** Form generated from reading UI file 'pwdEditFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWDEDITFRM_H
#define UI_PWDEDITFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_pwdEditFrm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelPwd;
    QLineEdit *lineEditPwd;
    QLabel *labelPwd2;
    QLineEdit *lineEditPwd2;

    void setupUi(QDialog *pwdEditFrm)
    {
        if (pwdEditFrm->objectName().isEmpty())
            pwdEditFrm->setObjectName(QString::fromUtf8("pwdEditFrm"));
        pwdEditFrm->resize(400, 300);
        pwdEditFrm->setWindowOpacity(-7.000000000000000);
        buttonBox = new QDialogButtonBox(pwdEditFrm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelPwd = new QLabel(pwdEditFrm);
        labelPwd->setObjectName(QString::fromUtf8("labelPwd"));
        labelPwd->setGeometry(QRect(50, 60, 91, 16));
        lineEditPwd = new QLineEdit(pwdEditFrm);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));
        lineEditPwd->setGeometry(QRect(160, 60, 221, 20));
        lineEditPwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        labelPwd2 = new QLabel(pwdEditFrm);
        labelPwd2->setObjectName(QString::fromUtf8("labelPwd2"));
        labelPwd2->setGeometry(QRect(50, 120, 101, 16));
        lineEditPwd2 = new QLineEdit(pwdEditFrm);
        lineEditPwd2->setObjectName(QString::fromUtf8("lineEditPwd2"));
        lineEditPwd2->setGeometry(QRect(160, 120, 221, 20));
        lineEditPwd2->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        retranslateUi(pwdEditFrm);
        QObject::connect(buttonBox, SIGNAL(accepted()), pwdEditFrm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), pwdEditFrm, SLOT(reject()));

        QMetaObject::connectSlotsByName(pwdEditFrm);
    } // setupUi

    void retranslateUi(QDialog *pwdEditFrm)
    {
        pwdEditFrm->setWindowTitle(QCoreApplication::translate("pwdEditFrm", "\320\222\320\262\320\276\320\264 \320\275\320\276\320\260\320\276\320\263\320\276 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        labelPwd->setText(QCoreApplication::translate("pwdEditFrm", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelPwd2->setText(QCoreApplication::translate("pwdEditFrm", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pwdEditFrm: public Ui_pwdEditFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWDEDITFRM_H
