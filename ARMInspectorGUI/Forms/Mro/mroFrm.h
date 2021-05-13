/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mroFrm.h
 * Author: kazun_as
 *
 * Created on 4 мая 2021 г., 16:28
 */

#ifndef _MROFRM_H
#define _MROFRM_H

#include "ui_mroFrm.h"
#include "Mro/Mro.h"
#include "ModelList.h"
#include "mroEditForm.h"
#include "Functor.h"
#include "MQuery.h"

class mroFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit mroFrm(QWidget *parent = 0);
    ~mroFrm();
    ///Получить ссылку на виджет
    Ui::mroFrm* getUI();
    ///Установить размер таблицы
    void setSizeTbl(const int& width, const int& height);
    ///определить модель вывода данных
    void setModel(const QList<Mro>& mro);
    ///показать данные МРО
    void showData(const Mro& asMro);
private slots:
    ///обработчик кнопки добавления записи НСИ
    void on_pushButton_AddMro_clicked();
    ///обработчик кнопки редактирования записи НСИ
    void on_pushButton_EditMro_clicked();
    ///обработчик кнопки удаления  записи НСИ
    void on_pushButton_RemoveMro_clicked();

    ///Обработчик команд (ответов) сервера
    void worker(const QString&);

signals:
    void ready();
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///сигнализировать  о  необходимости  ожидания ответа от сервера 
    void waitReady();
private:
    Ui::mroFrm *widget_;
    ///ссылка на модель  данных 
    ModelList<Mro>* listmro_;
    ///ссылк на экземпляр модели вывода данных
    Mro *mro_;
    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;

};

#endif /* _MROFRM_H */
