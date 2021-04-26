/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             ВЫВОД СПИСКА ПОЛЬЗОВАТЕЛЕЙ
 **             Класс окна вывода списка пользователя -Dialog.
 **             Используются для вывода данных о пользователе списком
 **             Модель вывода UserView.
 **
 ****************************************************************************/

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
#include "QMessageBoxEx.h"

#include "ui_dialog.h"
#include "Inspection.h"
#include "User.h"
#include "userForm.h"
#include "userEditFrm.h"
#include "ModelList.h"
#include "UserView.h"
#include "pwdFrm.h"
#include <QSortFilterProxyModel>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    ///Констуктор
    explicit Dialog(QWidget *parent = 0);
    //Деструктор
    ~Dialog();
    ///Получить ссылку на виджет
    Ui::dialog* getUI();
    ///определить модель вывода данных
    void setModel(const QList<UserView>& users);
    ///заполнить форму редактирования пользователя
    void fillUserEditFrm(const User& user);
    ///вывести на экран  окно списка пользователей
    void showBox();
private slots:
    ///обработчик кнопки добавления пользователя
    void on_pushButton_addUser_clicked();
    ///обработчик кнопки редактирования пользователя
    void on_pushButton_editUser_clicked();
    ///обработчик кнопки удаления  пользователя
    void on_pushButton_deleteUser_clicked();
    ///обработчик кнопки удаления  пользователя
    void on_pushButton_changePassword_clicked();
public slots:
    //void listInspection(const QList<Inspection>& inspections);
    ///показать данные о новом пользователе в  окне списка пользователей
    void showNewUserData(const User&);
    ///показать отредактированные данные о  пользователе в  окне списка пользователей
    void showEditUserData(const User&);
signals:
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();

    ///заменить пароль пользователя
    void setPwd(const User&);
    ///пользователе подготовлены и необходимо их передать на сервер
    void addUser(const User&);
    ///сигнализировать  о  готовности передать на сервер отредактированные 
    ///данные  выбранного  пользователя
    void updateUser(const User&);
    ///сигнализировать  о  необходимости получить от сервера данные о
    ///пользователе
    void getUserData(const qint64&);
    ///сигнализировать  о  необходимости удалить на сервере данные о
    ///пользователе
    void deleteUser(const qint64&);
    ///Запросить список инспекций
    void getInspections();
    ///сигнализировать  о  необходимости  ожидания ответа от сервера 
    ///с результатом предыдущей операции
    void waitServer();
public slots:
    ///Инициализировать список инспекций
    void setListInspections(const QList<Inspection>&);

private:
    ///ссылка на виджет основного окна
    Ui::dialog *ui;
    ///ссылка на окно ввоода нового пользователя
    userForm *usrFrm_;
    ///ссылка на окно ввоода нового пароля
    pwdFrm *pwdFrm_;
    ///ссылка на окно релактирования выбранного пользователя
    userEditFrm *usrEdtFrm_;
    ///ссылка на модель  данных 
    ModelList<UserView>* listusers_;
    ///ссылк на экземпляр модели вывода данных
    UserView *userview_;
    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;
};

#endif // DIALOG_H
