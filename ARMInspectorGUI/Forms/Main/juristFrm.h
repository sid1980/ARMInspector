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
#include <QMainWindow>
#include <QTableView>
#include <QModelIndex>
#include <QStandardItemModel>
#include "ClientController.h"
#include "Mro/Mro.h"
#include "Nsi/nsiFrm.h"
#include "DialogDestroyer.h"

class juristFrm : public QMainWindow {
    Q_OBJECT
public:
    juristFrm();
    virtual ~juristFrm();
    ///Инициализация ссылки на контроллер клинта
    void initClient(ClientController *clientController);
    void hideControlsFrm();
    void showControlsFrm();
    void report();
    void spanTbl();
    QMenuBar * getMenuBar();
    void OnGenerateReport();
    void OnExit();
    void OnGenerateReprt2();
    void OnArticle();
    void OnSubject();
    //void closeEvent(QCloseEvent *event);
signals:
    ///Ждать ответ сервера
    void waitServer();
private slots:
    void onTableClicked(const QModelIndex &);
    void setlistMro(const QList<Mro>&);
    void on_pushButton_Report_clicked();
private:
    Ui::juristFrm widget;
    QMenuBar * m_pMenuBar;
    QMenu * m_pMenu;
    QStandardItemModel *model_;
    ///список МРО
    QList<Mro> mro_;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};
    //nsiFrm* frm; 


};

#endif /* _JURISTFRM_H */
