/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mro.cpp
 * Author: kazun_as
 * 
 * Created on 20 апреля 2021 г., 15:36
 */

#include "Mro.h" 

Mro::Mro() : id_(0), name_(""), inspection_(0) {
}

Mro::~Mro() {
}

void Mro::setId(const qint64& id) {
    id_ = id;
};

void Mro::setName(const QString& name) {
    name_ = name;
};

void Mro::setInspection(const qint64& inspection) {
    inspection_ = inspection;
};

const qint64& Mro::getId() const {
    return id_;
};

const QString& Mro::getName() const {
    return name_;
};

const qint64& Mro::getInspection() const {
    return inspection_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Mro::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setName(jsonObj["name"].toString());
    this->setInspection(jsonObj["id_inspection"].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Mro::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["name"] = this->getName();
    jsonObj["id_inspection"] = this->getInspection();

};


///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Mro::getData(const int& position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getName();
        case 2:
            return this->getInspection();
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

void Mro::setData(const int& position, const QVariant& value) {
    switch (position) {
        case 0:
            this->setId(value.toInt());
            break;
        case 1:
            this->setName(value.toString());
            break;
        case 2:
            this->setInspection(value.toInt());
            break;
        default:
            break;
    }

};

