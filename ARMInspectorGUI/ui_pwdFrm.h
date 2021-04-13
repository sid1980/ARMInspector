/********************************************************************************
** Form generated from reading UI file 'pwdFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWDFRM_H
#define UI_PWDFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pwdFrm
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *labelPwd;
    QLineEdit *lineEditPwd;
    QLabel *labelPwd2;
    QLineEdit *lineEditPwd2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *pwdFrm)
    {
        if (pwdFrm->objectName().isEmpty())
            pwdFrm->setObjectName(QString::fromUtf8("pwdFrm"));
        pwdFrm->setWindowModality(Qt::WindowModal);
        pwdFrm->resize(400, 252);
        widget = new QWidget(pwdFrm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 351, 191));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelPwd = new QLabel(widget);
        labelPwd->setObjectName(QString::fromUtf8("labelPwd"));
        labelPwd->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(labelPwd, 0, 0, 1, 1);

        lineEditPwd = new QLineEdit(widget);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));

        gridLayout->addWidget(lineEditPwd, 0, 1, 1, 1);

        labelPwd2 = new QLabel(widget);
        labelPwd2->setObjectName(QString::fromUtf8("labelPwd2"));

        gridLayout->addWidget(labelPwd2, 1, 0, 1, 1);

        lineEditPwd2 = new QLineEdit(widget);
        lineEditPwd2->setObjectName(QString::fromUtf8("lineEditPwd2"));

        gridLayout->addWidget(lineEditPwd2, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(pwdFrm);
        QObject::connect(buttonBox, SIGNAL(accepted()), pwdFrm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), pwdFrm, SLOT(reject()));

        QMetaObject::connectSlotsByName(pwdFrm);
    } // setupUi

    void retranslateUi(QDialog *pwdFrm)
    {
        pwdFrm->setWindowTitle(QCoreApplication::translate("pwdFrm", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelPwd->setText(QCoreApplication::translate("pwdFrm", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelPwd2->setText(QCoreApplication::translate("pwdFrm", "\320\237\320\260\321\200\320\276\320\273\321\214(\320\277\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pwdFrm: public Ui_pwdFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWDFRM_H
