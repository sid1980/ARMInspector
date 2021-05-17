/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RptRowEditForm.cpp
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#include "RptRowEditForm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptRowEditForm::RptRowEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::RptRowEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

RptRowEditForm::~RptRowEditForm() {
    delete widget_;
}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::RptRowEditForm* RptRowEditForm::getUI() {
    return widget_;
}

///-----------------------------------------------------------------------------
///
///         Получить список статей.
///          
///-----------------------------------------------------------------------------

//const QList<Nsi>& RptRowEditForm::getListArticle()const {
//    return listarticle_;
//};

const QHash <qint64, QString>& RptRowEditForm::getMapArticle() const {
    return maparticle_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список статей и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void RptRowEditForm::setMapArticle(const QList<Nsi>& listarticle) {
//    listarticle_ =  listarticle;
    maparticle_.clear();
    this->getUI()->comboBoxArticle->clear();
    for (auto& t : listarticle) {
        maparticle_.insert(t.getId(), t.getName());
        this->getUI()->comboBoxArticle->addItem(t.getName());
    }
}

///-----------------------------------------------------------------------------
///
///         Получить список статей.
///          
///-----------------------------------------------------------------------------

//const QList<Nsi>& RptRowEditForm::getListSubject() const {
//    return listsubject_;
//};
const QHash <qint64, QString>& RptRowEditForm::getMapSubject() const {
    return mapsubject_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список статей и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void RptRowEditForm::setMapSubject(const QList<Nsi>& listsubject) {
//    listsubject_ =  listsubject;
    mapsubject_.clear();
    this->getUI()->comboBoxSubject->clear();
    for (auto& t : listsubject) {
        mapsubject_.insert(t.getId(), t.getName());
        this->getUI()->comboBoxSubject->addItem(t.getName());
    }

}