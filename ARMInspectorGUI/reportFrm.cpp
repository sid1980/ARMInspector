/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   reportFrm.cpp
 * Author: kazun_as
 *
 * Created on 15 апреля 2021 г., 12:26
 */

#include "reportFrm.h"

reportFrm::reportFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::reportFrm) {
    widget_->setupUi(this);
}

reportFrm::~reportFrm() {
}


///-----------------------------------------------------------------------------
///
///         Получить указатель на виджет окна.
///          
///-----------------------------------------------------------------------------

Ui::reportFrm* reportFrm::getWidget() {
    return widget_;
}

