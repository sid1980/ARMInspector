/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RptColumnEditForm.cpp
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#include "RptColumnEditForm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptColumnEditForm::RptColumnEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::RptColumnEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

RptColumnEditForm::~RptColumnEditForm() {
    delete widget_;
}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::RptColumnEditForm* RptColumnEditForm::getUI() {
    return widget_;
}

///-----------------------------------------------------------------------------
///
///         Получить список статей.
///          
///-----------------------------------------------------------------------------

const QList<Mro>& RptColumnEditForm::getListArticle()const {
    return listarticle_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список статей и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void RptColumnEditForm::setListArticle(const QList<Nsi>& listarticle) {
    listarticle_ =  listarticle;
    this->getUI()->comboBox->clear();
    for (auto& t : listarticle_) {
        this->getUI()->comboBox->addItem(t.getName());
    }

}

///-----------------------------------------------------------------------------
///
///         Получить список статей.
///          
///-----------------------------------------------------------------------------

const QList<Mro>& RptColumnEditForm::getListSubject()const {
    return listsubject_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список статей и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void RptColumnEditForm::setListSubject(const QList<Nsi>& listsubject) {
    listsubject_ =  listsubject;
    this->getUI()->comboBox->clear();
    for (auto& t : listsubject_) {
        this->getUI()->comboBox->addItem(t.getName());
    }

}