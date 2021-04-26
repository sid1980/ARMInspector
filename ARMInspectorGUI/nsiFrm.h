/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nsiFrm.h
 * Author: kazun_as
 *
 * Created on 26 апреля 2021 г., 08:40
 */

#ifndef _NSIFRM_H
#define _NSIFRM_H

#include <QDialog>
#include <QCloseEvent>
#include "QMessageBoxEx.h"
#include "ui_nsiFrm.h"
#include "nsiEditForm.h"
#include "Nsi.h"
#include "UserView.h"
#include "pwdFrm.h"
#include "ModelList.h"
#include "ModelList.h"
#include "DialogDestroyer.h"

#include <QSortFilterProxyModel>

class nsiFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit nsiFrm(QWidget *parent = 0);
    virtual ~nsiFrm();
    ///Получить ссылку на виджет
    Ui::nsiFrm* getUI();
    void closeEvent(QCloseEvent *event);
    ///Установить размер таблицы
    void setSizeTbl(const int& width, const int& height);
private slots:
    ///определить модель вывода данных
    void setModel(const QList<Nsi>& nsi);
    ///обработчик кнопки добавления записи НСИ
    void on_pushButton_addNsi_clicked();
    ///обработчик кнопки редактирования записи НСИ
    void on_pushButton_editNsi_clicked();
    ///обработчик кнопки удаления  записи НСИ
    void on_pushButton_deleteNsi_clicked();
    
signals:
    void ready();
private:
    Ui::nsiFrm *widget_;
    ///ссылка на окно ввода/редактирования записи НСИ
    nsiEditForm *nsiEditFrm_;
    ///ссылка на модель  данных 
    ModelList<Nsi>* listnsi_;
    ///ссылк на экземпляр модели вывода данных
    Nsi *nsi_;
    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;
};

#endif /* _NSIFRM_H */
