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
 * File:   WorkerClient.h
 * Author: ASK
 *
 * Created on 14 декабря 2019 г., 19:50
 */

#ifndef WORKERCLIENT_H
#define WORKERCLIENT_H
#include <QtCore>
#include "ModelWrapper.h"
#include "JsonSerializer.h"
#include "ItemContainer.h"
#include "ModelList.h"
#include "User.h"
#include "UserView.h"
#include "Inspection.h"
#include "dialog.h"

class WorkerClient : public QObject {
    Q_OBJECT

public:
    QList<Inspection> inspections_;
    /// Стандартный конструктор.
    /// @param apParent Родитель.
    WorkerClient(QObject *apParent = nullptr);
    /// Стандартный конструктор.
    ~WorkerClient();
    void setModelWrapperString(const QString& asWrapperString);
    const QString& getModelWrapperString() const;
    ///Основная функция потока
    void process();


signals:
    ///Установить идентификатор клиента
    void setID(int asID);
    ///Ждать ответ сервера
    void waitServer();
    ///Получить список инспекций
    void getInspections();
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
    ///Передать список инспекций
    void passListInspections(const QList<Inspection>& inspections);
    ///Передать данные о пользователе
    void addUser(const User&);
    ///Получить  данные о пользователе
    void getUserData(const qint64&);
    ///Сигнал завершения работы.
    /// @param asResult Результат выполнения запроса 
    void finished(QString asResult);
    void error(QString asError);    
private:
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    Dialog* dialog_;
};

#endif /* WORKERCLIENT_H */

