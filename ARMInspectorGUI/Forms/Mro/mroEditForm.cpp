/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mroEditForm.cpp
 * Author: kazun_as
 *
 * Created on 13 мая 2021 г., 14:47
 */

#include "mroEditForm.h"
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

mroEditForm::mroEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::mroEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

mroEditForm::~mroEditForm() {
    delete widget_;
}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::mroEditForm* mroEditForm::getUI() {
    return widget_;
}
