/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReportOut.cpp
 * Author: kazun_as
 * 
 * Created on 20 мая 2021 г., 09:22
 */

#include "ReportOut.h"

ReportOut::ReportOut() {
}
ReportOut::~ReportOut() {
}

///Функции чтения - записи полей класса

void ReportOut::setCount(const qint64& count) {
    count_ = count;
}
const qint64& ReportOut::getCount()const {
    return count_;
}
///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void ReportOut::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Report::getFieldArray();
    array<QString, OUT_COLUMN> fld = ReportOut::getFields();

    this->setCount(jsonObj[fld[ReportOut::Column::COUNT]].toInt());

}
///Запись полей класса в JSON объкт. 

void ReportOut::write(QJsonObject &jsonObj) const {

    array<QString, OUT_COLUMN> fld = ReportOut::getFields();
    jsonObj[fld[ReportOut::Column::COUNT]] = this->getCount();
}
