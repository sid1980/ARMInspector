/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mroEditForm.h
 * Author: kazun_as
 *
 * Created on 13 мая 2021 г., 14:47
 */

#ifndef _MROEDITFORM_H
#define _MROEDITFORM_H

#include "ui_mroEditForm.h"

class mroEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit mroEditForm(QWidget *parent = 0);
    virtual ~mroEditForm();
    ///Получить ссылку на виджет
    Ui::mroEditForm* getUI();

private:
    Ui::mroEditForm* widget_;
};

#endif /* _MROEDITFORM_H */
