/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumnEditForm.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#ifndef _RPTCOLUMNEDITFORM_H
#define _RPTCOLUMNEDITFORM_H

#include "ui_RptColumnEditForm.h"

class RptColumnEditForm : public QDialog {
    Q_OBJECT
public:
    RptColumnEditForm();
    virtual ~RptColumnEditForm();
private:
    Ui::RptColumnEditForm widget;
};

#endif /* _RPTCOLUMNEDITFORM_H */
