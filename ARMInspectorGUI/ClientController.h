#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>

#include "CommandController.h"
#include "ServerClient.h"
#include "ModelWrapper.h"
#include "WorkerClient.h"

class ClientController : public QObject {

    Q_OBJECT
    Q_DISABLE_COPY(ClientController)
    /// Клиент.
    ServerClient *m_pServerClient {
        nullptr
    };
    /// Командный контроллер.
    CommandController *m_pCommandController{nullptr};
    /// Обработчик серверных сообщений
    WorkerClient *m_pWorkerClient{nullptr};

    /// Стандартный конструктор.
    /// @param Родительский класс.
    explicit ClientController(QObject *aParent = nullptr);

public:
    /// Получить экземпляр класса.
    /// @return Instance of a class.
    Q_INVOKABLE static ClientController &getInstance();
    /// Инициализировать командный контроллер клиента.
    /// @param apServerClient Клиент.
    void init(ServerClient *apServerClient);
    ///установить флаг  авторизации клиента
    void setLogged(bool asLogged);
    ///получить флаг  авторизации клиента
    bool getLogged();
    ///Получить модель
    void getModel(const qint64&, ModelWrapper::Model model);
    ///Удалить модель
    void deleteModel(const qint64&, ModelWrapper::Model model);


signals:
    void ready();

private slots:

    /// Обработать ответ сервера на   запрос клиента.
    /// @param asJson Ответ сервера в виде JSON
    /// объекта сериализованного в строку. 
    void processRequestServer(QString asJson);
    ///Установить идентификатор сессии
    void setSessionID(int asID);
    ///Полчить список инспекций
    void getListInspection();
    ///Установить сигнал готовности формы 
    void formReady();



public slots:
    /// Выполнить запрос к  серверу на авторизацию пользователя.
    /// @param asLogin  Имя пользователя. 
    /// @param asPassword Пароль пользователя.
    void login(const QString &asLogin, const QString & asPassword);
    /// Получить список моделей.
    /// @param asQuery SQL запрос.
    /// @param asModel Модель данных.
    void getListModels(ModelWrapper::Model model);
    ///добавить в базу нового пользователя
    void addUser(const User&);
    ///отредактировать данные о  пользователе
    void updateUser(const User&);
    ///добавить в базу нового пользователя
    void getUser(const qint64&);
    ///Удалить пользователя
    void deleteUser(const qint64&);
    ///Ждать завершения предыдущей операции или сигнала старта.
    void waitReady();

private:
    int m_aSessionID{0};
    bool m_aLogged{false};
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;



};


#endif // CLIENTCONTROLLER_H
