/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************
 **
 **             Класс модели инспекции Inspection.
 **
 ****************************************************************************/

/* 
 * File:   Inspection.cpp
 * Author: kazun
 * 
 * 
 * Created on 3 апреля 2021 г., 21:58
 */

#include "Inspection.h"
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

Inspection::Inspection() {
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

Inspection::~Inspection() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void Inspection::setId(const qint64& id) {
    id_ = id;
};

void Inspection::setName(const QString& name) {
    name_ = name;
};

void Inspection::setMro(const qint64& mro) {
    mro_ = mro;
};

const qint64& Inspection::getId()const {
    return id_;
};

const QString& Inspection::getName()const {
    return name_;
};

const qint64& Inspection::getMro()const {
    return mro_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Inspection::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setName(jsonObj["name_i"].toString());
    this->setMro(jsonObj["id_mro"].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Inspection::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["name_i"] = this->getName();
    jsonObj["id_mro"] = this->getMro();
};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Inspection::getData(const int& position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getName();
        case 2:
            return this->getMro();
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

void Inspection::setData(const int& position, const QVariant& value) {
    switch (position) {
        case 0:
            this->setId(value.toInt());
            break;
        case 1:
            this->setName(value.toString());
            break;
        case 2:
            this->setMro(value.toInt());
            break;
        default:
            break;
    }

};
