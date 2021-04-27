/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainWindow.cpp
 * Author: kazun_as
 *
 * Created on 5 февраля 2021 г., 10:26
 */

#include "MainWindow.h"
#include "Report/reportFrm.h"
#include <QStandardItemModel>
#include <QScrollBar>

MainWindow::MainWindow() {
    widget.setupUi(this);
    connect(this->widget.actionListUsers, SIGNAL(triggered()), this, SLOT(ListUsers()));
    connect(this->widget.actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));

}

MainWindow::~MainWindow() {
}



///-----------------------------------------------------------------------------
///
///         Список пользователей.
///          
///-----------------------------------------------------------------------------

void MainWindow::ListUsers() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    m_pClientController->getListModels(ModelWrapper::Model::UserView);

}

///-----------------------------------------------------------------------------
///
///         Список пользователей.
///          
///-----------------------------------------------------------------------------

void MainWindow::OnExit() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    QMessageBoxEx::StandardButton reply;
    reply = QMessageBoxEx::question(this, "Завершение работы АРМ Инспектор",
            "Вы действительно хотите завершить работу ? ",
            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        qApp->quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}


///-----------------------------------------------------------------------------
///
///         initClient
///          
///-----------------------------------------------------------------------------

void MainWindow::initClient(ClientController * clientController) {
    m_pClientController = clientController;

};



