/********************************************************************************
** Form generated from reading UI file 'juristFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JURISTFRM_H
#define UI_JURISTFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_juristFrm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *juristFrm)
    {
        if (juristFrm->objectName().isEmpty())
            juristFrm->setObjectName(QString::fromUtf8("juristFrm"));
        juristFrm->resize(1201, 875);
        juristFrm->setStyleSheet(QString::fromUtf8("QHeaderView {\n"
"    background-color: #fff;\n"
"    font-size:11px;\n"
"}\n"
"QHeaderView::section:horizontal {\n"
"    color: #fff;\n"
"    border-style: solid;\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                        stop: 0 #4287ff, stop: 1 #356ccc);\n"
" }\n"
"QTableView {\n"
"    border: 2px solid #3873d9;\n"
"    border-top-color: #4287ff;\n"
"    border-radius: 4px;\n"
"    background-color: #fff;\n"
"    background-image: url(:/img/other/background.png);\n"
"    gridline-color: #777;\n"
"    selection-background-color: royalblue;\n"
"    color:#333;\n"
"    font-size:11px;\n"
" }\n"
"\n"
"QScrollBar:vertical {\n"
"     background: #e4e4e4;\n"
"     border-top-right-radius: 4px;\n"
"     border-bottom-right-radius: 4px;\n"
"     width: 12px;\n"
"     margin: 0px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 1, y2: 0,\n"
"                                    stop: 0 #4287ff, stop: 1 #356cc"
                        "c);\n"
"     border-radius: 4px;\n"
"     min-height: 20px;\n"
"     margin: 0px 2px 0px 2px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }"));
        centralwidget = new QWidget(juristFrm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        juristFrm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(juristFrm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1201, 21));
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
