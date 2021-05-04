/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mroFrm.cpp
 * Author: kazun_as
 *
 * Created on 4 мая 2021 г., 16:28
 */

#include "mroFrm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

mroFrm::mroFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::mroFrm) {
    widget_->setupUi(this);
    listmro_ = new ModelList<Mro>();
    proxyModel_ = new QSortFilterProxyModel(listmro_);

}

mroFrm::~mroFrm() {
    delete widget_;
    delete listmro_;
    delete proxyModel_;

}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::mroFrm* mroFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void mroFrm::setModel(const QList<Mro>& mro) {
    listmro_->setListModel(mro);
    proxyModel_->setSourceModel(listmro_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView->setSpan(0,1,2,2);
}
