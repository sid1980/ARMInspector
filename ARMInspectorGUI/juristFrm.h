/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juristFrm.h
 * Author: kazun_as
 *
 * Created on 16 апреля 2021 г., 13:09
 */

#ifndef _JURISTFRM_H
#define _JURISTFRM_H

#include "ui_juristFrm.h"
#include <QMenuBar>
#include <QTableView>

class juristFrm : public QMainWindow {
    Q_OBJECT
public:
    juristFrm();
    virtual ~juristFrm();
    void report();
    void spanTbl();
    QMenuBar * getMenuBar();
    void OnFileNew();
    void OnFileSave();
    void OnFileOpen();

private:
    Ui::juristFrm widget;
    QMenuBar * m_pMenuBar;
    QMenu * m_pMenu;

};

#endif /* _JURISTFRM_H */
