/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mro.h
 * Author: kazun_as
 *
 * Created on 20 апреля 2021 г., 15:36
 */

#ifndef MRO_H
#define MRO_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"

class Mro: public JsonSerializable, Model
 {
public:
    Mro();
    virtual ~Mro();
    void setId(const qint64& id);
    void setName(const QString& name);
    void setInspection(const qint64& inspection);
    const qint64& getId()const;
    const QString& getName()const;
    const qint64& getInspection()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;
    
        ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "Название ",
            "Инспекция",
        };
        return jsonArray;
    }

    ///Список названий полей базы
    static const QJsonArray getFieldArray() {
        const QJsonArray jsonArray = {
            "id",
            "name",
            "id_inspection",
        };
        return jsonArray;
    }


    ///название модели
    static const QString getModelName() {
        return QString("Mro");
    }
    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select *  from mro ");
    }
    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from mro ");
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);


    
private:
//Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///Название МРО 
    QString name_;
    ///Идентификатор инспекции
    qint64 inspection_;

};

#endif /* MRO_H */
