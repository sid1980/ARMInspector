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

//Форма вывода списка пользователей



#include "dialog.h"
#include "User.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QComboBox>

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::dialog) {
    ui->setupUi(this);
    usrFrm_ = new userForm(this);

}

Dialog::~Dialog() {
    delete ui;
    delete usrFrm_;
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
    if (usrFrm_->exec() == QDialog::Accepted) {
        User* user = new User();
        user->setFio(usrFrm_->getWidget()->lineEditFio->text());
        user->setInspection(inspections_[usrFrm_->getWidget()->comboBoxInspection->currentIndex()].getId());
        user->setName(usrFrm_->getWidget()->lineEditName->text());
        user->setPassword(usrFrm_->getWidget()->lineEditPassword->text());
        QButtonGroup group;
        QList<QRadioButton *> allButtons;
        allButtons = usrFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
        for (int i = 0; i < allButtons.size(); ++i) {
            group.addButton(allButtons[i], i);
        }
        user->setStatus(group.checkedId());
        
        allButtons = usrFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
        for (int i = 0; i < allButtons.size(); ++i) {
            group.addButton(allButtons[i], i);
        }
        user->setRole(group.checkedId());
        QMessageBox::information(this, "Добавление нового пользовтеля", QString::number(user->getRole()));
        delete user;
    }
}

void Dialog::on_pushButton_editUser_clicked() {
    //QMessageBox::information(0, "Список инспекций", "Список инспекций");
    //QMessageBox::information(0, "Список инспекций", inspections_[0].getName());




}

void Dialog::listInspection(const QList<Inspection>& inspections) {
    inspections_ = inspections;
    //QMessageBox::information(0, "Список инспекций", inspections_[0].getName());
    // QMessageBox::information(this, "Список инспекций", "Список Инспекций");
}

void Dialog::setListInspection(const QList<Inspection>& inspections) {
    inspections_ = inspections;
    for (auto& t : inspections_) {
        //qInfo() << "name" << t.getName();
        usrFrm_->getWidget()->comboBoxInspection->addItem(t.getName());
    }

    // QMessageBox::information(this, "Список инспекций", "Список Инспекций");
}
