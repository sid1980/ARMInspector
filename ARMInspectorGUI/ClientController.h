#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>

#include "CommandController.h"
#include "ServerClient.h"
#include "ModelWrapper.h"
#include "WorkerClient.h"
#include "User.h"
#include "Mro.h"

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
    ///установить номер справочника
    void setNsiNum(const QString& nsinum);
    ///получить номер справочника
    const QString&  getNsiNum();
    ///получить флаг  авторизации клиента
    bool getLogged();
    ///Получить модель
    void getModel(const qint64&, ModelWrapper::Model model);
    ///Удалить модель
    void deleteModel(const qint64&, ModelWrapper::Model model);
    ///Получить пользователя сессии
    const User& getSessionUser();
    ///Полчить список МРО
    void getListMRO();
    ///Полчить список МРО
    void getListNSI(const QString& asNumNsi);


signals:
    void ready();
    ///Cписок МРО подготовлен  
    void listMroReady(const QList<Mro>&);
    ///Cписок НСИ подготовлен  
    void listNsiReady(const QList<Nsi>&);

private slots:

    /// Обработать ответ сервера на   запрос клиента.
    /// @param asJson Ответ сервера в виде JSON
    /// объекта сериализованного в строку. 
    void processRequestServer(QString asJson);
    ///Установить идентификатор сессии
    void setSessionID(int asID);
    ///Полчить список инспекций
    void getListInspections();
    ///заменить пароль пользователя
    void setPwd(const User&);
    ///Установить сигнал готовности формы 
    void formReady();



public slots:
    /// Выполнить запрос к  серверу на авторизацию пользователя.
    /// @param asLogin  Имя пользователя. 
    /// @param asPassword Пароль пользователя.
    void login(const QString &asLogin, const QString & asPassword);
    ///Установить пользователя сессии
    void  setSessionUser(const User& );
    /// Получить список моделей.
    /// @param asQuery SQL запрос.
    /// @param asModel Модель данных.
    void getListModels(ModelWrapper::Model model);
    ///добавить в базу нового пользователя
    void addUser(const User&);
    ///отредактировать данные о  пользователе
    void updateUser(const User&);
    ///получить   пользователя
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
    ///Пользователь, открывший сессию
    User m_aSessionUser;
    ///
    QString m_aNsiNum;


};


#endif // CLIENTCONTROLLER_H
