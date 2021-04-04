/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

}

///Деструктор.

WorkerClient::~WorkerClient() {
    //Освободить  ресурсы
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
    ModelWrapper wrapper;
    Dialog dlg; 
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
            case ModelWrapper::Command::SQL_QUERY:
            {
                //Сервер вернул результат команды "SQL_QUERY"  
                //Процесс обработки возвращённого реультата.    
                ModelWrapper::Model model = wrapper.getEnumModel();
                switch (model) {
                    case ModelWrapper::Model::Inspection:
                    {
                        QMessageBox::information(0, "Список инспекций", "Список Инспекций");
                        ItemContainer<Inspection> inspectionContainer;
                        //Выбираем данные.
                        JsonSerializer::parse(wrapper.getData(), inspectionContainer);
                       //что сессия готова передать контроллеру информацию
                       //connect(dlg, SIGNAL(onReadyResult(const RpcSocket*)), this, SLOT(notifyCurrentClient(const RpcSocket*, QString)));
     //QList<Inspection> inspections=inspectionContainer.getItemsList();
                        //for (auto& t : inspections) {
                        //    qInfo() << "name" << t.getName();
                        //}
                    }
                    break;
                    case ModelWrapper::Model::User:
                    {
                        //QMessageBox::information(0, "Information Box", "This is information text");
                        ItemContainer<User> userContainer;
                        //Выбираем данные.
                        JsonSerializer::parse(wrapper.getData(), userContainer);
                        ModelList<User>* listuser = new ModelList<User>(userContainer.getItemsList());
                        dlg.getUI()->tableView->setModel(listuser);
                        dlg.getUI()->tableView->setColumnHidden(0, true);
                        dlg.getUI()->tableView->setColumnHidden(4, true);
                        dlg.getUI()->tableView->setColumnHidden(5, true);
                        dlg.getUI()->tableView->setColumnHidden(6, true);
                        dlg.getUI()->tableView->setColumnHidden(7, true);
                        dlg.getUI()->tableView->setColumnHidden(8, true);
                        dlg.getUI()->tableView->setColumnHidden(9, true);
                        //dlg.getUI()->tableView->setColumnHidden(2, true);
                        dlg.getUI()->tableView->resizeColumnsToContents();
                        dlg.getUI()->tableView->resizeRowsToContents();
                        //dlg.getUI()->tableView->setColumnWidth(1, 500);
                        emit getInspections();
                        dlg.exec();
                        delete listuser;
                        //QList<User> users=userContainer.getItemsList();
                        //for (auto& t : users) {
                        //    qInfo() << "name" << t.getName();
                        //}
                    }
                        break;
                    case ModelWrapper::Model::PassList:
                    {
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
                qInfo() << "User with name " << user.getName().trimmed() << " is logged in";
                //Сигнализировать о завершении обработки.
                emit ready();
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
            case ModelWrapper::Command::SQL_QUERY:
            case ModelWrapper::Command::NOP:
            {

            }
                break;
        }

    }
}



