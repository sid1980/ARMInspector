/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **
 **            Класс обработки сообщений от сервера. 
 **            Обрабатывает сообщения от сервера  и передает управление
 **            с помощью сигнально-слотового соединения контоллеру клиента или  
 **            новому окну ввода данных или окну сообщения или вызывает 
 **            дополнительные модули обработки данных.
 **             
 **
 ****************************************************************************/


/* 
 * File:   WorkerClient.cpp
 * Author: ASK
 * 
 * Created on 14 декабря 2019 г., 19:50
 */

#include "WorkerClient.h"
#include <QMessageBox>
#include <QTableView>
#include "dialog.h"
/// Стандартный конструктор.
/// @param apParent Родитель.

WorkerClient::WorkerClient(QObject *apParent) : QObject(apParent) {
    dialog_ = new Dialog();
    connect(dialog_, SIGNAL(addUser(const User&)), this, SIGNAL(addUser(const User&)));
    connect(dialog_, SIGNAL(updateUser(const User&)), this, SIGNAL(updateUser(const User&)));
    connect(dialog_, SIGNAL(getUserData(const qint64&)), this, SIGNAL(getUserData(const qint64&)));
    connect(dialog_, SIGNAL(deleteUser(const qint64&)), this, SIGNAL(deleteUser(const qint64&)));
    connect(dialog_, SIGNAL(waitServer()), this, SIGNAL(waitServer()));
}

///Деструктор.

WorkerClient::~WorkerClient() {
    //Освободить  ресурсы
    delete dialog_;
}
/// Инициализировать строку командной обёртки.
/// @param asWrapperString Строка инициализации командной обёртки

void WorkerClient::setModelWrapperString(const QString& asWrapperString) {
    m_aModelWrapperString = asWrapperString;
}


/// Получить строку командной обёртки.
/// @return Возвращает строку командной обёртки.

const QString& WorkerClient::getModelWrapperString() const {
    return m_aModelWrapperString;
}



///Основная функция обработчика сообщений, полученных от сервера.

void WorkerClient::process() {
    //QMessageBox::information(0, "Добавление нового пользовтеля", "Пользователь успешно добавлен в базу данных");
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(m_aModelWrapperString, wrapper);
    //Вывести заголовок и сообщение.
    qInfo() << "head: " << QString::fromLocal8Bit(wrapper.getHead().toStdString().c_str());
    qInfo() << "message: " << QString::fromLocal8Bit(wrapper.getMessage().toStdString().c_str());
    //Проверяем результат выполнения команды 
    ModelWrapper::Command command = wrapper.getEnumCommand();
    if (wrapper.getSuccess()) {
        //Команда на сервере выполнена успешно.Определяем тип возвращённой команды.
        switch (command) {
            case ModelWrapper::Command::GET_LIST_MODELS:
            {
                //Сервер вернул результат команды "GET_LIST_MODELS"  
                //Процесс обработки возвращённого реультата.    

                ModelWrapper::Model model = wrapper.getEnumModel();
                switch (model) {
                    case ModelWrapper::Model::Inspection:
                    {
                        ItemContainer<Inspection> inspectionContainer;
                        JsonSerializer::parse(wrapper.getData(), inspectionContainer);
                        QList<Inspection> inspections = inspectionContainer.getItemsList();
                        dialog_->setListInspection(inspections);
                        dialog_->showBox();
                    }
                        break;
                    case ModelWrapper::Model::UserView:
                    {
                        //QMessageBox::information(0, "Information Box", "This is information text");
                        ItemContainer<UserView> userContainer;
                        JsonSerializer::parse(wrapper.getData(), userContainer);
                        dialog_->setModel(userContainer.getItemsList());
                        //dialog_->getUI()->tableView->setModel(new ModelList<UserView>(userContainer.getItemsList()));
                        emit getInspections();
                    }
                        break;
                }
            }
                break;
            case ModelWrapper::Command::LOGIN:
            {
                //Сервер вернул результат команды "LOGIN"     
                //Процесс обработки возвращённого реультата.    
                User user;
                JsonSerializer::parse(wrapper.getData(), user);
                //MessageBox::information(0, "LOGIN",
                //        "User with name " + user.getName().trimmed() + " is logged in");
                qInfo() << "User with name " << user.getName().trimmed() << " is logged in";
                //Сигнализировать о завершении обработки.
                emit ready();
            }
                break;
            case ModelWrapper::Command::ADD_NEW_USER:
            {
                //Сервер вернул результат команды "ADD_NEW_USER"     
                //Процесс обработки возвращённого реультата.  
                //connect(this, SIGNAL(readyUserData(const User&)),
                //        dialog_, SLOT(showUserData(const User&)));
                User user;
                JsonSerializer::parse(wrapper.getData(), user);
                
                dialog_->showNewUserData(user);
                //emit readyUserData(user);
                emit ready();

            }
                break;
            case ModelWrapper::Command::EDIT_USER:
            {
                //Сервер вернул результат команды "EDIT_USER"     
                User user;
                JsonSerializer::parse(wrapper.getData(), user);

                //dialog_->showUserData(user);
                //emit readyUserData(user);
                QMessageBox::information(0, "Редактирование пользовтеля",
                        "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> успешно отредактирован");
                dialog_->showEditUserData(user);
                emit ready();

            }
                break;
            case ModelWrapper::Command::GET_MODEL:
            {
                //Сервер вернул результат команды "GET_MODEL"     
                ModelWrapper::Model model = wrapper.getEnumModel();
                switch (model) {
                    case ModelWrapper::Model::User:
                    {
                        User user;
                        JsonSerializer::parse(wrapper.getData(), user);
                        //emit dialog_->showUserData(user);
                        //QMessageBox::information(0, "Получение данных о пользователе",
                        //        "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> ");
                        dialog_->fillUserEditFrm(user);
                        emit ready();

                    }
                        break;

                }
            }
                break;
            case ModelWrapper::Command::DEL_MODEL:
            {
                //Сервер вернул результат команды "GET_MODEL"     
                ModelWrapper::Model model = wrapper.getEnumModel();
                switch (model) {
                    case ModelWrapper::Model::User:
                    {
                        User user;
                        JsonSerializer::parse(wrapper.getData(), user);
                        //emit dialog_->showUserData(user);
                        QMessageBox::information(0, "Удаление  пользователя",
                                "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a>  успешно удален");
                        emit ready();

                    }
                        break;

                }
            }
                break;

            case ModelWrapper::Command::NOP:
            {
                qInfo() << "Command is incorrect";

            }
                break;
            case ModelWrapper::Command::SERVER_RESPONSE:
            {

                qInfo() << "Уведомление от сервера";

            }
                break;
            case ModelWrapper::Command::SET_SESSION_ID:
            {
                ///Сообщить контроллеру клиента о небходимости
                //установить ID сессии
                emit setID(wrapper.getSessionID());
            }
                break;
        }
    } else {
        switch (command) {
            case ModelWrapper::Command::LOGIN:
            {
                QMessageBox msgBox;
                msgBox.setText("<a style='color:royalblue'> Вы ввели данные правильно? (Нет. Попробуйте ещё раз.)</a>");
                msgBox.exec();
            }
                break;
            case ModelWrapper::Command::ADD_NEW_USER:
            {
                QMessageBox msgBox;
                msgBox.setText("<a style='color:red'> Ошибка добавления нового пользователя</a>");
                msgBox.exec();
            }
                break;
            case ModelWrapper::Command::GET_LIST_MODELS:
            {
                QMessageBox::information(0, "СПИСОК МОДЕЛЕЙ", "Список моделей");
                qInfo() << "Список моделей";
            }
                break;
            case ModelWrapper::Command::NOP:
            {

            }
                break;
        }

    }
}



