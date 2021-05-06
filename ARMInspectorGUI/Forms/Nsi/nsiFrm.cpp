/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   nsiFrm.cpp
 * Author: kazun_as
 *
 * Created on 26 апреля 2021 г., 08:40
 */

#include "nsiFrm.h"
#include "JsonSerializer.h"
#include "JsonSerializable.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

nsiFrm::nsiFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::nsiFrm) {
    widget_->setupUi(this);
    nsiEditFrm_ = new nsiEditForm(this);
    listnsi_ = new ModelList<Nsi>();
    proxyModel_ = new QSortFilterProxyModel(listnsi_);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

nsiFrm::~nsiFrm() {
    delete widget_;
    delete nsiEditFrm_;
    delete listnsi_;
    delete proxyModel_;
}

///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::nsiFrm* nsiFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void nsiFrm::setModel(const QList<Nsi>& nsi) {
    listnsi_->setListModel(nsi);
    proxyModel_->setSourceModel(listnsi_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///                 Установить размер таблицы
///          
///-----------------------------------------------------------------------------

void nsiFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->getUI()->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->getUI()->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->getUI()->tableView->setSortingEnabled(true);
    this->getUI()->tableView->verticalHeader()->hide();
    this->getUI()->tableView->setWordWrap(false);
    this->getUI()->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView->setShowGrid(false);
    this->getUI()->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->getUI()->tableView->horizontalHeader()->setHighlightSections(false);
    this->getUI()->tableView->setAlternatingRowColors(true); // alternative colors 
    this->getUI()->tableView->setFrameShape(QFrame::NoFrame);
    this->getUI()->tableView->setMinimumWidth(width);
    this->getUI()->tableView->setMinimumHeight(height);
    this->getUI()->tableView->setColumnWidth(0, 50);
    this->getUI()->tableView->setColumnWidth(1, width - 50);
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки добавления записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_addNsi_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addNsi_clicked");
    nsiEditForm frm;
    frm.setWindowTitle("Добавление новой статьи КоАП");
    frm.getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    frm.getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (frm.exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        Nsi* nsi = new Nsi();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        nsi->setName(frm.getUI()->lineEditName->text());
        QString nsiAsString = JsonSerializer::serialize(nsi);
        QJsonObject param;
        param.insert("numNSI", Nsi::num_);
        param.insert("data", nsiAsString);
        emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::ADD_NEW_MODEL, param));
        emit waitServer();
        delete nsi;
    }
}
///-----------------------------------------------------------------------------
///
///         обработчик кнопки редактирования записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_editNsi_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editNsi_clicked");
    nsiEditForm frm;
    frm.setWindowTitle("Редактирование записи НСИ");
    frm.getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    frm.getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    Nsi nsi = listnsi_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
    frm.getUI()->lineEditName->setText(nsi.getName());
    if (frm.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Редактирование записи НСИ", "QDialog::Accepted");
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_deleteNsi_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_deleteNsi_clicked");

}

///-----------------------------------------------------------------------------
///
///         close event 
///          
///-----------------------------------------------------------------------------

void nsiFrm::closeEvent(QCloseEvent *event) {
    event->accept();
    QDialog::closeEvent(event);
}