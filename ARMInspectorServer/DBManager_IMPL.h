/****************************************************************************
 **
 ** Реализация  шаблонного метода  DBManager::getListModels .
 **
 ****************************************************************************/

#ifndef DBMANAGER_IMPL_H
#define DBMANAGER_IMPL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QThread>
#include <QDebug>
#include <RpcSocket.h>
#include <JsonSerializable.h>
#include <JsonSerializer.h>
#include <ItemContainer.h>
#include "ModelWrapper.h"
#include "ServerMessage.h"

///-----------------------------------------------------------------------------
///
///             Получить список моделей.
///
///-----------------------------------------------------------------------------

/// Выполнить Sql запрос для объекта класса Т. T - шаблон модели для которй 
/// выполняется запрос. Результат работы запроса упаковывается в секцию данных
/// командной обёртки m_pModellWrapper.

template<typename T> void DBManager::getListModels() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загружаем параметры команды.
    //QJsonObject param;
    //JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //Выполнить SQL запрос.
    //QString asSqlQuery = param["query"].toString();
    //QString asSqlQuery = T::getQuery();

    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](ItemContainer<T> container, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(container);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    //Контейнер, в который записываются  объекты сериализаци.
    ItemContainer<T> container;
    //Проверить , открыта ли  база данных. 
    QSqlDatabase database = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
    //Проверить подключение подключение к  базе данных.
    if (!database.isValid()) {
        //Подключение  к базе данных некорректно.
        //Установить сообщение.
        setResult(container, Message::DATABASE_CONNECTION_INCORRECT);
        //Прекратить работу менеджера базы данных.
        return;
    }

    if (!database.isOpen()) {
        setResult(container, Message::DATABASE_IS_NOT_OPENED);
        return;
    }
    //Проверить  и выполнить  SQL запрос.
    QSqlQuery queryStatementInfo(database);
    qDebug() << T::getQuery();

    if (!queryStatementInfo.exec(T::getQuery())) {
        setResult(container, Message::SQL_ERROR);
        return;
    }
    //Выборка данных.
    while (queryStatementInfo.next()) {
        QJsonObject recordObject;
        ///Экземпляр объекта класса T, который будет  сериализоваться.
        T model;
        for (int x = 0; x < queryStatementInfo.record().count(); x++) {
            recordObject.insert(queryStatementInfo.record().fieldName(x), QJsonValue::fromVariant(queryStatementInfo.value(x)));
        }
        ///Считать запись базы данных  в объект класса T.  
        model.read(recordObject);
        ///Добавить объект класса T в контейнер сериализации.
        container.add(model);
    }
    setResult(container, Message::SQL_SUCCESS);
    return;

}


///-----------------------------------------------------------------------------
///
///             Получить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::getModel() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    T model;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();
    //Выполнить SQL запрос.
    //QString asSqlQuery = param["query"].toString();
    //QString asSqlQuery = T::getQuery();

    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](T model, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(model);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    //Проверить , открыта ли  база данных. 
    m_Db = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
    //Проверить подключение подключение к  базе данных.
    if (!m_Db.isValid()) {
        //Подключение  к базе данных некорректно.
        //Установить сообщение.
        setResult(model, Message::DATABASE_CONNECTION_INCORRECT);
        //Прекратить работу менеджера базы данных.
        return;
    }
    if (!m_Db.isOpen()) {
        setResult(model, Message::DATABASE_IS_NOT_OPENED);
        return;
    }
    //Проверить  и выполнить  SQL запрос.
    QString query = T::getQuery() + " where id=" + QString::number(asId);
    QJsonObject recordObject = getRecord(query);
    if (recordObject.isEmpty()) {
        setResult(model, Message::MODEL_GET_FAILURE);
        return;
    }
    ///Считать запись базы данных  в объект класса T.  
    model.read(recordObject);
    setResult(model, Message::MODEL_GET_SUCCESS);
    return;

}


///-----------------------------------------------------------------------------
///
///             Удалить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::deleteModel() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    T model;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();

    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](T model, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(model);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    //Проверить , открыта ли  база данных. 
    m_Db = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
    //Проверить подключение подключение к  базе данных.
    if (!m_Db.isValid()) {
        //Подключение  к базе данных некорректно.
        //Установить сообщение.
        setResult(model, Message::DATABASE_CONNECTION_INCORRECT);
        //Прекратить работу менеджера базы данных.
        return;
    }

    if (!m_Db.isOpen()) {
        setResult(model, Message::DATABASE_IS_NOT_OPENED);
        return;
    }
    //Проверить  и выполнить  SQL запрос.
    //qDebug() << T::getQuery();
    //QString::number(user.getId());
    QString query = T::getQuery() + " where id=" + QString::number(asId);
    QJsonObject recordObject = getRecord(query);
    if (recordObject.isEmpty()) {
        setResult(model, Message::MODEL_GET_FAILURE);
        return;
    }
    ///Считать запись базы данных  в объект класса T.  
    model.read(recordObject);
    //qDebug() << T::delQuery();
    //QString::number(user.getId());
    QSqlQuery queryStatementInfo(m_Db);
    query = T::delQuery() + " where id=" + QString::number(asId);
    if (!queryStatementInfo.exec(query)) {
        setResult(model, Message::MODEL_DEL_FAILURE);
        return;
    }

    setResult(model, Message::MODEL_DEL_SUCCESS);
    return;
}
#endif /* DBMANAGER_IMPL_H */

