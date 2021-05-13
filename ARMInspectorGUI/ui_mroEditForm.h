/********************************************************************************
** Form generated from reading UI file 'mroEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MROEDITFORM_H
#define UI_MROEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_mroEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelName;
    QLineEdit *lineEditName;

    void setupUi(QDialog *mroEditForm)
    {
        if (mroEditForm->objectName().isEmpty())
            mroEditForm->setObjectName(QString::fromUtf8("mroEditForm"));
        mroEditForm->resize(400, 185);
        buttonBox = new QDialogButtonBox(mroEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 100, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelName = new QLabel(mroEditForm);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(10, 60, 47, 13));
        lineEditName = new QLineEdit(mroEditForm);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(110, 60, 211, 20));

        retranslateUi(mroEditForm);

        QMetaObject::connectSlotsByName(mroEditForm);
    } // setupUi

    void retranslateUi(QDialog *mroEditForm)
    {
        mroEditForm->setWindowTitle(QCoreApplication::translate("mroEditForm", "mroEditForm", nullptr));
        labelName->setText(QCoreApplication::translate("mroEditForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mroEditForm: public Ui_mroEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MROEDITFORM_H
