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
 * File:   Inspection.h
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 21:58
 */

#ifndef INSPECTION_H
#define INSPECTION_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>

class Inspection : public JsonSerializable {
public:
    ///Конструктор
    Inspection();
    ///деструктор
    virtual ~Inspection();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setName(const QString& name);
    void setMro(const qint64& mro);
    const qint64& getId()const;
    const QString& getName()const;
    const qint64& getMro()const;

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "Название", "МРО"};
        return jsonArray;
    }

    ///название модели

    static const QString getModelName() {
        return QString("Inspection");
    }

    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select *  from inspection ");
    }

    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from inspection ");
    }


    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);


private:
    qint64 id_;
    QString name_;
    qint64 mro_;

};

#endif /* INSPECTION_H */

