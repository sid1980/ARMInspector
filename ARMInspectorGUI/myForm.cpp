/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   myForm.cpp
 * Author: kazun_as
 *
 * Created on 2 февраля 2021 г., 10:31
 */

#include "myForm.h"
#include <QMessageBox>

myForm::myForm(QWidget *parent) :
QDialog(parent),widget(new Ui::myForm) {
    widget->setupUi(this);
    //widget.setupUi(this);
    connect(widget->okButton, SIGNAL(clicked()), this, SLOT(start_ARM()));
    connect(widget->cancelButton, SIGNAL(clicked()), this, SLOT(exit_app()));
}

myForm::~myForm() {
        delete widget;
}

void myForm::closeEvent(QCloseEvent* ev) {
    //    m_pApp->quit();
    qApp->quit();

}

void myForm::exit_app() {
    //QPushButton *button =widget.okButton;
    //this->hide();
    //m_pApp->quit();
    qApp->quit();
    //exit(0);
}

void myForm::start_ARM() {
    //QPushButton *button =widget.okButton;
    m_pClientController->login(this->widget->nameEdit->text(), this->widget->passEdit->text());
    //m_pClientController->execSqlquery("Select * from user", ModelWrapper::Model::User);

    //this->hide();
    //emit ready();
    //return;
}

//void myForm::initApp(QApplication *app) {
//    m_pApp = app;
//
//}

void myForm::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    // Сигнально-слотовое соединение, сигнализирующее, что   контроллер комманд
    // готов вернуть  результат  выполнения запроса к серверу.
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));

};
