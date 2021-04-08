/****************************************************************************
 **
 ** Реализация методов вспомогательный класса для организации отдельного потока 
 ** и работы  с базой данных.
 **
 ****************************************************************************/

#include "Worker.h"
#include "User.h"
#include <QScopedPointer>
//#include <memory> C++ 14



/// Стандартный конструктор.
/// @param apParent Родитель.

Worker::Worker(QObject *apParent) : QObject(apParent) {
}


///Деструктор.

Worker::~Worker() {
    //Освободить  ресурсы
    qDebug() << "Stop Worker";

}
/// Инициализировать строку командной обёртки.
/// @param asWrapperString Строка инициализации командной обёртки

void Worker::setModelWrapperString(const QString& asWrapperString) {
    m_aModelWrapperString = asWrapperString;
}

/// Получить строку командной обёртки.
/// @return Возвращает строку командной обёртки.

const QString& Worker::getModelWrapperString() const {
    return m_aModelWrapperString;
}






///Основная функция  потока, который создаётся в сеансе.
///Создает экземпляр класса управления базой данных DBManager.
///Прозводит обработку  данных, пришедших от клиента.
///Возвращает результат обработки данных.
///Все действия производятся через командную обёртку.

void Worker::process() {
    //Создать  командную обёртку. 
    ModelWrapper wrapper;
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [ &wrapper](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        wrapper.setMessage(result.str);
        wrapper.setSuccess(result.success);
    };
    //Создать экземпляр класса управления базой данных.
    //DBManager *pDBManager = new DBManager();
    QScopedPointer<DBManager> pDBManager(new DBManager());
    if (pDBManager != nullptr) {
        //Экземпляр класса управления базой данных создан успешно.
        //Конвертировать данные, пришедшие  от клиента в JSON объект.
        JsonSerializer::parse(m_aModelWrapperString, wrapper);
        //Читать команду, которую  необходимо выполнить на сервере.
        ModelWrapper::Command command = wrapper.getEnumCommand();
        ///Передать данные DBManager.
        pDBManager->setModelWrapper(&wrapper);
        //Подключаемся к базе данных.
        bool ok = pDBManager->addDataBase();
        if (ok) {
            //Подключение к базе данных успешно добавлено.
            //Выбрать команду, которую нужно выполнить. 
            switch (command) {
                case ModelWrapper::Command::LOGIN:
                {
                    //Авторизация.
                    pDBManager->login();
                }
                    break;
                case ModelWrapper::Command::ADD_NEW_USER:
                {
                    //Добавление нового пользователя .
                    pDBManager->addUser();
                }
                    break;
                case ModelWrapper::Command::GET_LIST_MODELS:
                {
                    //Получить список моделей.
                    pDBManager->getListModels();
                }
                    break;
                default:
                {
                    setResult(Message::INCORRECT_COMMAND);
                }
                    break;
            }
            ///Удаляем подключение  к базе данных.
            pDBManager->removeDatabase();
        }
        //Удалить экземпляр класса управления базой данных.
        //delete pDBManager;
    } else {
        //Не удалось создать экземпляр класса  управления базой данных.
        setResult(Message::FAILED_CREATE_DBMANAGER);
    }
    //Сериализовать  результат.
    m_aModelWrapperString = JsonSerializer::serialize(wrapper);
    //Сигнализировать о завершении  обработки информации.
    emit finished(m_aModelWrapperString);
}
