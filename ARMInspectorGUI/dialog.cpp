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
#include "UserV1.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QComboBox>
#include <QPalette>
#include <QColor>
#include <QString>
#include <string>

///Констуктор

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::dialog) {
    ui->setupUi(this);
    usrFrm_ = new userForm(this);
    user_ = new UserV1();
    listusers_ = new ModelList<UserV1>();
    //const QColor hlClr = Qt::red; // highlight color to set
    //const QColor txtClr = Qt::white; // highlighted text color to set

    //QPalette p = palette();
    //p.setColor(QPalette::Highlight, hlClr);
    //p.setColor(QPalette::HighlightedText, txtClr);
    //setPalette(p);
    this->getUI()->tableView->setStyleSheet("QTableView::item:selected { color:white; background:#0000ff; font-weight:900; }"
            "QTableCornerButton::section { background-color:#232326; }"
            "QHeaderView::section { color:white; background-color:#232326; }");
}

///Деструктор

Dialog::~Dialog() {
    delete ui;
    delete usrFrm_;
    delete user_;
    delete listusers_;
}

Ui::dialog* Dialog::getUI() {
    return ui;
}

void Dialog::on_pushButton_deleteUser_clicked() {
    //Question MessageBox

    QMessageBox::question(this, "Удаление пользователя", "Вы действительно хотите удалить пользователя? ",
            QMessageBox::Yes | QMessageBox::No);

}


///Показать строку данных о пользователе на экране

void Dialog::showUserData(const User& user) {
    //table2->selectRow(current.row());
    this->getUI()->tableView->scrollToBottom();
    this->getUI()->tableView->selectRow(listusers_->rowCount() - 1);
    QMessageBox::information(this, "Добавление нового пользовтеля",
            "Пользователь" + user.getFio() + " успешно добавлен в базу данных");
}

///Инициализировать список инспекций

void Dialog::setListInspection(const QList<Inspection>& inspections) {
    usrFrm_->setInspections(inspections);
};

///Установить модель списка пользователей

void Dialog::setModel(const QList<UserV1>& users) {
    listusers_->setListModel(users);
    this->getUI()->tableView->setModel(listusers_);
}

///Показать диалог списка организаци1

void Dialog::showBox() {
    this->getUI()->tableView->setColumnHidden(0, true);
    //this->getUI()->tableView->setColumnHidden(4, true);
    //this->getUI()->tableView->setColumnHidden(5, true);
    //this->getUI()->tableView->setColumnHidden(6, true);
    //this->getUI()->tableView->setColumnHidden(7, true);
    //this->getUI()->tableView->setColumnHidden(8, true);
    //this->getUI()->tableView->setColumnHidden(9, true);
    //dialog_.getUI()->tableView->setColumnHidden(2, true);
    this->getUI()->tableView->resizeColumnsToContents();
    this->getUI()->tableView->resizeRowsToContents();
    //emit passListInspections(inspections_);
    this->show();

}
///Обработка нажатия кнопки добавления  пользователя.
///Данные считываются из формы данных пользователя,
///добавляются в Модель отображения данных на экране и 
///и в Модель передачи данных на сервер.
///Для передачи данных на сервер диалог пользуется 
///сигналом readyUserData.

void Dialog::on_pushButton_addUser_clicked() {
    if (usrFrm_->exec() == QDialog::Accepted) {
        User* user = new User();
        user->setFio(usrFrm_->getWidget()->lineEditFio->text());
        user->setInspection(usrFrm_->getInspections()[usrFrm_->getWidget()->comboBoxInspection->currentIndex()].getId());
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
        //QMessageBox::information(this, "Добавление нового пользовтеля",
        //        QString::number(user->getInspection()));
        emit readyUserData(*user);
        user_->setFio(user->getFio());
        user_->setName(user->getName());
        user_->setInspection(usrFrm_->getInspections()[usrFrm_->getWidget()->comboBoxInspection->currentIndex()].getName());
        listusers_->addModel(*user_);
        delete user;
    }
}



///Обработка нажатия кнопки редактирования пользователя

void Dialog::on_pushButton_editUser_clicked() {
    //QMessageBox::information(0, "Список инспекций", "pushButton_editUser_clicked");
    //QMessageBox::information(0, "Список инспекций", inspections_[0].getName());
    qDebug() << "pushButton_editUser_clicked";

    QModelIndexList selection = this->getUI()->tableView->selectionModel()->selectedRows();

    //Multiple rows can be selected
    //QModelIndexList indexList = this->getUI()->tableView->selectionModel()->selectedIndexes();
    

    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    QModelIndexList indexes = select->selection().indexes();
    ///Перебрать все ячейки строки
    for (int i = 0; i < indexes.count(); ++i) {
        //select->model()->index(rowidx, i).data()
        //        QMessageBox::information(this, "", select->model()->index(rowidx, i).data().toString());
        //std::string stdstr = select->model()->index(rowidx, i).data().toString().toUtf8().constData();
        //qInfo() << QString::fromLocal8Bit(stdstr.c_str());
        qInfo() << QString::fromLocal8Bit(select->model()->index(rowidx, i).data().toString().toUtf8().constData());
    }
}



//void Dialog::setListInspection(const QList<Inspection>& inspections) {
//    inspections_ = inspections;
//    for (auto& t : inspections_) {
//qInfo() << "name" << t.getName();
//        usrFrm_->getWidget()->comboBoxInspection->addItem(t.getName());
//    }

// QMessageBox::information(this, "Список инспекций", "Список Инспекций");
//}
