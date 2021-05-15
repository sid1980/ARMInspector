/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RptColumnFrm.cpp
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 14:45
 */

#include "RptColumnFrm.h"
#include "ItemContainer.h"
#include "Nsi/Nsi.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptColumnFrm::RptColumnFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::RptColumnFrm) {
    widget_->setupUi(this);
    listrptcolumn_ = new ModelList<RptColumnView>();
    proxyModel_ = new QSortFilterProxyModel(listrptcolumn_);
    rptcolumnview_ = new RptColumnView();
    rptcolumnEditFrm_ = new RptColumnEditForm(this);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

RptColumnFrm::~RptColumnFrm() {
    delete widget_;
    delete listrptcolumn_;
    delete proxyModel_;
    delete rptcolumnview_;
    delete rptcolumnEditFrm_;

}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::RptColumnFrm* RptColumnFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::setModel(const QList<RptColumnView>& rptcolumn) {
    listrptcolumn_->setListModel(rptcolumn);
    proxyModel_->setSourceModel(listrptcolumn_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView_Mro->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            switch (model) {
                case ModelWrapper::Model::Nsi:
                {
                    ItemContainer<Nsi> nsiContainer;
                    JsonSerializer::parse(wrapper.getData(), nsiContainer);
                    QList<Mro> listnsi = nsiContainer.getItemsList();
                    setListNsi(listnsi);
                    //QMessageBox::information(this, "RptColumnFrm::worker", listmro[0].getName());
                    //setModel(listmro);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::RptColumnView:
                {
                    ItemContainer<RptColumnView> rptcolumnContainer;
                    JsonSerializer::parse(wrapper.getData(), rptcolumnContainer);
                    QList<RptColumnView> listrptcolumn = rptcolumnContainer.getItemsList();
                    //QMessageBox::information(this, "RptColumnFrm::worker", listmro[0].getName());
                    setModel(listrptcolumn);
                    emit ready();
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case ModelWrapper::Command::GET_MODEL:
        {
            RptColumn rptcolumn;
            JsonSerializer::parse(wrapper.getData(), rptcolumn);
            fillEditFrm(rptcolumn);
            emit ready();
        }
            break;

        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            RptColumn rptcolumn;
            JsonSerializer::parse(wrapper.getData(), rptcolumn);
            showData(rptcolumn);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            RptColumn rptcolumn;
            JsonSerializer::parse(wrapper.getData(), rptcolumn);
            showEditData(rptcolumn);
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            //Сервер вернул результат команды "DEL_MODEL"     
            RptColumn rptcolumn;
            JsonSerializer::parse(wrapper.getData(), rptcolumn);
            //emit dialog_->showUserData(user);
            QMessageBoxEx::information(0, wrapper.getHead(), wrapper.getMessage() +
                    "МРО  <a style='color:royalblue'> " + rptcolumn.getArticle() + "</a>");

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

void RptColumnFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView_Mro->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView_Mro->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView_Mro->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    this->getUI()->tableView->setColumnWidth(0, 85);
    this->getUI()->tableView->setColumnWidth(1, (width - 85) / 2);
    this->getUI()->tableView->setColumnWidth(2, (width - 85) / 2);
}
///-----------------------------------------------------------------------------
///
///      обработчик кнопки добавления записи МРО
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::on_pushButton_Add_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addMro_clicked()");
    this->getUI()->tableView->model()->sort(-1);
    //mroEditForm frm;
    rptcolumnEditFrm_->setWindowTitle("Добавление новой записи");
    rptcolumnEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    rptcolumnEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (rptcolumnEditFrm_->exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        RptColumn* rptcolumn = new RptColumn();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        rptcolumn->setCol(rptcolumnEditFrm_->getUI()->lineEdit->text());
        rptcolumn->setArticle(rptcolumnEditFrm_->getListArticle()[rptcolumnEditFrm_->getUI()->comboBoxArticle->currentIndex()].getId());
        rptcolumn->setSubject(rptcolumnEditFrm_->getListSubject()[rptcolumnEditFrm_->getUI()->comboBoxSubject->currentIndex()].getId());

        //QString mroAsString = JsonSerializer::serialize(*mro);
        //QJsonObject param;
        //param.insert(DATA, mroAsString);
        emit runServerCmd(Functor<RptColumn>::produce(ModelWrapper::Command::ADD_NEW_MODEL, *rptcolumn));
        emit waitReady();
        //showNewRecordData(*mro);
        delete rptcolumn;
    }
}

///-----------------------------------------------------------------------------
///
///       обработчик кнопки редактирования записи  МРО
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::on_pushButton_Edit_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editMro_clicked()");
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        RptColumnView rptcolumnV = listrptcolumn_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = rptcolumnV.getId();
        QJsonObject param;
        param.insert(ID_, id);
        emit runServerCmd(Functor<RptColumn>::producePrm(ModelWrapper::Command::GET_MODEL, param));
        emit waitReady();
        rptcolumnEditFrm_->setWindowTitle("Редактирование");
        rptcolumnEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        rptcolumnEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
        if (rptcolumnEditFrm_->exec() == QDialog::Accepted) {
            RptColumn* rptcolumn = new RptColumn();
            rptcolumn->setId(id);
            rptcolumn->setName(rptcolumnEditFrm_->getUI()->lineEdit->text());
            rptcolumn->setMro(rptcolumnEditFrm_->getListMro()[rptcolumnEditFrm_->getUI()->comboBox->currentIndex()].getId());
            emit runServerCmd(Functor<RptColumn>::produce(ModelWrapper::Command::UPDATE_MODEL, *rptcolumn));
            emit waitReady();
            delete rptcolumn;
        }
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  записи  МРО
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::on_pushButton_Remove_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_removeMro_clicked()");
    //Question MessageBox
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        RptColumnView rptcolumn = listrptcolumn_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = rptcolumn.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление записи",
                "Вы действительно хотите удалить РЭГИ <br><br><a style='font-size:14px;color:red;'> " +
                rptcolumn.getName() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert(ID_, id);
            //emit deleteUser(id);
            emit runServerCmd(Functor<RptColumn>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listrptcolumn_->delModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        } else {
            qDebug() << "Yes was *not* clicked";
        }
    }
}

///-----------------------------------------------------------------------------
///
///         показать данные новой записи
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::showData(const RptColumn& asRptColumn) {
    RptColumn rptcolumn = asRptColumn;
    rptcolumnview_->setId(rptcolumn.getId());
    rptcolumnview_->setName(rptcolumn.getName());
    rptcolumnview_->setMro(rptcolumnEditFrm_->getListMro()[rptcolumn.getMro() - 1].getName());

    listrptcolumn_->addModel(*rptcolumnview_);
    this->getUI()->tableView->selectRow(listrptcolumn_->rowCount() - 1);
    this->getUI()->tableView->scrollToBottom();
}

///-----------------------------------------------------------------------------
///
///         показать данные выбранной записи 
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::showEditData(const RptColumn& rptcolumn) {
    rptcolumnview_->setId(rptcolumn.getId());
    rptcolumnview_->setCol(rptcolumn.getCol());
    rptcolumnview_->setArticle(rptcolumnEditFrm_->getListArticle()[rptcolumn.getArticle() - 1].getName());
    rptcolumnview_->setSubject(rptcolumnEditFrm_->getListSubject()[rptcolumn.getSubject() - 1].getName());
    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), rptcolumnview_->getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), rptcolumnview_->getArticle(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 2), rptcolumnview_->getSubject(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 3), rptcolumnview_->getCol(), Qt::EditRole);
}

///-----------------------------------------------------------------------------
///
///         Инициализировать список статей или субъектов АП  в окнах ввода и 
///         редактирования
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::setListNsi(const QList<Nsi>& listnsi) {
    //QMessageBox::information(0, "Information Box", rptcolumns[1].getName());
    if (Nsi::num_ == 7) {
        rptcolumnEditFrm_->setListArticle(listnsi);
    } else if (Nsi::num_ == 5) {
        rptcolumnEditFrm_->setListSubject(listnsi);
    }
}

///-----------------------------------------------------------------------------
///
///         заполнить форму редактирования
///          
///-----------------------------------------------------------------------------

void RptColumnFrm::fillEditFrm(const RptColumn& rptcolumn) {
    rptcolumnEditFrm_->getUI()->lineEdit->setText(rptcolumn.getCol());
    for (int i = 0; i < rptcolumnEditFrm_->getListArticle().size(); i++) {
        if (rptcolumnEditFrm_->getListArticle()[i].getId() == rptcolumn.getArticle()) {
            rptcolumnEditFrm_->getUI()->comboBoxArticle->setCurrentIndex(i);
            break;
        }
    }
    for (int i = 0; i < rptcolumnEditFrm_->getListSubject().size(); i++) {
        if (rptcolumnEditFrm_->getListSubject()[i].getId() == rptcolumn.getSubject()) {
            rptcolumnEditFrm_->getUI()->comboBoxSubject->setCurrentIndex(i);
            break;
        }
    }
}

