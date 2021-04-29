/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **             Класс модели пользователя UserView.
 **             Используются для вывода данных о пользователе списком
 **
 ****************************************************************************/

/* 
 * File:   UserView.h
 * Author: kazun_as
 *
 * Created on 5 апреля 2021 г., 10:41
 */

#ifndef UserView_H
#define UserView_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <array>
#include <MQuery.h>

using namespace std;

class UserView : public JsonSerializable, Model {
public:

    enum Column {
        ID = 0,
        FIO,
        INSPECTION,
        NAME
    };
    ///конструктор
    UserView();
    ///деструктор
    virtual ~UserView();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setFio(const QString& fio);
    void setInspection(const QString& inspection);
    void setName(const QString& name);
    const qint64& getId()const;
    const QString& getFio()const;
    const QString& getInspection()const;
    const QString& getName()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий полей базы

    static array<QString, 4> getFields() {
        return array<QString, 4>{
            "id",
            "fio",
            "inspection",
            "name"};
    }

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "ФИО", "Инспекция", "Имя пользователя"};
        return jsonArray;
    }

    ///название модели

    static const QString getModelName() {
        return QString("UserView");
    }

    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select u.id,fio,name_i,name  from user as u "
                "INNER JOIN inspection as i"
                "  ON u.id_inspection=i.id");
    }

    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from user ");
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);

private:
   MQuery<UserView> query_;



    qint64 id_;
    QString fio_;
    QString inspection_;
    QString name_;

};

#endif /* UserView_H */

