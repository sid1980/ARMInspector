/****************************************************************************
 **
 **             Класс модели пользователя User.
 **
 ****************************************************************************/

/* 
 * File:   User.cpp
 * Author: 1
 * 
 * Created on 20 ноября 2019 г., 15:47
 */

#include "User/User.h"
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

User::User() : id_(0), fio_(""), inspection_(0), name_(""), password_(""),
status_(0), role_(0), access_(0), claim_(0), position_(0) {
}
///-----------------------------------------------------------------------------
///
///         Стандартный деструктор.
///          
///-----------------------------------------------------------------------------

User::~User() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void User::setId(const qint64& id) {
    id_ = id;
};

void User::setFio(const QString& fio) {
    fio_ = fio;
};

void User::setInspection(const qint64& inspection) {
    inspection_ = inspection;
};

void User::setName(const QString& name) {
    name_ = name;
};

void User::setPassword(const QString& password) {
    password_ = password;
};

void User::setStatus(const qint64& status) {
    status_ = status;
};

void User::setRole(const qint64& role) {
    role_ = role;
};

void User::setAccess(const qint64& access) {
    access_ = access;
};

void User::setClaim(const qint64& claim) {
    claim_ = claim;
};

void User::setPosition(const qint64& position) {
    position_ = position;
};

const qint64& User::getId() const {
    return id_;
};

const QString& User::getFio() const {
    return fio_;
};

const qint64& User::getInspection() const {
    return inspection_;
};

const QString& User::getName() const {
    return name_;
};

const QString& User::getPassword()const {
    return password_;
};

const qint64& User::getStatus() const {
    return status_;
};

const qint64& User::getRole() const {
    return role_;
};

const qint64& User::getAccess() const {
    return access_;
};

const qint64& User::getClaim() const {
    return claim_;
};

const qint64& User::getPosition() const {
    return position_;
};
///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void User::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=User::getFieldArray();
    array<QString, 10> fld = User::getFields();

    this->setId(jsonObj[fld[Column::ID]].toInt());
    this->setFio(jsonObj[fld[Column::FIO]].toString());
    this->setInspection(jsonObj[fld[Column::ID_INSPECTION]].toInt());
    this->setName(jsonObj[fld[Column::NAME]].toString());
    this->setPassword(jsonObj[fld[Column::PASSWORD]].toString());
    this->setStatus(jsonObj[fld[Column::STATUS]].toInt());
    this->setRole(jsonObj[fld[Column::ROLE]].toInt());
    this->setAccess(jsonObj[fld[Column::ACCESS]].toInt());
    this->setClaim(jsonObj[fld[Column::CLAIM]].toInt());
    this->setPosition(jsonObj[fld[Column::POSITION]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void User::write(QJsonObject &jsonObj) const {
    array<QString, 10> fld = User::getFields();

    jsonObj[fld[Column::ID]] = this->getId();
    jsonObj[fld[Column::FIO]] = this->getFio();
    jsonObj[fld[Column::ID_INSPECTION]] = this->getInspection();
    jsonObj[fld[Column::NAME]] = this->getName();
    jsonObj[fld[Column::PASSWORD]] = this->getPassword();
    jsonObj[fld[Column::STATUS]] = this->getStatus();
    jsonObj[fld[Column::ROLE]] = this->getRole();
    jsonObj[fld[Column::ACCESS]] = this->getAccess();
    jsonObj[fld[Column::CLAIM]] = this->getClaim();
    jsonObj[fld[Column::POSITION]] = this->getPosition();
};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant User::getData(const int& position) const {

    switch (position) {
        case Column::ID:
            return this->getId();
        case Column::FIO:
            return this->getFio();
        case Column::ID_INSPECTION:
            return this->getInspection();
        case Column::NAME:
            return this->getName();
        case Column::PASSWORD:
            return this->getPassword();
        case Column::STATUS:
            return this->getStatus();
        case Column::ROLE:
            return this->getRole();
        case Column::ACCESS:
            return this->getAccess();
        case Column::CLAIM:
            return this->getClaim();
        case Column::POSITION:
            return this->getPosition();
        default:
            return 0;
            break;
    }
};

///-----------------------------------------------------------------------------
///
///         Записать  данные в любое з поле класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

void User::setData(const int& position, const QVariant& value) {
    switch (position) {
        case Column::ID:
            this->setId(value.toInt());
            break;
        case Column::FIO:
            this->setFio(value.toString());
            break;
        case Column::ID_INSPECTION:
            this->setInspection(value.toInt());
            break;
        case Column::NAME:
            this->setName(value.toString());
            break;
        case Column::PASSWORD:
            this->setPassword(value.toString());
            break;
        case Column::STATUS:
            this->setStatus(value.toInt());
            break;
        case Column::ROLE:
            this->setRole(value.toInt());
            break;
        case Column::ACCESS:
            this->setAccess(value.toInt());
            break;
        case Column::CLAIM:
            this->setClaim(value.toInt());
            break;
        case Column::POSITION:
            this->setPosition(value.toInt());
            break;
        default:
            break;
    }

};

///-----------------------------------------------------------------------------
///
///         Привязать данны к запросу. 
///
///
///-----------------------------------------------------------------------------

void User::bindData(QSqlQuery* asSqlQuery) {
    qInfo() << "User::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, USER_COLUMN> fld = User::getFields();
        for (int i = 0; i < list.size(); i++) {
            qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Column::ID:
                    asSqlQuery->bindValue(":" + fld[Column::ID], this->getId());
                    break;
                case Column::FIO:
                    asSqlQuery->bindValue(":" + fld[Column::FIO], this->getFio());
                    break;
                case Column::ID_INSPECTION:
                    asSqlQuery->bindValue(":" + fld[Column::ID_INSPECTION], this->getInspection());
                    break;
                case Column::NAME:
                    asSqlQuery->bindValue(":" + fld[Column::NAME], this->getName());
                    break;
                case Column::PASSWORD:
                    asSqlQuery->bindValue(":" + fld[Column::PASSWORD], this->getPassword());
                    break;
                case Column::STATUS:
                    asSqlQuery->bindValue(":" + fld[Column::STATUS], this->getStatus());
                    break;
                case Column::ROLE:
                    asSqlQuery->bindValue(":" + fld[Column::ROLE], this->getRole());
                    break;
                case Column::ACCESS:
                    asSqlQuery->bindValue(":" + fld[Column::ACCESS], this->getAccess());
                    break;
                case Column::CLAIM:
                    asSqlQuery->bindValue(":" + fld[Column::CLAIM], this->getClaim());
                    break;
                case Column::POSITION:
                    asSqlQuery->bindValue(":" + fld[Column::POSITION], this->getPosition());
                    break;
            }
        }
    }
}

///-----------------------------------------------------------------------------
///
///         Изменить данные пользователя. 
///
///
///-----------------------------------------------------------------------------

const QString& User::update() {
    qInfo() << "User::update()";
    return query_.update()->set()->
            field(Column::ID)->equally()->bind(Column::ID)->
            field(Column::FIO)->equally()->bind(Column::FIO)->
            field(Column::ID_INSPECTION)->equally()->bind(Column::ID_INSPECTION)->
            field(Column::NAME)->equally()->bind(Column::NAME)->
            field(Column::STATUS)->equally()->bind(Column::STATUS)->
            field(Column::ROLE)->equally()->bind(Column::ROLE)->
            field(Column::ACCESS)->equally()->bind(Column::ACCESS)->
            where()->field(Column::ID)->equally()->bind(Column::ID)->
            prepare();

}

///-----------------------------------------------------------------------------
///
///         Изменить пароль пользователя . 
///
///
///-----------------------------------------------------------------------------

const QString& User::changePassword() {
    qInfo() << "User::changePassword()";
    return query_.update()->set()->
            field(User::Column::PASSWORD)->equally()->bind(User::Column::PASSWORD)->
            where()->field(User::Column::ID)->equally()->bind(User::Column::ID)->
            prepare();

}

///-----------------------------------------------------------------------------
///
///         Добавить пользователя . 
///
///
///-----------------------------------------------------------------------------

const QString& User::insert() {
    qInfo() << "User::insert()";
    return query_.insert()->
            field(Column::FIO)->
            field(Column::ID_INSPECTION)->
            field(Column::NAME)->
            field(Column::STATUS)->
            field(Column::ROLE)->
            field(Column::ACCESS)->prepare();
}


///-----------------------------------------------------------------------------
///
///         Выбрать  пользователя по имени. 
///
///
///-----------------------------------------------------------------------------

const QString& User::selectByName() {
    qInfo() << "User::selectByName()";
    return query_.select()->
            where()->field(User::Column::NAME)->equally()->bind(User::Column::NAME)->
            prepare();
}



