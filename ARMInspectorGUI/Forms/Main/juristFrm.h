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
#include "Report/Report.h"
#include "Mro/Mro.h"
#include "Mro/mroFrm.h"
#include "Nsi/nsiFrm.h"
#include "RptRow/RptRowFrm.h"
#include "DialogDestroyer.h"
#include "Inspection/inspectionFrm.h"

class juristFrm : public QMainWindow {
    Q_OBJECT
public:
    juristFrm();
    virtual ~juristFrm();
    ///Инициализация ссылки на контроллер клинта
    void initClient(ClientController *clientController);
    ///Скрыть элементы управления 
    void hideControlsFrm();
    ///Показать элементы управления 
    void showControlsFrm();
    ///Сформировать отчёт
    void report();
    ///Объединить ячейки таблицы
    void spanTbl();
    ///Получить указатель на меню
    QMenuBar * getMenuBar();
    ///Меню.Сформировать отчёт
    void OnGenerateReport();
    ///Меню.Выйти из программы 
    void OnExit();
    ///Меню.Сформировать отчёт.Приложение 2
    void OnGenerateReprt2();
    ///Меню. Управление справочником инспекций. 
    void OnInspection();
    ///Меню. Управление справочником МРО
    void OnMro();
    ///Меню. Управление справочником стаьей КоАП
    void OnArticle();
    ///Меню. Управление справочником  субъектов АП
    void OnSubject();
    ///Меню. Управление справочником  колонок отчёта 
    void OnRptColumn();
    ///Меню. Управление справочником  строк отчёта 
    void OnRptRow();
    ///создать сигнально-слотовые соединения
    ///между основноё формой и формой ввода-редактирования 
    void createFrmConnector(const QDialog&);
    //инициализировать список МРО;
    void setlistMro(const QList<Mro>&);
    //инициализироваь список строк отчёта;
    void setlistRow(const QList<RptRow>&);
    //инициализировать список колонок отчёта;
    void setlistCol(const QList<RptColumn>&);
    //инициализировать список результата полученного от сервера;
    void setlistResult(const QList<ReportOut>&);

signals:
    ///сигнал готовности
    void ready();
    ///Ждать ответ сервера
    void waitReady();
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///Ответ сервера
    void responseServer(const QString&);
    ///список НСИ подготовлен    
    void listNsiReady(const QList<Nsi>&);
    ///запись НСИ подготовлена    
    void nsiReady(const Nsi&);

private slots:
    void onTableClicked(const QModelIndex &);
    void on_pushButton_Report_clicked();
    void on_pushButton_Excel_clicked();
    ///Обработчик команд (ответов) сервера
    void worker(const QString& asWrapper);
private:
    Ui::juristFrm widget;
    QMenuBar * m_pMenuBar;
    QMenu * m_pMenu;
    QStandardItemModel *model_;
    ///список МРО
    QList<Mro> mro_;
    ///список строк отчёта
    QList<RptRow> listrow_;
    ///список колонок  отчёта
    QList<RptColumn> listcol_;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};
    //nsiFrm* frm; 
    QList<ReportOut> result_;

};

#endif /* _JURISTFRM_H */
