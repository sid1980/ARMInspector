/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

class UserView : public JsonSerializable {
public:
    UserView();
    virtual ~UserView();
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
        const QJsonArray jsonArray = {"Идентификатор", "ФИО", "Инспекция", "Имя пользователя"};
        return jsonArray;
    }

    static const QString getModelName() {
        return QString("UserView");
    }

    static const QString getQuery() {
        return QString("Select u.id,fio,name_i,name  from user as u "
                "INNER JOIN inspection as i"
                "  ON u.id_inspection=i.id");
    }

    static const QString delQuery() {
        return QString("Delete   from user ");
    }

    QVariant getData(int position) const;
    void setData(int position, const QVariant& value);
    //QVariant getFieldValue() {
    //    return QVariant();
    //};

private:
    qint64 id_;
    QString fio_;
    QString inspection_;
    QString name_;

};

#endif /* UserView_H */

