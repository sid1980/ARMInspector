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
#include "DBManager.h"


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
    //static QMutex mutex;
    //QMutexLocker lock(&mutex);
    //Проверить , открыта ли  база данных. 
    if (!connectDB<T>()) {
        
        return;
    }
    getAllRecordS<T>();
    
    return;
}


///-----------------------------------------------------------------------------
///
///             Получить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::getModel() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    //static QMutex mutex;
    //QMutexLocker lock(&mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param["ID"].toInt();
    if (!connectDB<T>()) {
        
        return;
    }
    getRecord<T>(MQuery<T>::selectById(asId));
    

    return;
}

///-----------------------------------------------------------------------------
///
///             Вызвать хранимую процедуру .
///
///-----------------------------------------------------------------------------

template<typename T, typename TOUT> void DBManager::callProcedure() {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    //Контейнер, в который записываются  объекты сериализаци-модели.
    ItemContainer<TOUT> container;
    auto setResult = [this](ItemContainer<TOUT> container, Message msg, QString attach) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(container);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(QString(result.str).arg(attach));
        m_pModelWrapper->setSuccess(result.success);
        

    };
    //Создать модель данных 
    T model; //Входные данные 
    TOUT outmodel; //Выходные данные
    //дополнение к сообщению
    QString attach = "<br><a style='color:red'>";
    attach += model.call() + "</a>";
    JsonSerializer::parse(m_pModelWrapper->getData(), model);
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<T>()) {
        return;
    }
    QSqlQuery query(m_Db);
    query.prepare(model.call());
    model.bindData(&query);
    //Проверить  и выполнить  SQL запрос.
    if (!query.exec()) {
        attach += query.lastError().text();
        setResult(container, Message::SQL_ERROR, attach);
        return;
    }
    QJsonObject recordObject;
    //Выборка данных.
    while (query.next()) {
        ///Экземпляр объекта класса T, который будет  сериализоваться.
        for (int x = 0; x < query.record().count(); x++) {
            recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
        }
        ///Считать запись базы данных  в объект класса T.
        outmodel.read(recordObject);
        container.add(outmodel);
    }
    setResult(container, Message::CALL_PROCEDURE_SUCCESS, attach);
    return;
}
///-----------------------------------------------------------------------------
///
///             Добавить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::addModel() {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](T model, Message msg, QString attach) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(model);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(QString(result.str).arg(attach));
        m_pModelWrapper->setSuccess(result.success);
        

    };
    //дополнение к сообщению
    QString attach = "<br><a style='color:red'>";
    //Создать модель данных 
    T model;
    JsonSerializer::parse(m_pModelWrapper->getData(), model);
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<T>()) {
        return;
    }
    QSqlQuery query(m_Db);
    attach += model.insert() + "</a>";
    //qInfo() << model.insert();
    query.prepare(model.insert());
    model.bindData(&query);

    if (query.exec()) {
        query.prepare(MQuery<T>::selectMaxID());
        attach += MQuery<T>::selectMaxID();
        if (!query.exec()) {
            setResult(model, Message::MODEL_ADD_FAILURE, attach);
            return;
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
        }
        setResult(model, Message::MODEL_ADD_SUCCESS, attach);
        ////qDebug() << "add model  succes: ";
    } else {
        setResult(model, Message::MODEL_ADD_FAILURE, attach);
    }
    return;
}


///-----------------------------------------------------------------------------
///
///                     Редактировать модель 
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::updateModel() {
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
    //Создать модель данных User
    T model;
    JsonSerializer::parse(m_pModelWrapper->getData(), model);
    ////qDebug() << myquery;
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<T>()) {
        return;
    }
    //База данных открыта. Можно проводить авторизацию пользователя. 
    QSqlQuery query(m_Db);
    ////qDebug() << model.update();
    query.prepare(model.update());
    model.bindData(&query);

    if (query.exec()) {
        setResult(model, Message::MODEL_UPDATE_SUCCESS);
        // //qDebug() << "update model  succes: ";
    } else {
        setResult(model, Message::MODEL_UPDATE_FAILURE);
        // //qDebug() << "update model failed: ";
    }
    return;
}


///-----------------------------------------------------------------------------
///
///             Удалить модель.
///
///-----------------------------------------------------------------------------

template<typename T> void DBManager::deleteModel() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    //static QMutex mutex;
    //QMutexLocker lock(&mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //ID модели.
    qint64 asId = param[ID_].toInt();
    if (!connectDB<T>()) {
        
        return;
    }
    T model = getRecord<T>(MQuery<T>::selectById(asId));
    if (!m_pModelWrapper->getSuccess()) {
        
        return;
    }
    //    query = T::delQuery() + " where id=" + QString::number(asId);
    delRecord<T>(model, MQuery<T>::removeById(asId));
    
    return;
}


///-----------------------------------------------------------------------------
///
///              Подключение к  базе данных.
///
///-----------------------------------------------------------------------------

template<typename T> bool DBManager::connectDB() {
    T model;
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
///             Получить запись из базы.
///
///-----------------------------------------------------------------------------

template<typename T> T DBManager::getRecord(const QString& queryStr) {
    T model;
    QJsonObject recordObject;
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](T model, Message msg, QString attach) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(model);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(QString(result.str).arg(attach));
        m_pModelWrapper->setSuccess(result.success);

    };
    //дополнение к сообщению
    QString attach = "<br><a style='color:red'>";
    attach += queryStr + "</a>";
    //Проверить  и выполнить  SQL запрос.
    QSqlQuery query(m_Db);
    if (!query.exec(queryStr)) {
        setResult(model, Message::SQL_ERROR, attach);
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
        setResult(model, Message::MODEL_GET_FAILURE, attach);
        return model;
    }
    ///Считать запись базы данных  в объект класса T.
    model.read(recordObject);
    setResult(model, Message::MODEL_GET_SUCCESS, attach);
    return model;
}


///-----------------------------------------------------------------------------
///
///             Получить все записи из базы.
///
///-----------------------------------------------------------------------------

template<typename T> ItemContainer<T> DBManager::getAllRecordS() {
    //Контейнер, в который записываются  объекты сериализаци-модели.
    ItemContainer<T> container;
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](ItemContainer<T> container, Message msg, QString attach) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(container);
        ////qDebug() << json;
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(QString(result.str).arg(attach));
        m_pModelWrapper->setSuccess(result.success);
    };
    //дополнение к сообщению
    QString attach = "<br><a style='color:red'>";
    attach += MQuery<T>::selectAll() + "</a>";

    //Проверить  и выполнить  SQL запрос.
    QSqlQuery query(m_Db);
    ///Выполнить SQL запрос
    ////qDebug() << QString::fromLocal8Bit("Выполнить SQL запрос:  ") << MQuery<T>::selectAll();
    if (!query.exec(MQuery<T>::selectAll())) {
        setResult(container, Message::SQL_ERROR, attach);
        return container;
    }
    //Выборка данных.
    while (query.next()) {
        QJsonObject recordObject;
        ///Экземпляр объекта класса T, который будет  сериализоваться.
        T model;
        for (int x = 0; x < query.record().count(); x++) {
            recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
            ////qDebug() << query.record().fieldName(x) << "   " << QString::fromLocal8Bit(QJsonValue::fromVariant(query.value(x)).toString().toStdString().c_str());
        }
        ///Считать запись базы данных  в объект класса T.  
        model.read(recordObject);
        ////qDebug()<<":  " << model.getFields()[0];
        ////qDebug()<<":  " << model.getFields()[1];
        ////qDebug()<<":  " << model.getFields()[2];
        ////qDebug()<<":  " << model.getFields()[3];
        ///Добавить объект класса T в контейнер сериализации.
        container.add(model);
    }
    setResult(container, Message::SQL_SUCCESS, attach);
    return container;
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




#endif /* DBMANAGER_IMPL_H */

