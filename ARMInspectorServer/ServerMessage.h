/****************************************************************************
 **
 **             Список сообщений сервера   
 **
 ****************************************************************************/

/* 
 * File:   ServerMessage.h
 * Author: kazun_as
 *
 * Created on 5 декабря 2019 г., 08:22
 */

#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H
#include <QtCore>
#include "ModelWrapper.h"

///Список идентификаторов сообщений. 

enum Message {
    USER_LOGIN_SUCCESS,
    USER_LOGIN_FAILURE,
    USER_ADD_SUCCESS,
    USERR_ADD_FAILURE,
    USER_IS_NOT_FOUND,
    DATABASE_IS_NOT_OPENED,
    NO_DATABASE_CONNECTION,
    DATABASE_IS_OPENED,
    SQL_ERROR,
    SQL_SUCCESS,
    CONNECTION_ERROR,
    MAXIMUM_CONNECTIONS_EXCEEDED,
    DATABASE_IS_CONNECTED,
    DATABASE_DRIVER_IS_NOT_AVAILABLE,
    CANNOT_CREATE_SESSION,
    CLIENT_IS_CONNECTED,
    SESSION_IS_OPEN,
    FAILED_CREATE_DBMANAGER,
    UNABLE_CONNECT_DATABASE,
    INCORRECT_COMMAND,
    UNABLE_OPEN_DATABASE,
    CANNOT_CREATE_SEANCE,
    FAILED_CREATE_THREAD,
    FAILED_CREATE_WORKER,
    DATABASE_CONNECTION_INCORRECT,
    CANNOT_DELETE_SESSION,
    ADD_ADMIN_USER_SUCCESS,
    CANNOT_ADD_ADMIN_USER

};


namespace ServerMessage {
    ///Структура, привязывающая сообщение к результату выполнения 
    ///команды на сервере/ 

    typedef struct {
        const char * str;
        bool success;
        ModelWrapper::Command cmd;
    } Result;
    ///Список сообщений с результатом выполнения команды сервером
    const QHash<const Message, Result> message = {
        {Message::USER_LOGIN_SUCCESS,{"Пользователь  успешно прошёл авторизацию.", true, ModelWrapper::Command::NOP}},
        {Message::USER_LOGIN_FAILURE,{"Пользователь  не прошёл авторизацию.", false, ModelWrapper::Command::NOP}},
        {Message::USER_ADD_SUCCESS,{"Пользователь  успешно добавлен в базу данных.", true, ModelWrapper::Command::NOP}},
        {Message::USERR_ADD_FAILURE,{"Ошибка при добавлении пользователя в базу данных.", false, ModelWrapper::Command::NOP}},
        {Message::USER_IS_NOT_FOUND,{"Пользователя с таким именем нет в базе данных.", false, ModelWrapper::Command::NOP}},
        {Message::DATABASE_IS_NOT_OPENED,{"База данных не открыта.", false, ModelWrapper::Command::NOP}},
        {Message::NO_DATABASE_CONNECTION,{"Подключение к базе данных отсутствует.", false, ModelWrapper::Command::NOP}},
        {Message::DATABASE_IS_OPENED,{"База данных открыта", true, ModelWrapper::Command::NOP}},
        {Message::SQL_ERROR,{"Ошибка SQL запроса.", false, ModelWrapper::Command::NOP}},
        {Message::SQL_SUCCESS,{"SQL запрос успешно выполнен.", true, ModelWrapper::Command::NOP}},
        {Message::CONNECTION_ERROR,{"Ошибка подключения.", false, ModelWrapper::Command::NOP}},
        {Message::DATABASE_DRIVER_IS_NOT_AVAILABLE,{"Драйвер базы данных не доступен.", false, ModelWrapper::Command::NOP}},
        {Message::CANNOT_CREATE_SESSION,{"Не возможно создать сессию.", false, ModelWrapper::Command::NOP}},
        {Message::MAXIMUM_CONNECTIONS_EXCEEDED,{"Превышено предельно допустимое число подключений.", false, ModelWrapper::Command::SERVER_RESPONSE}},
        {Message::DATABASE_IS_CONNECTED,{"Пользователь подключен к базе данных ARMInspector.", true, ModelWrapper::Command::NOP}},
        {Message::CLIENT_IS_CONNECTED,{"Пользователь подключен к серверу.", true, ModelWrapper::Command::NOP}},
        {Message::SESSION_IS_OPEN,{"Клиенту открыта сессия.", true, ModelWrapper::Command::SET_SESSION_ID}},
        {Message::FAILED_CREATE_DBMANAGER,{"Не удалось создать экземпляр класса  управления базой данных.", false, ModelWrapper::Command::NOP}},
        {Message::UNABLE_CONNECT_DATABASE,{"Не удалось подключиться к базе данных.", false, ModelWrapper::Command::NOP}},
        {Message::INCORRECT_COMMAND,{"Неверная  команда.", false, ModelWrapper::Command::NOP}},
        {Message::UNABLE_OPEN_DATABASE,{"Не могу открыть базу данных.", false, ModelWrapper::Command::NOP}},
        {Message::CANNOT_CREATE_SEANCE,{"Не возможно создать сеанс работы с базой данных.", false, ModelWrapper::Command::NOP}},
        {Message::FAILED_CREATE_THREAD,{"Не удалось создать поток в сеансе.", false, ModelWrapper::Command::NOP}},
        {Message::FAILED_CREATE_WORKER,{"Не удалось создать экземпляр класса, подсоединяемого к потоку.", false, ModelWrapper::Command::NOP}},
        {Message::DATABASE_CONNECTION_INCORRECT,{"Подключение  к базе данных некорректно.", false, ModelWrapper::Command::NOP}},
        {Message::CANNOT_DELETE_SESSION,{"Невозможно удалить сессию.", false, ModelWrapper::Command::NOP}},
        {Message::ADD_ADMIN_USER_SUCCESS,{"Пользователь admin успешно добавлен в базу данных.", true, ModelWrapper::Command::NOP}},
        {Message::CANNOT_ADD_ADMIN_USER,{"Ошибка добавления пользователя admin.", false, ModelWrapper::Command::NOP}}
    };
    /// Выбрать сообщение из списка.
    /// @param msg Идентификатор сообщения, которое выбирается из списка.
    /// @return Возвращает сообщение,  
    const Result outPut(const Message& msg);


}


#endif /* SERVERMESSAGE_H */

