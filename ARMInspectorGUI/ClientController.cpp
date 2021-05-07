#include "ClientController.h"
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
    // Сигнально-слотовое соединение для добавления нового пользователя в базу данных.
    connect(m_pWorkerClient, SIGNAL(runServerCmd(const QString&)), SLOT(runServerCmd(const QString&)));
    // Сигнально-слотовое соединение для добавления нового пользователя в базу данных.
    connect(m_pWorkerClient, SIGNAL(responseServer(const QString&)), SIGNAL(responseServer(const QString&)));
    ///пользователь прошёл аутентификацию
    ///необходимо установить данные сессионного пользователя
    connect(m_pWorkerClient, SIGNAL(setSessionUser(const User&)), SLOT(setSessionUser(const User&)));
    ///список МРО получен от сервера 
    connect(m_pWorkerClient, SIGNAL(userReady(const User&)), this, SIGNAL(userReady(const User&)));
    ///список МРО получен от сервера 
    connect(m_pWorkerClient, SIGNAL(listMroReady(const QList<Mro>&)), this,
            SIGNAL(listMroReady(const QList<Mro>&)));
    ///список инспекций  получен от сервера 
    connect(m_pWorkerClient, SIGNAL(listInspectionsReady(const QList<Inspection>&)), this,
            SIGNAL(listInspectionsReady(const QList<Inspection>&)));

    ///список пользователей получен от сервера 
    connect(m_pWorkerClient, SIGNAL(listUserReady(const QList<UserView>&)), this,
            SIGNAL(listUserReady(const QList<UserView>&)));

    //connect(m_pWorkerClient, &WorkerClient::addUser, this, &ClientController::addModel<User>);
    //connect(m_pWorkerClient, SIGNAL(addUser(const User&)), SLOT(addModel<User>(const User&)));



    ///список НСИ получен от сервера 
    connect(m_pWorkerClient, SIGNAL(listNsiReady(const QList<Nsi>&)), this,
            SIGNAL(listNsiReady(const QList<Nsi>&)));

    // Сигнально-слотовое соединение  ожидания ответа от сервера.
    connect(m_pWorkerClient, SIGNAL(waitReady()), SLOT(waitReady()));
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






///Ждать сигнала готовности данных.

void ClientController::waitReady() {
    QEventLoop loop;
    connect(this, SIGNAL(ready()), &loop, SLOT(quit()));
    //connect(m_pWorkerClient, SIGNAL(ready()), &loop, SLOT(quit()));
    //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();
}

void ClientController::runServerCmd(const QString &asQuery) {
    //Создать командную обёртку.
    ModelWrapper wrapper;
    //Конвертировать данные  в JSON объект.
    JsonSerializer::parse(asQuery, wrapper);
    //Установить идентификатор сессии. 
    wrapper.setSessionID(m_aSessionID);
    //Упаковать  весь запрос в строку
    QString query = JsonSerializer::serialize(wrapper);
    //Переслпть его на сервер.
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

///Получить пользователя сессии

const User& ClientController::getSessionUser() {
    return m_aSessionUser;
}
///Установить пользователя сессии

void ClientController::setSessionUser(const User& user) {
    m_aSessionUser = user;
}

