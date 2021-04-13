/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pwdEditFrm.h
 * Author: kazun_as
 *
 * Created on 13 апреля 2021 г., 16:52
 */

#ifndef _PWDEDITFRM_H
#define _PWDEDITFRM_H

#include "ui_pwdEditFrm.h"

class pwdEditFrm : public QDialog {
    Q_OBJECT
public:
    pwdEditFrm();
    virtual ~pwdEditFrm();
private:
    Ui::pwdEditFrm widget;
};

#endif /* _PWDEDITFRM_H */
