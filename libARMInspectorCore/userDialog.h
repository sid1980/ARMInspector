/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userDialog.h
 * Author: kazun_as
 *
 * Created on 2 апреля 2021 г., 12:51
 */

#ifndef _USERDIALOG_H
#define _USERDIALOG_H

#include "ui_userDialog.h"

class userDialog : public QDialog {
    Q_OBJECT
public:
    userDialog();
    virtual ~userDialog();
private:
    Ui::userDialog widget;
};

#endif /* _USERDIALOG_H */
