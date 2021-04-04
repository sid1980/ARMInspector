/****************************************************************************
 **
 ** Реализация  шаблонного метода  DBManager::execSqlquery .
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


/// Выполнить Sql запрос для объекта класса Т. T - шаблон модели для которй 
/// выполняется запрос. Результат работы запроса упаковывается в секцию данных
/// командной обёртки m_pModellWrapper.

template<typename T> void DBManager::execSqlquery() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загружаем параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //Выполнить SQL запрос.
    QString asSqlQuery = param["query"].toString();

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
    if (!queryStatementInfo.exec(asSqlQuery)) {
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
#endif /* DBMANAGER_IMPL_H */

