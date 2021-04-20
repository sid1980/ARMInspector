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
#include <QModelIndex>
#include "ClientController.h"

class juristFrm : public QMainWindow {
    Q_OBJECT
public:
    juristFrm();
    virtual ~juristFrm();
    ///Инициализация ссылки на контроллер клинта
    void initClient(ClientController *clientController);
    void report();
    void spanTbl();
    QMenuBar * getMenuBar();
    void OnFileNew();
    void OnFileSave();
    void OnFileOpen();
private slots:
    void onTableClicked(const QModelIndex &);
private:
    Ui::juristFrm widget;
    QMenuBar * m_pMenuBar;
    QMenu * m_pMenu;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};

};

#endif /* _JURISTFRM_H */
