/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumn.h
 * Author: kazun_as
 *
 * Created on 23 апреля 2021 г., 15:14
 */

#ifndef RPTCOLUMN_H
#define RPTCOLUMN_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include "ModelWrapper.h"
#include <MQuery.h>
#include <array>
#define RPT_COLUMN 4

using namespace std;

class RptColumn : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;
    RptColumn();
    virtual ~RptColumn();
    void setId(const qint64& id);
    void setArticle(const qint64& article);
    void setOffenseSubject(const qint64& offense_subject);
    void setCol(const qint64& col);
    const qint64& getId()const;
    const qint64& getArticle()const;
    const qint64& getOffenseSubject()const;
    const qint64& getCol()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "Статья",
            "Тип нарушиля",
            "№ колонки отчёта",
        };
        return jsonArray;
    }


    
    
    ///Список названий полей базы

    static array<QString, RPT_COLUMN> getFields() {
        return array<QString, RPT_COLUMN>{
            "id",
            "article",
            "offense_subject",
            "col"};
    }
    ///название модели

    static const QString getModelName() {
        return QString("RptColumn");
    }
    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select *  from rpt_column ");
    }
    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from rpt_column ");
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);



private:
    MQuery<RptColumn> query_;
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///Статья КоАП
    qint64 article_;
    ///Тип нарушителя
    qint64 offense_subject_;
    ///Колонка отчёта
    qint64 col_;


};

#endif /* RPTCOLUMN_H */

