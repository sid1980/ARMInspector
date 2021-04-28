/********************************************************************************
** Form generated from reading UI file 'nsiEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSIEDITFORM_H
#define UI_NSIEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_nsiEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelName;
    QLineEdit *lineEditName;

    void setupUi(QDialog *nsiEditForm)
    {
        if (nsiEditForm->objectName().isEmpty())
            nsiEditForm->setObjectName(QString::fromUtf8("nsiEditForm"));
        nsiEditForm->resize(400, 154);
        buttonBox = new QDialogButtonBox(nsiEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 90, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelName = new QLabel(nsiEditForm);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(30, 50, 47, 13));
        lineEditName = new QLineEdit(nsiEditForm);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(130, 50, 211, 20));

        retranslateUi(nsiEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), nsiEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), nsiEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(nsiEditForm);
    } // setupUi

    void retranslateUi(QDialog *nsiEditForm)
    {
        nsiEditForm->setWindowTitle(QCoreApplication::translate("nsiEditForm", "nsiEditForm", nullptr));
        labelName->setText(QCoreApplication::translate("nsiEditForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nsiEditForm: public Ui_nsiEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSIEDITFORM_H
