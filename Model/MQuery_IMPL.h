/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQuery_IMPL.h
 * Author: kazun_as
 * 
 * Created on 28 апреля 2021 г., 10:14
 */
#ifndef MQUERY_IMPL_H
#define MQUERY_IMPL_H

#include "MQuery.h"



///-----------------------------------------------------------------------------
///
///             Получить список привязанных к запросу полей.
///
///-----------------------------------------------------------------------------

template <class T> const QList<int>& MQuery<T>::getBindColumnList() {
    return bind_;
}
///-----------------------------------------------------------------------------
///
///             Выбрать записи.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::select() {
    clear();
    QString asSelect = "SELECT * FROM " + T::getModelName();
    query_.append(asSelect);
    return this;
}


///-----------------------------------------------------------------------------
///
///             Вставить запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::insert() {
    clear();
    QString asInsert = "INSERT INTO " + T::getModelName();
    query_.append(asInsert);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Редактировать  запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::update() {
    clear();
    QString asUpdate = "UPDATE " + T::getModelName();
    query_.append(asUpdate);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Запрос или значение параметра.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::strquery(const QString& asQuery) {
    query_.append(asQuery);
    return this;
}
///-----------------------------------------------------------------------------
///
///             удалить запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::remove() {
    clear();
    QString asDelete = "Delete   from " + T::getModelName();
    query_.append(asDelete);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Равно.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::equally() {
    QString asDelete = " = ";
    query_.append(asDelete);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Установить значения.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::set() {
    QString asSet = " set ";
    query_.append(asSet);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Условие.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::where() {
    QString asWhere = " where ";
    query_.append(asWhere);
    where_.append(asWhere);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Привязать поле модели.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::bind(const int& column) {
    query_.append(":" + T::getFields()[column]);
    bind_.append(column);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Поле модели.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::field(const int& column) {

    if (bind_.isEmpty()) {
        query_.append(" " + T::getFields()[column]);
    } else {
        if (where_.isEmpty()) {
            query_.append(", " + T::getFields()[column]);
        } else {
            query_.append(" " + T::getFields()[column]);

        }
    }

    return this;
}


///-----------------------------------------------------------------------------
///
///             Сгенерировать запрос.
///
///-----------------------------------------------------------------------------

template <class T> const QString& MQuery<T>::prepare() {
    queryStr_ = "";
    for (int i = 0; i < query_.size(); i++) {
        queryStr_ += query_.at(i);
    };
    return queryStr_;
}

///-----------------------------------------------------------------------------
///
///             Очистить списки.
///
///-----------------------------------------------------------------------------

template <class T> void MQuery<T>::clear() {
    query_.clear();
    bind_.clear();
    bindprm_.clear();
    where_.clear();

}


///-----------------------------------------------------------------------------
///
///             Выбрать все записи.
///
///-----------------------------------------------------------------------------

template <class T> const QString& MQuery<T>::selectAll() {
    return this->select()->prepare();

}
///-----------------------------------------------------------------------------
///
///             Выбрать  запись по ID.
///
///-----------------------------------------------------------------------------

template <class T> const QString& MQuery<T>::selectById(const int& id) {
    return this->select()->where()->field(T::Column::ID)->
            equally()->strquery(QString::number(id))->prepare();

}
///-----------------------------------------------------------------------------
///
///             Удалить  запись по ID.
///
///-----------------------------------------------------------------------------

template <class T> const QString& MQuery<T>::removeById(const int& id) {
    return this->remove()->where()->field(T::Column::ID)->
            equally()->strquery(QString::number(asId))->prepare();

}


#endif /* MQUERY_IMPL_H */