/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    Inspection();
    //Inspection(const Inspection& orig);
    virtual ~Inspection();
    void setId(const qint64& id);
    void setName(const QString& name);
    void setMro(const qint64& mro);
    const qint64& getId()const;
    const QString& getName()const;
    const qint64& getMro()const;
    void read(const QJsonObject &jsonObj);
    void write(QJsonObject &jsonObj) const;

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "Название", "МРО"};
        return jsonArray;
    }

    static const QString getModelName() {
        return QString("Inspection");
    }

    static const QString getQuery() {
        return QString("Select *  from inspection ");
    }

    QVariant getData(int position) const;


private:
    qint64 id_;
    QString name_;
    qint64 mro_;

};

#endif /* INSPECTION_H */

