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
///             Установить  модель.
///
///-----------------------------------------------------------------------------

template <class T> void MQuery<T>::setModel( T* model) {
    model_ = model;
}
///-----------------------------------------------------------------------------
///
///             Получить модель.
///
///-----------------------------------------------------------------------------

template <class T>  T* MQuery<T>::getModel() {
    return model_;
}
///-----------------------------------------------------------------------------
///
///             Выбрать записи.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::select() {
    query_.clear();
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
    query_.clear();
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
    query_.clear();
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
    query_.clear();
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
    return this;
}

///-----------------------------------------------------------------------------
///
///             Поле.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::bind_prm(const int& column) {

    query_.append(":" + T::getFields()[column]);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Параметр.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::field(const int& column) {

    query_.append(" "+T::getFields()[column]);
    return this;
}


///-----------------------------------------------------------------------------
///
///             Сгенерировать запрос.
///
///-----------------------------------------------------------------------------

template <class T> QString MQuery<T>::prepare() {
    QString query = "";
    for (int i = 0; i < query_.size(); i++) {
        query += query_.at(i);
    };
    return query;
}


#endif /* MQUERY_IMPL_H */