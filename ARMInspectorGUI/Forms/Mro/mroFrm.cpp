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
#include "ItemContainer.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

mroFrm::mroFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::mroFrm) {
    widget_->setupUi(this);
    listmro_ = new ModelList<MroView>();
    proxyModel_ = new QSortFilterProxyModel(listmro_);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

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

void mroFrm::setModel(const QList<MroView>& mro) {
    listmro_->setListModel(mro);
    proxyModel_->setSourceModel(listmro_);
    this->getUI()->tableView_Mro->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView_Mro->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView_Mro->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void mroFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            ItemContainer<MroView> mroContainer;
            JsonSerializer::parse(wrapper.getData(), mroContainer);
            QList<MroView> listmro = mroContainer.getItemsList();
            setModel(listmro);
            emit ready();
        }
            break;
        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            MroView mro;
            JsonSerializer::parse(wrapper.getData(), mro);
            showData(mro);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            emit ready();
        }
            break;
        default:
            break;
    }
}
///-----------------------------------------------------------------------------
///
///                 Установить размер таблицы
///          
///-----------------------------------------------------------------------------

void mroFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView_Mro->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView_Mro->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView_Mro->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->getUI()->tableView_Mro->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->getUI()->tableView_Mro->setSelectionMode(QAbstractItemView::SingleSelection);
    this->getUI()->tableView_Mro->setSortingEnabled(true);
    this->getUI()->tableView_Mro->verticalHeader()->hide();
    this->getUI()->tableView_Mro->setWordWrap(false);
    this->getUI()->tableView_Mro->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView_Mro->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView_Mro->setShowGrid(false);
    this->getUI()->tableView_Mro->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->getUI()->tableView_Mro->horizontalHeader()->setHighlightSections(false);
    this->getUI()->tableView_Mro->setAlternatingRowColors(true); // alternative colors 
    this->getUI()->tableView_Mro->setFrameShape(QFrame::NoFrame);
    this->getUI()->tableView_Mro->setMinimumWidth(width);
    this->getUI()->tableView_Mro->setMinimumHeight(height);
    this->getUI()->tableView_Mro->setColumnWidth(0, 85);
    this->getUI()->tableView_Mro->setColumnWidth(1, (width - 85)*3 / 4);
    this->getUI()->tableView_Mro->setColumnWidth(2, (width - 85) / 4);
}
///-----------------------------------------------------------------------------
///
///      обработчик кнопки добавления записи МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_AddMro_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addMro_clicked()");
    this->getUI()->tableView_Mro->model()->sort(-1);
    mroEditForm frm;
    frm.setWindowTitle("Добавление новой записи");
    frm.getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    frm.getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (frm.exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        Mro* mro = new Mro();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        mro->setName(frm.getUI()->lineEditName->text());
        //QString mroAsString = JsonSerializer::serialize(*mro);
        //QJsonObject param;
        //param.insert(DATA, mroAsString);
        emit runServerCmd(Functor<Mro>::produce(ModelWrapper::Command::ADD_NEW_MODEL, *mro));
        emit waitReady();
        //showNewRecordData(*mro);
        delete mro;
    }
}

///-----------------------------------------------------------------------------
///
///       обработчик кнопки редактирования записи  МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_EditMro_clicked() {
    QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editMro_clicked()");

}
///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  записи  МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_RemoveMro_clicked() {
    QMessageBox::information(this, "АРМ Юриста", "on_pushButton_removeMro_clicked()");

}

///-----------------------------------------------------------------------------
///
///         показать данные новой записи
///          
///-----------------------------------------------------------------------------

void mroFrm::showData(const MroView& asMro) {
    MroView mro = asMro;
    listmro_->addModel(mro);
    this->getUI()->tableView_Mro->selectRow(listmro_->rowCount() - 1);
    this->getUI()->tableView_Mro->scrollToBottom();
}
