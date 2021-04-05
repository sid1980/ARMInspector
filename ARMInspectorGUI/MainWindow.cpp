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

MainWindow::MainWindow() {
    widget.setupUi(this);
    connect(this->widget.actionReport, SIGNAL(triggered()), this, SLOT(Report()));
    connect(this->widget.actionListUsers, SIGNAL(triggered()), this, SLOT(ListUsers()));
}

MainWindow::~MainWindow() {
}


///Отчёт

void MainWindow::Report() {
    QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
    //QMessageBox::critical(0, qApp->tr("Cannot open database"),
    //        qApp->tr("Unable to establish a database connection.\n"
    //        "This example needs SQLite support. Please read "
    //        "the Qt SQL driver documentation for information how "
    //        "to build it.\n\n"
    //        "Click Cancel to exit."), QMessageBox::Ok);
}


///Список пользователей

void MainWindow::ListUsers() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    m_pClientController->getListModels(ModelWrapper::Model::UserV1);

}

void MainWindow::initClient(ClientController *clientController) {
    m_pClientController = clientController;

};

