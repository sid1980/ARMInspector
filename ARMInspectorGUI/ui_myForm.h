/********************************************************************************
 ** Form generated from reading UI file 'myForm.ui'
 **
 ** Created by: Qt User Interface Compiler version 5.15.2
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myForm {
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QLineEdit *passEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *myForm) {
        if (myForm->objectName().isEmpty())
            myForm->setObjectName(QString::fromUtf8("myForm"));
        myForm->setWindowModality(Qt::WindowModal);
        myForm->resize(400, 300);
        widget = new QWidget(myForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 56, 281, 121));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        nameEdit = new QLineEdit(widget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 2);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        passEdit = new QLineEdit(widget);
        passEdit->setObjectName(QString::fromUtf8("passEdit"));
        passEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passEdit, 1, 1, 1, 2);

        okButton = new QPushButton(widget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setToolTipDuration(-5);

        gridLayout->addWidget(okButton, 2, 1, 1, 1);

        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 2, 2, 1, 1);

        okButton->raise();
        nameEdit->raise();
        passEdit->raise();
        label->raise();
        label_2->raise();
        cancelButton->raise();

        retranslateUi(myForm);

        QMetaObject::connectSlotsByName(myForm);
    } // setupUi

    void retranslateUi(QDialog *myForm) {
        myForm->setWindowTitle(QCoreApplication::translate("myForm", "\320\220\320\240\320\234 \320\230\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200\320\260 \320\222\321\205\320\276\320\264", nullptr));
        label->setText(QCoreApplication::translate("myForm", "\320\230\320\274\321\217", nullptr));
        nameEdit->setPlaceholderText(QCoreApplication::translate("myForm", "\320\270\320\274\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("myForm", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        passEdit->setPlaceholderText(QCoreApplication::translate("myForm", "\320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        okButton->setText(QCoreApplication::translate("myForm", "\320\222\321\205\320\276\320\264", nullptr));
        cancelButton->setText(QCoreApplication::translate("myForm", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {

    class myForm : public Ui_myForm {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
