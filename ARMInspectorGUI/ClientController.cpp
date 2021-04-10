#include "ClientController.h"
#include "User.h"
#include "ModelWrapper.h"
#include "JsonSerializer.h"
#include "ItemContainer.h"
#include "WorkerClient.h"
#include <QTextCodec>
#include <QThread>
#include <QMutex>
#include "WorkerClient.h"
//int ClientController::m_aSessionID = {0};

/// Стандартный конструктор.
/// @param Родительский класс.

ClientController::ClientController(QObject *aParent) : QObject(aParent) {

}

/// Получить экземпляр класса.
/// @return Instance of a class.

ClientController &ClientController::getInstance() {
    static ClientController instance;
    return instance;
}

/// Инициализировать командный контроллер клиента.
/// @param apServerClient Клиент.

void ClientController::init(ServerClient *apServerClient) {
    m_pServerClient = apServerClient;

    // Creating rpc controller
    m_pCommandController = new CommandController(apServerClient->getClientSocket(), this);

    //Создать обработчик сообщений сервера 
    m_pWorkerClient = new WorkerClient();
    //addThread(QString(""));
    // Сигнально-слотовое соединение, сигнализирующее, что   контроллер комманд
    // готов вернуть  результат  выполнения запроса к серверу.
    connect(m_pCommandController, SIGNAL(onProcessRequestServer(QString)), SLOT(processRequestServer(QString)));
    // Сигнально-слотовое соединение установки идентификатора сессии.
    connect(m_pWorkerClient, SIGNAL(setID(int)), SLOT(setSessionID(int)));
    // Сигнально-слотовое соединение установки идентификатора сессии.
    connect(m_pWorkerClient, SIGNAL(ready()), SLOT(formReady()));
    // Сигнально-слотовое соединение получения списка организаций.
    connect(m_pWorkerClient, SIGNAL(getInspections()), SLOT(getListInspection()));
    // Сигнально-слотовое соединение для добавления нового пользователя в базу данных.
    connect(m_pWorkerClient, SIGNAL(addUser(const User&)), SLOT(addUser(const User&)));
    // Сигнально-слотовое соединение для полуяения  сведений о   пользователе из  базы данных.
    connect(m_pWorkerClient, SIGNAL(getUserData(const qint64&)), SLOT(getUser(const qint64&)));
    // Сигнально-слотовое соединение  ожидания ответа от сервера.
    connect(m_pWorkerClient, SIGNAL(waitServer()), SLOT(waitReady()));
}
///Установить идентификатор сессии

void ClientController::setSessionID(int asID) {
    m_aSessionID = asID;
    qInfo() << QString::fromLocal8Bit("ID сессии:") << m_aSessionID;
    emit ready();
}
///Установить сигнал готовности формы

void ClientController::formReady() {
    m_aLogged = true;
    emit ready();
}


///Полчить список инспекций

void ClientController::getListInspection() {
    this->getListModels(ModelWrapper::Model::Inspection);
};

///Ждать сигнала готовности данных.

void ClientController::waitReady() {
    QEventLoop loop;
    connect(this, SIGNAL(ready()), &loop, SLOT(quit()));
    //connect(m_pWorkerClient, SIGNAL(ready()), &loop, SLOT(quit()));
    //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();
}

/// Выполнить запрос клиента на авторизацию пользователя.
/// @param asLogin  Имя пользователя. 
/// @param asPassword Пароль пользователя.

void ClientController::login(const QString &asLogin, const QString &asPassword) {
    qInfo() << "ID" << m_aSessionID;
    //Создать командную обёртку.
    ModelWrapper wrapper(ModelWrapper::Command::LOGIN);
    //Установить идентификатор сессии. 
    wrapper.setSessionID(m_aSessionID);
    //Задать параметры команды.
    QJsonObject params;
    params.insert("name", asLogin);
    params.insert("password", asPassword);
    //Конвертировать параметры в строку.
    QString query = JsonSerializer::json_encode(params);
    //Положить параметры в раздел данных.
    wrapper.setData(query);
    //Упаковать  весь запрос в строку
    query = JsonSerializer::serialize(wrapper);
    //Переслпть его на сервер.
    m_pCommandController->requestServer(query);
}


///Получить данные о пользователе

void ClientController::getUser(const qint64& asId) {
    getModel(asId, ModelWrapper::Model::User);
}
///Добавить нового пользователя.

void ClientController::addUser(const User &user) {
    //QMessageBox::information(0, "Добавление нового пользовтеля", QString(user.getFio()));

    //Создать командную обёртку.
    ModelWrapper wrapper(ModelWrapper::Command::ADD_NEW_USER);
    //Установить идентификатор сессии.
    wrapper.setSessionID(m_aSessionID);
    //Установить модель.    
    wrapper.setEnumModel(ModelWrapper::Model::User);
    //Сериализовать модель User.Передать данные о пользователе.
    QString userAsString = JsonSerializer::serialize(user);
    wrapper.setData(userAsString);
    //Упаковать  весь запрос в строку
    QString query = JsonSerializer::serialize(wrapper);
    //Переслать его на сервер.
    m_pCommandController->requestServer(query);
}



///Получить  модель.

void ClientController::getModel(const qint64& asId, ModelWrapper::Model model) {
    //Создать командную обёртку.
    ModelWrapper wrapper(ModelWrapper::Command::GET_MODEL);
    //Установить идентификатор сессии.
    wrapper.setSessionID(m_aSessionID);
    //Установить модель.    
    wrapper.setEnumModel(model);
    //Задать параметры команды.
    QJsonObject params;
    params.insert("ID", asId);
    //params.insert("model", model);
    //Конвертировать параметры в строку.
    QString query = JsonSerializer::json_encode(params);
    //Положить параметры в раздел данных.
    wrapper.setData(query);
    //Упаковать  весь запрос в строку
    query = JsonSerializer::serialize(wrapper);
    //Переслать его на сервер.
    m_pCommandController->requestServer(query);

}///Получить список моделей.

void ClientController::getListModels(ModelWrapper::Model model) {
    //Создать командную обёртку.
    ModelWrapper wrapper(ModelWrapper::Command::GET_LIST_MODELS);
    //Установить идентификатор сессии.
    wrapper.setSessionID(m_aSessionID);
    //Установить модель.    
    wrapper.setEnumModel(model);
    //Задать параметры команды.
    //QJsonObject params;
    //params.insert("query", asQuery);
    //params.insert("model", model);
    //Конвертировать параметры в строку.
    //QString query = JsonSerializer::json_encode(params);
    //Положить параметры в раздел данных.
    wrapper.setData("");
    //Упаковать  весь запрос в строку
    QString query = JsonSerializer::serialize(wrapper);
    //Переслать его на сервер.
    m_pCommandController->requestServer(query);

}


/// Обработать ответ сервера.
/// @param asJson Ответ сервера в виде JSON
/// объекта сериализованного в строку.  JSON объект представляет
/// собой командную обёртку, внутри которой находится второй сериализованный в строку
/// JSON объект, содержащий  возврощённые сервером данные.  

void ClientController::processRequestServer(QString asJson) {
    //Переместить данные в обработчик.
    m_pWorkerClient->setModelWrapperString(asJson);
    //Стартовать процесс обработкм сообщений.
    m_pWorkerClient->process();
    //addThread(asJson);
}
///получить флаг  авторизации клиента

bool ClientController::getLogged() {
    return this->m_aLogged;
}

///установить  флаг  авторизации клиента
/// @param asLogged 

void ClientController::setLogged(bool asLogged) {
    this->m_aLogged = asLogged;
}

/// Создать новый поток.

