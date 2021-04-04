/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myForm.h
 * Author: kazun_as
 *
 * Created on 2 февраля 2021 г., 10:31
 */

//Форма аутентификации пользавателя

#ifndef _MYFORM_H
#define _MYFORM_H

#include "ui_myForm.h"
#include "ClientController.h"
#include <QCloseEvent>

class myForm : public QDialog {
    Q_OBJECT
public:
    explicit myForm(QWidget *parent = 0);
    virtual ~myForm();
    void initClient(ClientController *clientController);
    void initApp(QApplication *app);
    void closeEvent(QCloseEvent* ev);
public slots:
    void exit_app();
    void start_ARM();
signals:
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
private:
    Ui::myForm *widget;
    ///Контроллер клиента.
    ClientController *m_pClientController{nullptr};
    //QApplication *m_pApp;
};

#endif /* _MYFORM_H */
