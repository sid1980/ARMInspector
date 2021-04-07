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
QDialog(parent), widget_(new Ui::userForm) {
    widget_->setupUi(this);
}

userForm::~userForm() {
    delete widget_;
}

Ui::userForm* userForm::getWidget() {
    return widget_;
}

const QList<Inspection>& userForm::getInspections()const {
    return inspections_;
};

void userForm::setInspections(const QList<Inspection>& inspections) {
    inspections_ = inspections;
    for (auto& t : inspections_) {
        this->getWidget()->comboBoxInspection->addItem(t.getName());
    }

}