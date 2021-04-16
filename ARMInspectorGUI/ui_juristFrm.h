/********************************************************************************
** Form generated from reading UI file 'juristFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JURISTFRM_H
#define UI_JURISTFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_juristFrm
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *juristFrm)
    {
        if (juristFrm->objectName().isEmpty())
            juristFrm->setObjectName(QString::fromUtf8("juristFrm"));
        juristFrm->resize(800, 600);
        centralwidget = new QWidget(juristFrm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        juristFrm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(juristFrm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        juristFrm->setMenuBar(menubar);
        statusbar = new QStatusBar(juristFrm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        juristFrm->setStatusBar(statusbar);

        retranslateUi(juristFrm);

        QMetaObject::connectSlotsByName(juristFrm);
    } // setupUi

    void retranslateUi(QMainWindow *juristFrm)
    {
        juristFrm->setWindowTitle(QCoreApplication::translate("juristFrm", "juristFrm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class juristFrm: public Ui_juristFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JURISTFRM_H
