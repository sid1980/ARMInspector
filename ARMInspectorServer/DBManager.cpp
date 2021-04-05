/****************************************************************************
 **
 ** Реализация  методов  класса DBManager.
 **
 ****************************************************************************/

#include "DBManager.h"
#include "User.h"
#include "UserV1.h"
#include "Inspection.h"


/// Стандартный конструктор.
/// @param apParent Родитель.

DBManager::DBManager(QObject *apParent) : QObject(apParent) {
}


///Инициализировать указатель на класс командной обёртки .

void DBManager::setModelWrapper(ModelWrapper* wrapper) {

    m_pModelWrapper = wrapper;
}
///Получить  указатель на класс командной обёртки.

const ModelWrapper* DBManager::getModelWrapper() const {

    return m_pModelWrapper;
}



/// Подключиться к базе данных. Открыть  базу данных.

bool DBManager::addDataBase() {
    //Блокировать ресурсы SQL от использования их  другими пользователями. 
    QMutexLocker lock(&m_Mutex);
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    const QString DRIVER("QODBC3");
    if (!QSqlDatabase::isDriverAvailable(DRIVER)) {
        setResult(Message::DATABASE_DRIVER_IS_NOT_AVAILABLE);
        return false;
    }
    //Добавить  подключение клиента в список подключений к базе данных 
    QSqlDatabase database = QSqlDatabase::addDatabase(DRIVER, QString().setNum(m_pModelWrapper->getSessionID()));
    if (database.isValid()) {
        database.setDatabaseName("DRIVER={MySQL ODBC 8.0 Unicode Driver};SERVER=localhost;DATABASE=gu_delinq;Uid=test;Pwd=tst;");
        //database.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");
        //database.setDatabaseName("arm");
        //database.setUserName("test");
        //database.setHostName("localhost");
        //database.setPort(3306);
        //        //database.setPassword("tst");
        //Открыть базу данных
        if (!database.open()) {
            qDebug() << "FAILURE.db is not opened";
            //База данных не открыта.Авторизация не возможна.
            setResult(Message::UNABLE_OPEN_DATABASE);
            return false;
        }
        qDebug() << "SUCEESS. db is opened";
        qDebug() << "CONNECT " << QString().setNum(m_pModelWrapper->getSessionID());
        return true;
    } else {
        setResult(Message::UNABLE_CONNECT_DATABASE);
        return false;
    }
}




/// Авторизация пользователя.

void DBManager::login() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Загрузить параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //Имя пользователя.
    QString asLogin = param["name"].toString();
    //Пароль.
    QString asPassword = param["password"].toString();
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    //Создать модель данных User
    User user;
    //Взять ранее созданное подключение к  базе данных.
    QSqlDatabase database = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
    //Проверить подключение  к  базе данных.
    if (!database.isValid()) {
        //Подключение  к базе данных некорректно.
        //Установить сообщение.
        setResult(user, Message::DATABASE_CONNECTION_INCORRECT);
        //Прекратить работу менеджера базы данных.
        return;
    }

    //Проверить, открыта ли база данных.
    if (!database.isOpen()) {
        //База данных не открыта.Авторизация не возможна.
        setResult(user, Message::DATABASE_IS_NOT_OPENED);
        return;
    }

    //База данных открыта. Можно проводить авторизацию пользователя. 

    QSqlQuery queryStatementInfo(database);
    //Подготовить запрос на чтение данных из  базы.
    QString strGetStatementInfo = "select * from user where name='" + asLogin + "'";

    //Выполнить зыпрос к базе данных.
    if (!queryStatementInfo.exec(strGetStatementInfo)) {
        setResult(user, Message::SQL_ERROR);
        return;
    }
    //Проверить, есть ли в базе данных хотя бы одна запись, удовлетворяющая запросу    
    if (!queryStatementInfo.next()) {
        //Пользователя с таким именем нет в базе данных. 
        //Если это admin , то добавить его и установить пароль по умолчанию
        if (asLogin == "admin") {
            QString pasword_hash = QString(QCryptographicHash::hash(("adm11"), QCryptographicHash::Md5).toHex());
            //QString sqlquery_string = QString("INSERT INTO user(name,password) VALUES ('admin','") + pasword_hash + QString("')");
            QString sqlquery_string = QString("INSERT INTO user(name,password) VALUES (:name,:password)");
            queryStatementInfo.prepare(sqlquery_string);
            queryStatementInfo.bindValue(":name", asLogin);
            queryStatementInfo.bindValue(":password", pasword_hash);
            if (!queryStatementInfo.exec()) {
                setResult(user, Message::CANNOT_ADD_ADMIN_USER);
                return;
            } else {
                setResult(user, Message::ADD_ADMIN_USER_SUCCESS);
                //Пользователь admin успешно добавлен в базу данных
                return;
            }
        } else {
            setResult(user, Message::USER_IS_NOT_FOUND);
            return;
        }
    }
    //JSON объект для хранения записи базы данных.
    QJsonObject recordObject;
    //Скопировать запись базы данных в JSON объект.
    for (int x = 0; x < queryStatementInfo.record().count(); x++) {
        //qDebug() << queryStatementInfo.value(x);
        recordObject.insert(queryStatementInfo.record().fieldName(x), QJsonValue::fromVariant(queryStatementInfo.value(x)));
    }
    ///Считать данные JSON объекта  в объект класса User.  
    user.read(recordObject);
    //Имя пользователя найдено. Прверить пароль прользователя.Получить хеш пароля.
    QString pasword_hash = QString(QCryptographicHash::hash((asPassword.toStdString().c_str()), QCryptographicHash::Md5).toHex());
    //Сравнить его с хеш в базе данных
    if (pasword_hash.compare(user.getPassword().trimmed(), Qt::CaseSensitive) != 0) {
        //Пользователь не прошёл авторизацию. Пароль неверен. 
        setResult(user, Message::USERR_LOGIN_FAILURE);
        return;
    }
    //Пароль введённый пользователем и пароль в базе данных совпали. Пользователь  прошёл авторизацию. 
    setResult(user, Message::USER_LOGIN_SUCCESS);

    return;
    //}
}

///Выполнить запрос к базе данных.

void DBManager::getListModels() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
            getListModels<User>();
            break;
        case ModelWrapper::Model::UserV1:
            getListModels<UserV1>();
            break;
        case ModelWrapper::Model::Inspection:
            getListModels<Inspection>();
            break;

    }

}



/// Отключить клиента от сервера
/// @param apClientSocket Указатель на сокет клиент-серверного соединения.

void DBManager::removeDatabase() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    QMutexLocker lock(&m_Mutex);
    //Закрыть подключение  к базе данных.Освободить ресурсы.
    {
        QSqlDatabase database = QSqlDatabase::database(QString().setNum(m_pModelWrapper->getSessionID()));
        if (database.isOpen()) {

            database.close();
            qDebug() << "db  closed";
        }
    }
    //Удалить подключение к базе данных из списка QSqlDatabase
    QSqlDatabase::removeDatabase(QString().setNum(m_pModelWrapper->getSessionID()));
}







