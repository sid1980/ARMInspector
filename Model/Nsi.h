/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nsi.h
 * Author: kazun_as
 *
 * Created on 23 апреля 2021 г., 16:15
 */

#ifndef NSI_H
#define NSI_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
class Nsi : public JsonSerializable, Model {
public:
    Nsi();
    Nsi(const QString& num);
    virtual ~Nsi();
    void setId(const qint64& id);
    void setName(const QString& name);
    const qint64& getId()const;
    const QString& getName()const;
    static QString num_;

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "№",
            "Название "
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static const QJsonArray getFieldArray() {
        const QJsonArray jsonArray = {
            "id",
            "name"
        };
        return jsonArray;
    }


    ///название модели

    static const QString getModelName() {
        return QString("Nsi_"+Nsi::num_);
    }
    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select id,name_" + Nsi::num_ +" as name   from nsi_" + Nsi::num_);
    }
    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from nsi_"+Nsi::num_);
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);


private:
    qint64 id_;
    QString name_;
};

#endif /* NSI_H */

