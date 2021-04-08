/****************************************************************************
 **
 **             Класс DBManager для работы с базой данных.
 **
 ****************************************************************************/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QThread>
#include <QDebug>
#include <QMutexLocker>

#include <RpcSocket.h>
#include "ModelWrapper.h"
#include "ServerMessage.h"

class DBManager : public QObject {
    Q_OBJECT
public:

    /// Стандартный конструктор.
    /// @param apParent Родитель.
    DBManager(QObject *apParent = nullptr);

    ///Инициализировать указатель на класс командной обёртки.
    void setModelWrapper(ModelWrapper* wrapper);
    ///Получить  указатель на класс командной обёртки.
    const ModelWrapper* getModelWrapper() const;



    /// Подключиться к базе данных .Открыть  базу данных.
    bool addDataBase();

    /// Авторизация пользователя.
    void login();
    ///Добавить  пользователя.
    void addUser();
    /// Получить список моделей.
    void getListModels();
    template<typename T> void getListModels();
    /// Отключить клиента от сервера
    /// @param apClientSocket Указатель на сокет клиент-серверного соединения.
    void removeDatabase();
    /// Выполнить Sql запрос.
    void execSqlquery();



    /// Выполнить Sql запрос.
    template<typename T> void execSqlquery();


private:
    ///Указатель на командную обёртку модели.
    ModelWrapper *m_pModelWrapper;
    ///Мьютех блокировки внешних воздействий. 
    QMutex m_Mutex;
};
#include "DBManager_IMPL.h"

#endif // DBMANAGER_H
