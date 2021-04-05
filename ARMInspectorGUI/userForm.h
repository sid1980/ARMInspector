/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userForm.h
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 16:35
 */
//Форма данных  о пользователе

#ifndef _USERFORM_H
#define _USERFORM_H

#include "ui_userForm.h"

class userForm : public QDialog {
    Q_OBJECT
public:
    explicit userForm(QWidget *parent = 0);
    virtual ~userForm();
    Ui::userForm* getWidget();

private:
    Ui::userForm* widget_;
};

#endif /* _USERFORM_H */
