/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   userEditFrm.cpp
 * Author: kazun
 *
 * Created on 8 апреля 2021 г., 21:18
 */

#include "userEditFrm.h"

userEditFrm::userEditFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::userEditFrm) {
    widget_->setupUi(this);
}

userEditFrm::~userEditFrm() {
}

Ui::userEditFrm* userEditFrm::getWidget() {
    return widget_;
}

