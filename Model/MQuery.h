/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQuery.h
 * Author: kazun_as
 *
 * Created on 28 апреля 2021 г., 10:14
 */

#ifndef MQUERY_H
#define MQUERY_H
#include <QtCore>

template <class T> class MQuery {
public:
    MQuery<T>* select();
    MQuery<T>* strquery(const QString&);
    MQuery<T>* insert();
    MQuery<T>* update();
    MQuery<T>* remove();
    MQuery<T>* where();
    MQuery<T>* set();
    MQuery<T>* field(const int&);
    MQuery<T>* equally();
    MQuery<T>* bind_prm(const int&);
    QString prepare();
     T* getModel();
    void  setModel( T*);
private:
    /// Список объектов класса T. 
    QList<QString> query_;
    T* model_;
};
#include "MQuery_IMPL.h"
#endif /* MQUERY_H */

