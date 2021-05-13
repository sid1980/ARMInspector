/****************************************************************************
 **
 ** Реализация  методов  класса DBManager.
 **
 ****************************************************************************/

#include "DBManager.h"
#include <QSqlError>


///-----------------------------------------------------------------------------
///         Стандартный конструктор.
///          @param apParent Родитель.
///-----------------------------------------------------------------------------

DBManager::DBManager(QObject *apParent) : QObject(apParent) {
}

///-----------------------------------------------------------------------------

///Инициализировать указатель на класс командной обёртки .
///-----------------------------------------------------------------------------

void DBManager::setModelWrapper(ModelWrapper* wrapper) {

    m_pModelWrapper = wrapper;
}
///-----------------------------------------------------------------------------
///
///             Получить  указатель на класс командной обёртки.
///
///-----------------------------------------------------------------------------

const ModelWrapper* DBManager::getModelWrapper() const {

    return m_pModelWrapper;
}


///-----------------------------------------------------------------------------
///
///              Подключиться к базе данных. Открыть  базу данных.
///
///-----------------------------------------------------------------------------

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
        //database.setUserName("");
        //database.setHostName("localhost");
        //database.setPort(3305);
        //database.setPassword("");
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



///-----------------------------------------------------------------------------
///
///             Авторизация пользователя.
///
///-----------------------------------------------------------------------------

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
    //Создать модель данных User
    User user;
    user.setName(asLogin);

    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str + QString("<a style='color:red'> ") + user.getName() + QString("</a>"));
        m_pModelWrapper->setSuccess(result.success);
    };
    if (!asLogin.isEmpty()&&!asPassword.isEmpty()) {
        //Взять ранее созданное подключение к  базе данных.
        if (!connectDB<User>()) {
            qDebug() << "DB not connected";
            return;
        }
        //База данных открыта. Можно проводить авторизацию пользователя. 

        QSqlQuery queryStatementInfo(m_Db);
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
                qDebug() << asLogin;
                QString pasword_hash = QString(QCryptographicHash::hash(("adm11"), QCryptographicHash::Md5).toHex());
                QString sqlquery_string = QString("INSERT INTO user(name,password)"
                        " VALUES ('admin','") + pasword_hash + QString("')");
                qDebug() << sqlquery_string;

                if (!queryStatementInfo.exec(sqlquery_string)) {
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
            setResult(user, Message::USER_LOGIN_FAILURE);
            return;
        }
        //Пароль введённый пользователем и пароль в базе данных совпали. Пользователь  прошёл авторизацию. 
        setResult(user, Message::USER_LOGIN_SUCCESS);

        return;
    } else {
        if (asLogin.isEmpty()) {
            setResult(user, Message::USER_NAME_EMPTY);
            return;
        }
        setResult(user, Message::USER_PASSWORD_EMPTY);
        return;
    }
}


///-----------------------------------------------------------------------------
///
///             Удалить модель
///
///-----------------------------------------------------------------------------

void DBManager::deleteModel() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
            deleteModel<User>();
            break;
        case ModelWrapper::Model::UserView:
            deleteModel<UserView>();
            break;
        case ModelWrapper::Model::Inspection:
            deleteModel<Inspection>();
            break;
        case ModelWrapper::Model::Nsi:
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            //            m_pModelWrapper->setData(param[DATA].toString());
            deleteModel<Nsi>();
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Добавить модель
///
///-----------------------------------------------------------------------------

void DBManager::addModel() {
    qInfo() << "Получаем модель";
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //номер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            m_pModelWrapper->setData(param[DATA].toString());
            //qInfo() << param[DATA].toString();
            addModel<Nsi>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            //qInfo() << param[DATA].toString();
            addModel<Mro>();
        }
            break;
        default:
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Редактировать модель
///
///-----------------------------------------------------------------------------

void DBManager::updateModel() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::Nsi:
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            m_pModelWrapper->setData(param[DATA].toString());
            updateModel<Nsi>();
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Получить модель
///
///-----------------------------------------------------------------------------

void DBManager::getModel() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
            getModel<User>();
            break;
        case ModelWrapper::Model::UserView:
            getModel<UserView>();
            break;
        case ModelWrapper::Model::Inspection:
            getModel<Inspection>();
            break;
        case ModelWrapper::Model::Nsi:
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            getModel<Nsi>();
            break;

    }
}
///-----------------------------------------------------------------------------
///
///                 Получить список моделей
///
///-----------------------------------------------------------------------------

void DBManager::getListModels() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
            getListModels<User>();
            break;
        case ModelWrapper::Model::Mro:
            getListModels<Mro>();
            break;
        case ModelWrapper::Model::MroView:
            getListModels<MroView>();
            break;
        case ModelWrapper::Model::UserView:
            getListModels<UserView>();
            break;
        case ModelWrapper::Model::Inspection:
            getListModels<Inspection>();
            break;
        case ModelWrapper::Model::Nsi:
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            //qDebug()<<"num_" << Nsi::num_;
            getListModels<Nsi>();
            break;

    }

}



///-----------------------------------------------------------------------------
///
///                      Отключить клиента от сервера
///                      @param apClientSocket 
///                      Указатель на сокет клиент-серверного соединения.
///
///-----------------------------------------------------------------------------

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

///-----------------------------------------------------------------------------
///
///                     Изменить пароль  пользователя 
///
///-----------------------------------------------------------------------------

void DBManager::changePassword() {
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
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<User>()) {
        return;
    }

    //База данных открыта. Можно проводить авторизацию пользователя. 
    QSqlQuery query(m_Db);
    QString pasword_hash = QString(QCryptographicHash::hash((user.getPassword().toStdString().c_str()), QCryptographicHash::Md5).toHex());
    user.setPassword(pasword_hash);
    query.prepare(user.changePassword());
    user.bindData(&query);
    if (query.exec()) {
        setResult(user, Message::PASSWORD_CHANGE_SUCCESS);
        qDebug() << user.getName();
        qDebug() << user.getId();
        qDebug() << "update user password  succes: ";
    } else {
        setResult(user, Message::PASSWORD_CHANGE_FAILURE);
        qDebug() << "update user password  failed: " << query.lastError();
        qDebug() << user.getName();
    }

    return;
}


///-----------------------------------------------------------------------------
///
///                     Редактировать пользователя 
///
///-----------------------------------------------------------------------------

void DBManager::updateUser() {
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
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    //qDebug() << myquery;
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<User>()) {
        return;
    }
    //База данных открыта. Можно проводить авторизацию пользователя. 
    QSqlQuery query(m_Db);
    //qDebug() << user.getName();
    query.prepare(user.update());
    user.bindData(&query);

    if (query.exec()) {
        setResult(user, Message::USER_EDIT_SUCCESS);
        qDebug() << user.getName();
        qDebug() << user.getId();
        qDebug() << "update user  succes: ";
    } else {
        setResult(user, Message::USER_EDIT_FAILURE);
        qDebug() << "update person failed: " << query.lastError();
        qDebug() << user.getName();
    }
    return;
}

///-----------------------------------------------------------------------------
///
///         Проверить имя пользователя
///
///-----------------------------------------------------------------------------

bool DBManager::isUserName(const QString& name) {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    User user;
    user.setName(name);
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str + QString("<br><a style='color:red'> ") +
                user.getName() +
                QString("</a> <br> Необходимо выбрать другое имя."));
        m_pModelWrapper->setSuccess(result.success);
    };
    QSqlQuery query(m_Db);
    query.prepare(user.selectByName());
    user.bindData(&query);
    if (!query.exec()) {
        setResult(user, Message::USER_ADD_FAILURE);
        return false;
    }
    if (!query.next()) {
        setResult(user, Message::USER_NAME_NO);
        return false;
    }
    QJsonObject recordObject;
    ///Экземпляр объекта класса T, который будет  сериализоваться.
    for (int x = 0; x < query.record().count(); x++) {
        recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
        qDebug() << "DBManager::isUserName(User user)";
    }
    ///Считать запись базы данных  в объект класса T.  
    user.read(recordObject);
    qInfo() << user.getName();
    setResult(user, Message::USER_NAME_IS);
    return true;
}

///-----------------------------------------------------------------------------
///
///         Добавить нового пользователя
///
///-----------------------------------------------------------------------------

void DBManager::addUser() {
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
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    //Взять ранее созданное подключение к  базе данных.
    if (!connectDB<User>()) {
        return;
    }
    if (isUserName(user.getName())) {
        return;
    }

    QString pasword_hash = QString(QCryptographicHash::hash((user.getPassword().toStdString().c_str()), QCryptographicHash::Md5).toHex());
    user.setPassword(pasword_hash);
    qInfo() << user.insert();
    //База данных открыта. Можно проводить авторизацию пользователя. 

    QSqlQuery query(m_Db);
    query.prepare(user.insert());
    user.bindData(&query);

    //queryAdd.prepare("INSERT INTO user (fio,id_inspection,name,password,status,role,access)"
    //        " VALUES (:fio,:id_inspection,:name,:password,:status,:role,:access)");
    //queryAdd.bindValue(":fio", user.getFio());
    //queryAdd.bindValue(":id_inspection", user.getInspection());
    //queryAdd.bindValue(":name", user.getName());
    //Получить хеш пароля.
    //queryAdd.bindValue(":password", pasword_hash);
    //queryAdd.bindValue(":status", user.getStatus());
    //queryAdd.bindValue(":role", user.getRole());
    //queryAdd.bindValue(":access", user.getAccess());

    if (query.exec()) {
        //query.prepare("SELECT * FROM user WHERE ID = (SELECT max(ID) FROM user)");
        query.prepare(MQuery<User>::selectMaxID());
        if (!query.exec()) {
            setResult(user, Message::USER_ADD_FAILURE);
            return;
        }
        //Выборка данных.
        while (query.next()) {
            QJsonObject recordObject;
            ///Экземпляр объекта класса T, который будет  сериализоваться.
            for (int x = 0; x < query.record().count(); x++) {
                recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
            }
            ///Считать запись базы данных  в объект класса T.  
            user.read(recordObject);
        }
        setResult(user, Message::USER_ADD_SUCCESS);
        qDebug() << user.getName();
        qDebug() << user.getId();
        qDebug() << "add user  succes: ";
    } else {
        setResult(user, Message::USER_ADD_FAILURE);
        qDebug() << "add person failed: " << query.lastError();
        qDebug() << user.getName();
    }

    return;
}










