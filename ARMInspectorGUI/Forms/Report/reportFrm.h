/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reportFrm.h
 * Author: kazun_as
 *
 * Created on 15 апреля 2021 г., 12:26
 */

#ifndef _REPORTFRM_H
#define _REPORTFRM_H

#include "ui_reportFrm.h"

class reportFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit reportFrm(QWidget *parent = 0);
    ///деструктор
    virtual ~reportFrm();
    ///получить указатель на виджет окна
    Ui::reportFrm* getWidget();

private:
    Ui::reportFrm* widget_;
};

#endif /* _REPORTFRM_H */
