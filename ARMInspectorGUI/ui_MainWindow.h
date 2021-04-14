/********************************************************************************
 ** Form generated from reading UI file 'MainWindow.ui'
 **
 ** Created by: Qt User Interface Compiler version 5.15.2
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
    QAction *actionAccount;
    QAction *action;
    QAction *actionListUsers;
    QAction *actionReport;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(839, 570);
        MainWindow->setAutoFillBackground(true);
        actionAccount = new QAction(MainWindow);
        actionAccount->setObjectName(QString::fromUtf8("actionAccount"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        actionListUsers = new QAction(MainWindow);
        actionListUsers->setObjectName(QString::fromUtf8("actionListUsers"));
        actionListUsers->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../xmlParser/images/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListUsers->setIcon(icon);
        actionReport = new QAction(MainWindow);
        actionReport->setObjectName(QString::fromUtf8("actionReport"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 839, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setTearOffEnabled(false);
        menuFile->setToolTipsVisible(true);
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu->menuAction());
        menuFile->addAction(actionListUsers);
        menu->addAction(actionReport);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow) {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\320\240\320\234 \320\230\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\276\320\265 \321\200\320\260\320\261\320\276\321\207\320\265\320\265 \320\274\320\265\321\201\321\202\320\276 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAccount->setText(QCoreApplication::translate("MainWindow", "Account", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202 \320\276\320\261 \320\220\320\237", nullptr));
        actionListUsers->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271", nullptr));
#if QT_CONFIG(shortcut)
        actionListUsers->setShortcut(QCoreApplication::translate("MainWindow", "Alt+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReport->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\240\320\234 \320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\240\320\234 \320\256\321\200\320\270\321\201\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {

    class MainWindow : public Ui_MainWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
