/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserV1.h
 * Author: kazun_as
 *
 * Created on 5 апреля 2021 г., 10:41
 */

#ifndef USERV1_H
#define USERV1_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>

class UserV1: public JsonSerializable  {
public:
    UserV1();
    virtual ~UserV1();
    void setId(const qint64& id);
    void setFio(const QString& fio);
    void setInspection(const QString& inspection);
    void setName(const QString& name);
    const qint64& getId()const;
    const QString& getFio()const;
    const QString& getInspection()const;
    const QString& getName()const;
    void read(const QJsonObject &jsonObj);
    void write(QJsonObject &jsonObj) const;

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "ФИО", "Инспекция","Имя пользователя"};
        return jsonArray;
    }

    static const QString getModelName() {
        return QString("UserV1");
    }
    QVariant getData(int position) const;
    //QVariant getFieldValue() {
    //    return QVariant();
    //};

private:
    qint64 id_;
    QString fio_;
    QString inspection_;
    QString name_;

};

#endif /* USERV1_H */

