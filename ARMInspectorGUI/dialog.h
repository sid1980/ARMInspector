/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dialog.h
 * Author: kazun
 *
 * Created on 29 марта 2021 г., 20:44
 */


//Форма вывода списка пользователей

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMessageBox>

#include "ui_dialog.h"
#include "Inspection.h"
#include "User.h"
#include "userForm.h"
#include "userEditFrm.h"
#include "ModelList.h"
#include "UserView.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    //Dialog(){};
    ~Dialog();
    Ui::dialog* getUI();
    void setListInspection(const QList<Inspection>& inspections);
    void setModel(const QList<UserView>& users);
    void fillUserEdiFrm(const User& user);
    void showBox();
private slots:
    void on_pushButton_addUser_clicked();
    void on_pushButton_editUser_clicked();
    void on_pushButton_deleteUser_clicked();
public slots:
    //void listInspection(const QList<Inspection>& inspections);
    void showUserData(const User&);
signals:
    void readyUserData(const User&);
    void getUserData(const qint64&);
    void waitServer();

private:
    Ui::dialog *ui;
    userForm *usrFrm_;
    userEditFrm *usrEdtFrm_;
    ModelList<UserView>* listusers_;
    UserView *userview_;

};

#endif // DIALOG_H
