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
#include "userForm.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    Ui::dialog* getUI();
    void setListInspection(const QList<Inspection>& inspections);

private slots:

    void on_pushButton_addUser_clicked();
    void on_pushButton_editUser_clicked();
    void on_pushButton_deleteUser_clicked();
public slots:
    void listInspection(const QList<Inspection>& inspections);

private:
    Ui::dialog *ui;
    userForm *usrFrm_;
    QList<Inspection> inspections_;
};

#endif // DIALOG_H
