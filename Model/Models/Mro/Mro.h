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
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>

#define MRO_COLUMN 3
#define DATA    "data"
#define ID_    "ID"

using namespace std;

class Mro : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NAME,
        INSPECTION
    };
    Mro();
    virtual ~Mro();
    void setId(const qint64& id);
    void setName(const QString& name);
    void setInspection(const QString& inspection);
    const qint64& getId()const;
    const QString& getName()const;
    const QString& getInspection()const;
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

    static array<QString, MRO_COLUMN> getFields() {
        return array<QString, MRO_COLUMN>{
            "id",
            "name",
            "inspection",};
    }


    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);

    void bindData(QSqlQuery* asSqlQuery);
    const QString& insert();



private:
    MQuery<Mro> query_;
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///Название МРО 
    QString name_;
    ///Идентификатор инспекции
    QString inspection_;

};

#endif /* MRO_H */

