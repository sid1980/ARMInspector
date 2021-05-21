/********************************************************************************
** Form generated from reading UI file 'myProgressBar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPROGRESSBAR_H
#define UI_MYPROGRESSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_myProgressBar
{
public:
    QProgressBar *progressBar;

    void setupUi(QDialog *myProgressBar)
    {
        if (myProgressBar->objectName().isEmpty())
            myProgressBar->setObjectName(QString::fromUtf8("myProgressBar"));
        myProgressBar->resize(400, 94);
        progressBar = new QProgressBar(myProgressBar);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 30, 311, 23));
        progressBar->setValue(24);

        retranslateUi(myProgressBar);

        QMetaObject::connectSlotsByName(myProgressBar);
    } // setupUi

    void retranslateUi(QDialog *myProgressBar)
    {
        myProgressBar->setWindowTitle(QCoreApplication::translate("myProgressBar", "myProgressBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myProgressBar: public Ui_myProgressBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPROGRESSBAR_H
