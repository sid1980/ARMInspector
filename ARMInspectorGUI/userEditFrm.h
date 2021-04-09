/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userEditFrm.h
 * Author: kazun
 *
 * Created on 8 апреля 2021 г., 21:18
 */

#ifndef _USEREDITFRM_H
#define _USEREDITFRM_H

#include "ui_userEditFrm.h"
//#include "User.h"
#include "Inspection.h"

class userEditFrm : public QDialog {
    Q_OBJECT
public:
    explicit userEditFrm(QWidget *parent = 0);
    virtual ~userEditFrm();
    Ui::userEditFrm* getWidget();
    void setInspections(const QList<Inspection>&);

private:
    Ui::userEditFrm* widget_;
    QList<Inspection> inspections_;

};

#endif /* _USEREDITFRM_H */
