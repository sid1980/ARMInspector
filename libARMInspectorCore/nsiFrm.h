/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nsiFrm.h
 * Author: kazun
 *
 * Created on 25 апреля 2021 г., 20:09
 */

#ifndef _NSIFRM_H
#define _NSIFRM_H

#include "ui_nsiFrm.h"

class nsiFrm : public QDialog {
    Q_OBJECT
public:
    nsiFrm();
    virtual ~nsiFrm();
private:
    Ui::nsiFrm widget;
};

#endif /* _NSIFRM_H */
