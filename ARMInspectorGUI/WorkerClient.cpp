/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **            ОБРАБОТЧИК СООБЩЕНИЙ СЕРВЕРА 
 **            Класс обработки сообщений  сервера. 
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
#include "QMessageBoxEx.h"
#include <QTableView>
#include "User/dialog.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

WorkerClient::WorkerClient(QObject *apParent) : QObject(apParent) {
}

///-----------------------------------------------------------------------------
///
///         Деструктор
///          
///-----------------------------------------------------------------------------

WorkerClient::~WorkerClient() {
    //Освободить  ресурсы

}
///-----------------------------------------------------------------------------
///
///            Инициализировать строку командной обёртки.
///            @param asWrapperString Строка инициализации командной обёртки
///          
///-----------------------------------------------------------------------------

void WorkerClient::setModelWrapperString(const QString& asWrapperString) {

    m_aModelWrapperString = asWrapperString;
}

///-----------------------------------------------------------------------------
///
///          Получить строку командной обёртки.
///          @return Возвращает строку командной обёртки.
///          
///-----------------------------------------------------------------------------

const QString& WorkerClient::getModelWrapperString() const {

    return m_aModelWrapperString;
}



///-----------------------------------------------------------------------------
///
///         Основная функция обработчики сообщений, полученных от сервера.
///          
///-----------------------------------------------------------------------------

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
    ModelWrapper::Model model = wrapper.getEnumModel();
    QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
    QMessageBoxEx::setCustomTextForButton(QMessageBox::No, "Нет");
    if (wrapper.getSuccess()) {
        //*******************************************************************************************************************************************
        //                                  Команда на сервере выполнена успешно.
        //*******************************************************************************************************************************************
        switch (command) {
            case ModelWrapper::Command::GET_LIST_MODELS:
                ///-----------------------------------------------------------------------------
                ///
                ///                         GET_LIST_MODELS
                ///          
                ///-----------------------------------------------------------------------------
                //Сервер вернул результат команды "GET_LIST_MODELS"  
                //Процесс обработки возвращённого реультата.    

                switch (model) {
                    case ModelWrapper::Model::Mro:
                    {
                        ItemContainer<Mro> mroContainer;
                        JsonSerializer::parse(wrapper.getData(), mroContainer);
                        QList<Mro> mro = mroContainer.getItemsList();
                        //QMessageBox::information(0, "Information Box", inspections[1].getName());
                        emit listMroReady(mro);

                    }
                        break;
                    case ModelWrapper::Model::Nsi:
                    {
                        ItemContainer<Nsi> nsiContainer;
                        JsonSerializer::parse(wrapper.getData(), nsiContainer);
                        QList<Nsi> nsi = nsiContainer.getItemsList();
                        //QMessageBox::information(0, "Information Box", nsi[1].getName());
                        emit listNsiReady(nsi);

                    }
                        break;
                    case ModelWrapper::Model::Inspection:
                    {
                        ItemContainer<Inspection> inspectionContainer;
                        JsonSerializer::parse(wrapper.getData(), inspectionContainer);
                        QList<Inspection> inspections = inspectionContainer.getItemsList();
                        //QMessageBox::information(0, "Information Box", inspections[1].getName());
                        emit listInspectionsReady(inspections);

                    }
                        break;
                    case ModelWrapper::Model::UserView:
                    {
                        //QMessageBox::information(0, "Information Box", "This is information text");
                        ItemContainer<UserView> userContainer;
                        JsonSerializer::parse(wrapper.getData(), userContainer);
                        QList<UserView> users = userContainer.getItemsList();
                        emit listUserReady(users);
                        //dialog_->setModel(userContainer.getItemsList());
                        //dialog_->getUI()->tableView->setModel(new ModelList<UserView>(userContainer.getItemsList()));
                        //dialog_->showBox();

                    }
                        break;
                }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         LOGIN
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::LOGIN:
            {
                //Сервер вернул результат команды "LOGIN"     
                //Процесс обработки возвращённого реультата.    
                User user;
                JsonSerializer::parse(wrapper.getData(), user);
                emit setSessionUser(user);
                //MessageBox::information(0, "LOGIN",
                //        "User with name " + user.getName().trimmed() + " is logged in");
                qInfo() << "User with name " << user.getName().trimmed() << " is logged in";
                //Сигнализировать о завершении обработки.
                emit ready();
            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         ADD_NEW_USER
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::ADD_NEW_USER:
            {
                //Сервер вернул результат команды "ADD_NEW_USER"     
                //Процесс обработки возвращённого реультата.  
                //connect(this, SIGNAL(readyUserData(const User&)),
                //        dialog_, SLOT(showUserData(const User&)));
                //User user;
                //JsonSerializer::parse(wrapper.getData(), user);

                //dialog_->showNewUserData(user);
                emit responseServer(wrapper.getData());
                //emit readyUserData(user);
                //emit ready();

            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         EDIT_USER
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::EDIT_USER:
            {
                //Сервер вернул результат команды "EDIT_USER"     
                User user;
                JsonSerializer::parse(wrapper.getData(), user);

                //dialog_->showUserData(user);
                //emit readyUserData(user);
                QMessageBox::information(0, "Редактирование пользовтеля",
                        "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> успешно отредактирован");
                //dialog_->showEditUserData(user);
                emit ready();

            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         CHANGE_PASSWORD
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::CHANGE_PASSWORD:
            {
                //Сервер вернул результат команды "EDIT_USER"     
                User user;
                JsonSerializer::parse(wrapper.getData(), user);

                //dialog_->showUserData(user);
                //emit readyUserData(user);
                QMessageBox::information(0, wrapper.getHead(), wrapper.getMessage() +
                        QString(":<br><br> <a style='font-size:14px;color:royalblue'> ") + user.getName() + QString("</a>"));
                //QMessageBox::information(0, "Редактирование пользовтеля",
                //        "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> успешно отредактирован");
                //dialog_->showEditUserData(user);
                emit ready();

            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         GET_MODEL
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::GET_MODEL:
            {
                //Сервер вернул результат команды "GET_MODEL"     
                switch (model) {
                    case ModelWrapper::Model::User:
                    {
                        User user;
                        JsonSerializer::parse(wrapper.getData(), user);
                        //emit dialog_->showUserData(user);
                        //QMessageBox::information(0, "Получение данных о пользователе",
                        //        "Пользователь <a style='color:royalblue'> " + user.getFio() + "</a> ");
                        //dialog_->fillUserEditFrm(user);
                        emit userReady(user);
                        //emit ready();

                    }
                        break;

                }
            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         ADD_MODEL
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::ADD_NEW_MODEL:
            {
                //Сервер вернул результат команды "ADD_NEW_MODEL"     
                switch (model) {
                    case ModelWrapper::Model::Nsi:
                    {
                        Nsi nsi;
                        JsonSerializer::parse(wrapper.getData(), nsi);
                        //QMessageBox::information(0, "НСИ",
                        //        " <a style='color:royalblue'> " + nsi.getName() + "</a> ");
                        emit responseServer(wrapper.getData());

                    }
                        break;

                }
            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         DEL_MODEL
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::DEL_MODEL:
            {
                //Сервер вернул результат команды "DEL_MODEL"     
                ModelWrapper::Model model = wrapper.getEnumModel();
                switch (model) {
                    case ModelWrapper::Model::User:
                    {
                        User user;
                        JsonSerializer::parse(wrapper.getData(), user);
                        //emit dialog_->showUserData(user);
                        QMessageBoxEx::information(0, wrapper.getHead(), wrapper.getMessage() +
                                "пользователя <a style='color:royalblue'> " + user.getFio() + "</a>");
                        emit ready();

                    }
                        break;
                }
            }
                break;

                ///-----------------------------------------------------------------------------
                ///
                ///                         NOP
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::NOP:
            {
                qInfo() << "Command is incorrect";

            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         SERVER_RESPONSE
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::SERVER_RESPONSE:
            {

                qInfo() << "Уведомление от сервера";

            }
                break;
                ///-----------------------------------------------------------------------------
                ///
                ///                         SET_SESSION_ID
                ///          
                ///-----------------------------------------------------------------------------
            case ModelWrapper::Command::SET_SESSION_ID:
            {
                ///Сообщить контроллеру клиента о небходимости
                //установить ID сессии
                emit setID(wrapper.getSessionID());
            }
                break;
        }
    } else {
        //*******************************************************************************************************************************************
        //                                  Ошибка выполнения команды на сервере.
        //*******************************************************************************************************************************************
        QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
        QMessageBoxEx::critical(Q_NULLPTR, wrapper.getHead(), wrapper.getMessage());
    }
}



