/****************************************************************************
 **
 **            ОБРАБОТЧИК СООБЩЕНИЙ СЕРВЕРА
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
#include "reportFrm.h"

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
    ///Установить сессионого пользователя
    void setSessionUser(const User&);
    ///Ждать ответ сервера
    void waitServer();
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
    ///Передать список инспекций
    void passListInspections(const QList<Inspection>& inspections);
    ///Передать данные о пользователе
    void addUser(const User&);
    ///заменить пароль пользователя
    void setPwd(const User&);
    ///Редактировать данные о пользователе
    void updateUser(const User&);
    ///Получить  данные о пользователе
    void getUserData(const qint64&);
    ///Удалить  данные о пользователе
    void deleteUser(const qint64&);
    ///Запросить список инспекций
    void getInspections();
    ///Cписок инспекций подготовлен  
    void listInspectionsReady(const QList<Inspection>&);
    ///Сигнал завершения работы.
    /// @param asResult Результат выполнения запроса 
    void finished(QString asResult);
    void error(QString asError);
private:
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    Dialog* dialog_;
    reportFrm* reportDlg_;
};

#endif /* WORKERCLIENT_H */

