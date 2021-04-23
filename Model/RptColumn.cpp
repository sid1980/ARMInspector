/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumn.cpp
 * Author: kazun_as
 * 
 * Created on 23 апреля 2021 г., 15:14
 */

#include "RptColumn.h"

RptColumn::RptColumn() {
}


RptColumn::~RptColumn() {
}

///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void RptColumn::setId(const qint64& id) {
    id_ = id;
};
void RptColumn::setArticle(const qint64& article) {
    article_ = article;
};
void RptColumn::setOffenseSubject(const qint64& offense_subject) {
    offense_subject_ = offense_subject;
};
void RptColumn::setCol(const qint64& col) {
    col_ = col;
};


const qint64& RptColumn::getId() const {
    return id_;
};
const qint64& RptColumn::getArticle() const {
    return article_;
};
const qint64& RptColumn::getOffenseSubject() const {
    return offense_subject_;
};
const qint64& RptColumn::getCol() const {
    return col_;
};


///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void RptColumn::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setArticle(jsonObj["article"].toInt());
    this->setOffenseSubject(jsonObj["offense_subject"].toInt());
    this->setCol(jsonObj["col"].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void RptColumn::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["article"] = this->getArticle();
    jsonObj["offense_subject"] = this->getOffenseSubject();
    jsonObj["col"] = this->getCol();

};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant RptColumn::getData(const int& position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getArticle();
        case 2:
            return this->getOffenseSubject();
        case 3:
            return this->getCol();
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

void RptColumn::setData(const int& position, const QVariant& value) {
    switch (position) {
        case 0:
            this->setId(value.toInt());
            break;
        case 1:
            this->setArticle(value.toInt());
            break;
        case 2:
            this->setOffenseSubject(value.toInt());
            break;
        case 3:
            this->setCol(value.toInt());
            break;
        default:
            break;
    }

};
