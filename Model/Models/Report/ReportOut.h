/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReportOut.h
 * Author: kazun_as
 *
 * Created on 20 мая 2021 г., 09:22
 */

#ifndef REPORTOUT_H
#define REPORTOUT_H
#include <QtCore/QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include "JsonSerializable.h"
#include "Model.h"
#include <array>
#include <QSqlQuery>
#include <MQuery.h>
#include "ModelWrapper.h"
#define OUT_COLUMN 1
using namespace std;

class ReportOut : public JsonSerializable {
public:
    static ModelWrapper::Model model_;
     enum Column {
        COUNT = 0
    };
    ReportOut();
    virtual ~ReportOut();
    ///Функции чтения - записи полей класса
    void setCount(const qint64&);
    const qint64& getCount()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;
    
    ///Список названий полей базы
    static array<QString, OUT_COLUMN> getFields() {
        return array<QString, OUT_COLUMN>{
            "count"};
    }
private:
    qint64 count_;
};

#endif /* REPORTOUT_H */

