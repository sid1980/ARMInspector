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
#include "ItemContainer.h"
#include <array>
#include "User/User.h"
#include "Mro/Mro.h"
#include "User/UserView.h"
#include "Inspection/Inspection.h"
#include "Nsi/Nsi.h"

using namespace std;
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
    ///Проверить имя  пользователя.
    bool isUserName(const QString&);
    ///Редактировать   пользователя.
    void updateUser();
    ///Изменить пароль    пользователя.
    void changePassword();
    /// Получить список моделей.
    void getListModels();
    template<typename T> void getListModels();


    /// Удалить  модель.
    void deleteModel();
    ///удалить модель из списка
    template<typename T> void deleteModel();
    
    /// Редактировать  модель.
    void updateModel();
    template<typename T> void updateModel();
    ///добавить модель
    void addModel();
    template<typename T> void addModel();
    /// Получить  модель.
    void getModel();
    template<typename T> void getModel();
    ///Получить  запись из базы данных.
    template<typename T> T getRecord(const QString& queryStr);
    ///Получить  записи из базы данных.
    template<typename T> ItemContainer<T> getAllRecordS();
    ///удалить запись
    template<typename T> void delRecord(const T&, const QString&);
    ///Проверить  подключение к базе данных.
    template<typename T> bool connectDB();
    /// Отключить клиента от сервера
    /// @param apClientSocket Указатель на сокет клиент-серверного соединения.
    void removeDatabase();
    /// Выполнить Sql запрос.
    ///void execSqlquery();



    /// Выполнить Sql запрос.
    //template<typename T> void execSqlquery();


private:
    ///Указатель на командную обёртку модели.
    ModelWrapper *m_pModelWrapper;
    ///Мьютех блокировки внешних воздействий. 
    QMutex m_Mutex;
    ///DB. 
    QSqlDatabase m_Db;
};
#include "DBManager_IMPL.h"

#endif // DBMANAGER_H
