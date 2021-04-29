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
#include <MQuery.h>
#include "ModelWrapper.h"
#include "ServerMessage.h"






///-----------------------------------------------------------------------------
///
///             Добавить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::addModel() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();
    T model;
    if (!connectDB<T>(model)) {
        return;
    }

    //MQuery<T> mQuery;
    //QString query = mQuery.insert().prepare() + " where id=" + QString::number(asId);
    QString query = T::getQuery() + " where id=" + QString::number(asId);
    model = getRecord<T>(model,query);
    if (!m_pModelWrapper->getSuccess()) {
        return;
    }
    query = T::delQuery() + " where id=" + QString::number(asId);
    delRecord<T>(model, query);
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
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();
    T model;
    if (!connectDB<T>(model)) {
        return;
    }
    //QString query = T::getQuery() + " where id=" + QString::number(asId);
    //qDebug() << query;
    T model = getRecord<T>(model,MQuery<T>::selectById(asId));
    if (!m_pModelWrapper->getSuccess()) {
        return;
    }
///    query = T::delQuery() + " where id=" + QString::number(asId);
    delRecord<T>(model, MQuery<T>::removeById(asId));
    return;
}

///-----------------------------------------------------------------------------
///
///              Подключение к  базе данных.
///
///-----------------------------------------------------------------------------

template<typename T> bool DBManager::connectDB(const T& model) {
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
    m_Db = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
    //Проверить , открыта ли  база данных. 
    //Проверить подключение подключение к  базе данных.
    if (!m_Db.isValid()) {
        //Подключение  к базе данных некорректно.
        setResult(model, Message::DATABASE_CONNECTION_INCORRECT);
    } else if (!m_Db.isOpen()) {
        setResult(model, Message::DATABASE_IS_NOT_OPENED);
    } else {
        setResult(model, Message::DATABASE_IS_OPENED);
    }
    return m_pModelWrapper->getSuccess();
}
///-----------------------------------------------------------------------------
///
///             Удалить запись из базы.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::delRecord(const T& model, const QString& queryStr) {
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
    //Проверить  и выполнить  SQL запрос.
    QSqlQuery query(m_Db);
    if (!query.exec(queryStr)) {
        setResult(model, Message::MODEL_DEL_FAILURE);
        return;
    }
    setResult(model, Message::MODEL_DEL_SUCCESS);
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
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();
    T model;
    //QString query = MQuery<T>::selectAll() + " where id=" + QString::number(asId);
    getRecord<T>(model,MQuery<T>::selectById(asId));
    return;
}


///-----------------------------------------------------------------------------
///
///             Получить запись из базы.
///
///-----------------------------------------------------------------------------

template<typename T> T DBManager::getRecord(const T& model, const QString& queryStr) {
   
    //Выполнить SQL запрос.
    if (!connectDB<T>(model)) {
        return;
    }
    QJsonObject recordObject;
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
    //Проверить  и выполнить  SQL запрос.
    QSqlQuery query(m_Db);
    if (!query.exec(queryStr)) {
        setResult(model, Message::SQL_ERROR);
        return model;
    }
    //Выборка данных.
    while (query.next()) {
        ///Экземпляр объекта класса T, который будет  сериализоваться.
        for (int x = 0; x < query.record().count(); x++) {
            recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
        }
    }
    if (recordObject.isEmpty()) {
        setResult(model, Message::MODEL_DEL_FAILURE);
        return model;
    }
    ///Считать запись базы данных  в объект класса T.
    model.read(recordObject);
    setResult(model, Message::MODEL_GET_SUCCESS);
    return model;
}


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
    T model;
    getAllRecordS<T>(model);
    return;
}

///-----------------------------------------------------------------------------
///
///             Получить все записи из базы.
///
///-----------------------------------------------------------------------------

template<typename T> ItemContainer<T> DBManager::getAllRecordS(const T& model) {
    //Проверить , открыта ли  база данных. 
    if (!connectDB<T>(model)) {
        return;
    }
    //Контейнер, в который записываются  объекты сериализаци-модели.
    ItemContainer<T> container;
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

    //Проверить  и выполнить  SQL запрос.
    QSqlQuery query(m_Db);
    ///Выполнить SQL запрос
    //qDebug()<<"Выполнить SQL запрос:  " << T::getQuery();
    if (!query.exec(MQuery<T>::selectAll())) {
        setResult(container, Message::SQL_ERROR);
        return container;
    }
    //Выборка данных.
    while (query.next()) {
        QJsonObject recordObject;
        ///Экземпляр объекта класса T, который будет  сериализоваться.
        for (int x = 0; x < query.record().count(); x++) {
            recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
        }
        ///Считать запись базы данных  в объект класса T.  
        model.read(recordObject);
        //qDebug()<<":  " << model.getFields()[1];
        ///Добавить объект класса T в контейнер сериализации.
        container.add(model);
    }
    setResult(container, Message::SQL_SUCCESS);
    return container;

}


#endif /* DBMANAGER_IMPL_H */

