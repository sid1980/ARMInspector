/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nsi.cpp
 * Author: kazun_as
 * 
 * Created on 23 апреля 2021 г., 16:15
 */

#include "Nsi/Nsi.h"
QString Nsi::num_ = {""};

Nsi::Nsi() {
}

Nsi::Nsi(const QString& num) {
    Nsi::num_ = num;
}

Nsi::~Nsi() {
}

void Nsi::setId(const qint64& id) {
    id_ = id;
};

void Nsi::setName(const QString& name) {
    name_ = name;
};

const qint64& Nsi::getId() const {
    return id_;
};

const QString& Nsi::getName() const {
    return name_;
};



///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Nsi::read(const QJsonObject &jsonObj) {
    array<QString, 2> fld = Nsi::getFields();
    this->setId(jsonObj[fld[Column::ID]].toInt());
    this->setName(jsonObj[fld[Column::NAME]].toString());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Nsi::write(QJsonObject &jsonObj) const {
    array<QString, 2> fld = Nsi::getFields();
    jsonObj[fld[Column::ID]] = this->getId();
    jsonObj[fld[Column::NAME]] = this->getName();

};


///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Nsi::getData(const int& position) const {

    switch (position) {
        case Column::ID:
            return this->getId();
        case Column::NAME:
            return this->getName();
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

void Nsi::setData(const int& position, const QVariant& value) {
    switch (position) {
        case Column::ID:
            this->setId(value.toInt());
            break;
        case Column::NAME:
            this->setName(value.toString());
            break;
        default:
            break;
    }

};

