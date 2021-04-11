/* * To change this license header, coose License Headers in Project Properties.
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
#include "UserView.h"
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
    usrEdtFrm_ = new userEditFrm(this);
    userview_ = new UserView();
    listusers_ = new ModelList<UserView>();
    proxyModel_ = new QSortFilterProxyModel(listusers_);
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
    delete usrEdtFrm_;
    delete userview_;
    delete listusers_;
    delete proxyModel_;
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
    userview_->setId(user.getId());
    userview_->setFio(user.getFio());
    userview_->setName(user.getName());
    userview_->setInspection(usrFrm_->getInspections()[user.getInspection()].getName());
    listusers_->addModel(*userview_);
    this->getUI()->tableView->scrollToBottom();
    this->getUI()->tableView->selectRow(listusers_->rowCount() - 1);
    //    QMessageBox::information(this, "Добавление нового пользовтеля",
    //            "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> успешно добавлен в базу данных");
}

//Заполнить форму редактирования пользователя его данными

void Dialog::fillUserEditFrm(const User& user) {
    usrEdtFrm_->getWidget()->lineEditFio->setText(user.getFio());
    for (int i = 0; i < usrEdtFrm_->getInspections().size(); i++) {
        if (usrEdtFrm_->getInspections()[i].getId() == user.getInspection()) {
            usrEdtFrm_->getWidget()->comboBoxInspection->setCurrentIndex(i);
            break;
        }
    }
    usrEdtFrm_->getWidget()->lineEditName->setText(user.getName());
    QList<QRadioButton *> allButtons;
    allButtons = usrEdtFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
    for (int i = 1; i <= allButtons.size(); ++i) {
        if (i == user.getStatus()) {
            allButtons[i - 1]->setChecked(true);
        }
    }
    allButtons = usrEdtFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
    for (int i = 1; i <= allButtons.size(); ++i) {
        if (i == user.getRole()) {
            allButtons[i - 1]->setChecked(true);
        }
    }


}


///Инициализировать список инспекций

void Dialog::setListInspection(const QList<Inspection>& inspections) {
    usrFrm_->setInspections(inspections);
    usrEdtFrm_->setInspections(inspections);
};

///Установить модель списка пользователей

void Dialog::setModel(const QList<UserView>& users) {
    listusers_->setListModel(users);
    //this->getUI()->tableView->setModel(listusers_);
    ///Разрешить сортировку по столбцам
    //QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(listusers_); // create proxy
    proxyModel_->setSourceModel(listusers_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
}

///Показать диалог списка организаций

void Dialog::showBox() {
    this->getUI()->tableView->setColumnHidden(0, true);
    this->getUI()->tableView->resizeColumnsToContents();
    this->getUI()->tableView->resizeRowsToContents();
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

        ///Получить значение RadioBox
        QButtonGroup group;
        QList<QRadioButton *> allButtons;
        allButtons = usrFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
        for (int i = 1; i <= allButtons.size(); ++i) {
            group.addButton(allButtons[i - 1], i);
        }
        user->setStatus(group.checkedId());

        allButtons = usrFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
        for (int i = 1; i < allButtons.size(); ++i) {
            group.addButton(allButtons[i - 1], i);
        }
        user->setRole(group.checkedId());
        //QMessageBox::information(this, "Добавление нового пользовтеля",
        //        QString::number(user->getInspection()));
        //proxyModel_->setSourceModel(listusers_);

        emit addUser(*user);
        emit waitServer();
        //this->showUserData(*user);
        delete user;

    }
}


///Обработка нажатия кнопки редактирования пользователя

void Dialog::on_pushButton_editUser_clicked() {
    //QMessageBox::information(0, "Список инспекций", "pushButton_editUser_clicked");
    //QMessageBox::information(0, "Список инспекций", inspections_[0].getName());
    qDebug() << "pushButton_editUser_clicked";
    //QModelIndexList selection = this->getUI()->tableView->selectionModel()->selectedRows();

    //Multiple rows can be selected
    //QModelIndexList indexList = this->getUI()->tableView->selectionModel()->selectedIndexes();


    //QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    ///int rowidx = select->currentIndex().row();
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        //QModelIndexList indexes = select->selection().indexes();
        //UserView user = listusers_->getModel(select->currentIndex());
        UserView user = listusers_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        //qDebug() << QString::number(user.getId());
        auto id = user.getId();
        //auto id = select->model()->index(rowidx, 0).data().toInt();
        emit getUserData(id);
        emit waitServer();
        if (usrEdtFrm_->exec() == QDialog::Accepted) {
            User* user = new User();
            user->setFio(usrEdtFrm_->getWidget()->lineEditFio->text());
            user->setInspection(usrEdtFrm_->getInspections()[usrEdtFrm_->getWidget()->comboBoxInspection->currentIndex()].getId());
            user->setName(usrEdtFrm_->getWidget()->lineEditName->text());

            ///Получить значение RadioBox
            QList<QRadioButton *> buttons;
            buttons = usrEdtFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
            for (int i = 1; i <= buttons.size(); ++i) {
                if (buttons[i - 1]->isChecked()) {
                    user->setStatus(i);
                }
            }
            buttons = usrEdtFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
            for (int i = 1; i <= buttons.size(); ++i) {
                if (buttons[i - 1]->isChecked()) {
                    user->setRole(i);
                }
            }
            //QMessageBox::information(this, "Добавление нового пользовтеля",
            //        QString::number(user->getInspection()));
            //proxyModel_->setSourceModel(listusers_);

            emit updateUser(*user);
            emit waitServer();
            //this->showUserData(*user);
            delete user;

        }

        //listusers_->record(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row());
        ///Перебрать все ячейки строки
        //    for (int i = 0; i < indexes.count(); ++i) {
        //select->model()->index(rowidx, i).data()
        //        QMessageBox::information(this, "", select->model()->index(rowidx, i).data().toString());
        //std::string stdstr = select->model()->index(rowidx, i).data().toString().toUtf8().constData();
        //qInfo() << QString::fromLocal8Bit(stdstr.c_str());
        //qDebug() << rowidx;
        //        qDebug() << QString::fromLocal8Bit(select->model()->index(rowidx, i).data().toString().toUtf8().constData());
        //    }
    }
}

