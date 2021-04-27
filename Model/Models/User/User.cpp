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
    
    this->setId(jsonObj[fld_[Column::ID]].toInt());
    this->setFio(jsonObj[fld_[Column::FIO]].toString());
    this->setInspection(jsonObj[fld_[Column::ID_INSPECTION]].toInt());
    this->setName(jsonObj[fld_[Column::NAME]].toString());
    this->setPassword(jsonObj[fld_[Column::PASSWORD]].toString());
    this->setStatus(jsonObj[fld_[Column::STATUS]].toInt());
    this->setRole(jsonObj[fld_[Column::ROLE]].toInt());
    this->setAccess(jsonObj[fld_[Column::ACCESS]].toInt());
    this->setClaim(jsonObj[fld_[Column::CLAIM]].toInt());
    this->setPosition(jsonObj[fld_[Column::POSITION]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void User::write(QJsonObject &jsonObj) const {

    jsonObj[fld_[Column::ID]] = this->getId();
    jsonObj[fld_[Column::FIO]] = this->getFio();
    jsonObj[fld_[Column::ID_INSPECTION]] = this->getInspection();
    jsonObj[fld_[Column::NAME]] = this->getName();
    jsonObj[fld_[Column::PASSWORD]] = this->getPassword();
    jsonObj[fld_[Column::STATUS]] = this->getStatus();
    jsonObj[fld_[Column::ROLE]] = this->getRole();
    jsonObj[fld_[Column::ACCESS]] = this->getAccess();
    jsonObj[fld_[Column::CLAIM]] = this->getClaim();
    jsonObj[fld_[Column::POSITION]] = this->getPosition();

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



