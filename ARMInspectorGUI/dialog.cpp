/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   dialog.cpp
 * Author: kazun
 *
 * Created on 29 марта 2021 г., 20:44
 */

#include "dialog.h"
#include "ui_dialog.h"
#include "userForm.h"

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}

Ui::dialog* Dialog::getUI() {
    return ui;
}

void Dialog::on_pushButton_deleteUser_clicked() {
    //Question MessageBox

    QMessageBox::question(this, "Удаление пользователя", "Вы действительно хотите удалить пользователя? ",
            QMessageBox::Yes | QMessageBox::No);
}

void Dialog::on_pushButton_addUser_clicked() {
    QMessageBox::information(this, "Добавление нового пользовтеля", "Добавление нового пользовтеля");
}

void Dialog::on_pushButton_editUser_clicked() {
                        //QMessageBox::information(0, "Список инспекций", "Список инспекций");
                        for (auto& t : inspections_) {
                            //qInfo() << "name" << t.getName();
                        }

    userForm frm;
    if (frm.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Редактирование пользовтеля", " Редактирование пользовтеля");
    }

}

void Dialog::listInspection(const QList<Inspection>& inspections){
    inspections_=inspections;
       // QMessageBox::information(this, "Список инспекций", "Список Инспекций");
    }
