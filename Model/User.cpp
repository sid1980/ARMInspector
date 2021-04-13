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

#include "User.h"
///-----------------------------------------------------------------------------
///
///         Стандартный конструктор.
///          
///-----------------------------------------------------------------------------

User::User() : id_(0), fio_(""), inspection_(0), name_(""), password_(""), status_(0), role_(0), access_(0), claim_(0), position_(0) {
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
    this->setId(jsonObj["id"].toInt());
    this->setFio(jsonObj["fio"].toString());
    this->setInspection(jsonObj["id_inspection"].toInt());
    this->setName(jsonObj["name"].toString());
    this->setPassword(jsonObj["password"].toString());
    this->setStatus(jsonObj["status"].toInt());
    this->setRole(jsonObj["role"].toInt());
    this->setAccess(jsonObj["access"].toInt());
    this->setClaim(jsonObj["claim"].toInt());
    this->setPosition(jsonObj["position"].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void User::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["fio"] = this->getFio();
    jsonObj["id_inspection"] = this->getInspection();
    jsonObj["name"] = this->getName();
    jsonObj["password"] = this->getPassword();
    jsonObj["status"] = this->getStatus();
    jsonObj["role"] = this->getRole();
    jsonObj["access"] = this->getAccess();
    jsonObj["claim"] = this->getClaim();
    jsonObj["position"] = this->getPosition();

};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant User::getData(const int& position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getFio();
        case 2:
            return this->getInspection();
        case 3:
            return this->getName();
        case 4:
            return this->getPassword();
        case 5:
            return this->getStatus();
        case 6:
            return this->getRole();
        case 7:
            return this->getAccess();
        case 8:
            return this->getClaim();
        case 9:
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
        case 0:
            this->setId(value.toInt());
            break;
        case 1:
            this->setFio(value.toString());
            break;
        case 2:
            this->setInspection(value.toInt());
            break;
        case 3:
            this->setName(value.toString());
            break;
        case 4:
            this->setPassword(value.toString());
            break;
        case 5:
            this->setStatus(value.toInt());
            break;
        case 6:
            this->setRole(value.toInt());
            break;
        case 7:
            this->setAccess(value.toInt());
            break;
        case 8:
            this->setClaim(value.toInt());
            break;
        case 9:
            this->setPosition(value.toInt());
            break;
        default:
            break;
    }

};



