/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   userForm.cpp
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 16:35
 */

#include "userForm.h"

userForm::userForm(QWidget *parent) :
QDialog(parent),widget(new Ui::userForm) {
    widget->setupUi(this);
}

userForm::~userForm() {
    delete widget;
}
