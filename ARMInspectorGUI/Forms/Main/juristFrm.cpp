/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   juristFrm.cpp
 * Author: kazun_as
 *
 * Created on 16 апреля 2021 г., 13:09
 */

#include "juristFrm.h"
#include "myProgressBar.h"
#include "QMessageBoxEx.h"
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QProgressBar>
#include <QtCore/QCoreApplication>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxBase>
#include <ActiveQt/QAxObject>
#include <array>
// [0] include QXlsx headers 
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

juristFrm::juristFrm() {
    widget.setupUi(this);
    model_ = new QStandardItemModel;
    m_pMenuBar = new QMenuBar(this);
    //frm = new nsiFrm(this);
    this->setMenuBar(m_pMenuBar);
    QMenu * menu1 = m_pMenuBar->addMenu("&Журнал");
    // Выход
    QAction * action = new QAction("&Выход", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnExit);
    menu1->addAction(action);
    QMenu * menu = m_pMenuBar->addMenu("&Отчеты по АП");
    //menu->setLayoutDirection(Qt::RightToLeft); // Display menu bar to the right
    // New
    action = new QAction("&Отчёт Приложение 1", this);
    action->setIcon(QPixmap("Icons/icons8-file-48.png"));
    connect(action, &QAction::triggered, this, &juristFrm::OnGenerateReport);
    menu->addAction(action);
    // Open
    action = new QAction("&Отчёт Приложение 2", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnGenerateReprt2);
    menu->addAction(action);
    QMenu * menu2 = m_pMenuBar->addMenu("&Справочники");
    // Справочники
    action = new QAction("&Список инспекций", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnInspection);
    menu2->addAction(action);
    action = new QAction("&Список МРО", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnMro);
    menu2->addAction(action);
    action = new QAction("&Статьи КоАП", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnArticle);
    menu2->addAction(action);
    action = new QAction("&Субъекты АП", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnSubject);
    menu2->addAction(action);
    action = new QAction("&Справочник колонок отчёта", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnRptColumn);
    menu2->addAction(action);
    action = new QAction("&Справочник строк отчёта", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnRptRow);
    menu2->addAction(action);

    //qApp->setStyleSheet("QMainWindow { background-color: yellow; border: 1px solid #424242 }"
    //        "QLCDNumber { background-color: red }"
    //        "QMenu::separator{height: 2px; background: lightblue; margin-left: 10px; margin-right: 5px;}"
    //        "QMenu::indicator { width: 13px; height: 13px; }"
    //        "QMenuBar::item { spacing: 3px;  padding: 1px 4px; background: transparent; border-radius: 4px; }"
    //        "QMenuBar::item:selected {background: #a8a8a8;}"
    //        "QMenuBar::item:pressed { background: #888888; }"
    //        "QToolBar { background: blue; spacing: 10px;}"
    //        "QTableWidget QTableCornerButton::section { background: red; border: 2px outset red; }");
    //   QString style = R"(
    //               )";
    //m_pMenuBar->setStyleSheet(style);

    //QString style1 = R"(
    //               )";
    //menu->setStyleSheet(style1);
    //m_pMenuBar->setStyle();
    //m_pMenuBar->adjustSize();
    QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
    QMessageBoxEx::setCustomTextForButton(QMessageBox::No, "Нет");
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

juristFrm::~juristFrm() {
    delete model_;
    delete m_pMenuBar;
}

///-----------------------------------------------------------------------------
///
///         getMenuBar.
///          
///-----------------------------------------------------------------------------

QMenuBar * juristFrm::getMenuBar() {
    return m_pMenuBar;
}

///-----------------------------------------------------------------------------
///
///         Меню.Формирование отчёта.Приложение 1.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnGenerateReport() {
    //QVBoxLayout *layout = new QVBoxLayout;
    //ayout->addWidget(widget->tableView);
    ///получен ответ от сервера в виде строки
    connect(this, SIGNAL(responseServer(const QString&)), this, SLOT(worker(const QString&)));
    QJsonObject param;
    emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    this->showControlsFrm();
    report();
    //QMessageBox::information(0, "Menu", "Отчёт Приложение 1");
}
///-----------------------------------------------------------------------------
///
///         Меню.Формирование отчёта.Приложение 2.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnGenerateReprt2() {
    model_->clear();
    this->hideControlsFrm();
}

///-----------------------------------------------------------------------------
///
///         Меню.Выход из приложения.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnExit() {

    QMessageBoxEx::StandardButton reply;
    reply = QMessageBoxEx::question(this, "Завершение работы АРМ Инспектор",
            "Вы действительно хотите завершить работу ? ",
            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        //this->close();
        //qApp->closeAllWindows();
        qApp->quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}


///-----------------------------------------------------------------------------
///
///         Меню.Список РЭГИ.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnInspection() {
    QMessageBox::information(this, "АРМ Юриста", "OnInspection()");
    inspectionFrm* frm = new inspectionFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<InspectionView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Список инспекций");
    frm->setSizeTbl(853, 550);
    frm->exec();
}
///-----------------------------------------------------------------------------
///
///         Меню.Справочник колонок отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnRptColumn() {
    //QMessageBox::information(this, "АРМ Юриста", "OnRptColumn()");
    RptColumnFrm* frm = new RptColumnFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<RptColumnView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    Nsi::num_ = NSI_ARTICLE;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    Nsi::num_ = NSI_SUBJECT;
    param[NSI_NUM] = Nsi::num_;
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Справочник колонок отчёта");
    frm->setSizeTbl(853, 550);
    frm->exec();


}

///-----------------------------------------------------------------------------
///
///         Меню.Справочник строк отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnRptRow() {
    //QMessageBox::information(this, "АРМ Юриста", "OnRptColumn()");
    RptRowFrm* frm = new RptRowFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Справочник строк отчёта");
    frm->setSizeTbl(853, 550);
    frm->exec();


}

///-----------------------------------------------------------------------------
///
///         Меню.Список МРО.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnMro() {
    //QMessageBox::information(this, "АРМ Юриста", "OnMro()");
    mroFrm* frm = new mroFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<MroView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<Inspection>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("МРО");
    frm->setSizeTbl(953, 200);
    frm->exec();
}

///-----------------------------------------------------------------------------
///
///         Меню.Справочник статей КоАП.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnArticle() {
    //QMessageBox::information(this, "АРМ Юриста", "Статьи КоАП");
    nsiFrm* frm = new nsiFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    Nsi::num_ = NSI_ARTICLE;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Статьи КоАП");
    frm->setSizeTbl(353, 570);
    frm->exec();
}


///-----------------------------------------------------------------------------
///
///         сигнально-слотовое соединение juristFrm<---->nsiFrm
///          
///-----------------------------------------------------------------------------

void juristFrm::createFrmConnector(const QDialog& frm) {
    ///выполнить команду на сервере
    connect(&frm, SIGNAL(runServerCmd(const QString&)), this, SIGNAL(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(this, SIGNAL(responseServer(const QString&)), &frm, SLOT(worker(const QString&)));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(&frm, SIGNAL(waitReady()), this, SIGNAL(waitReady()));
    ///сигнал завершения процесса обработки
    connect(&frm, SIGNAL(ready()), this, SIGNAL(ready()));

}

///-----------------------------------------------------------------------------
///
///         Инициализация ссылки на контроллер клиента.
///         сигнально-слотовое соединение juristFrm<---->m_pClientController
///          
///-----------------------------------------------------------------------------

void juristFrm::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    ///сигнал завершения процесса обработки
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(this, SIGNAL(waitReady()), m_pClientController, SLOT(waitReady()));
    ///выполнить команду на сервере
    connect(this, SIGNAL(runServerCmd(const QString&)), m_pClientController,
            SLOT(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(m_pClientController, SIGNAL(responseServer(const QString&)),
            this, SIGNAL(responseServer(const QString&)));

};


///-----------------------------------------------------------------------------
///
///         Обработать команду (ответ) сервера.
///          
///-----------------------------------------------------------------------------

void juristFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
            ///-----------------------------------------------------------------------------
            ///
            ///                         GET_LIST_MODELS
            ///          
            ///-----------------------------------------------------------------------------
            //Сервер вернул результат команды "GET_LIST_MODELS"  

        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            //Сервер вернул результат команды "GET_LIST_MODELS"  
            //Процесс обработки возвращённого реультата.    

            switch (model) {
                case ModelWrapper::Model::Mro:
                {
                    ItemContainer<Mro> mroContainer;
                    JsonSerializer::parse(wrapper.getData(), mroContainer);
                    QList<Mro> listmro = mroContainer.getItemsList();
                    setlistMro(listmro);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::RptColumn:
                {
                    //QMessageBox::information(this, "RptColumn", "RptColumn");
                    ItemContainer<RptColumn> rptcolumnContainer;
                    JsonSerializer::parse(wrapper.getData(), rptcolumnContainer);
                    QList<RptColumn> listrptcolumn = rptcolumnContainer.getItemsList();
                    setlistCol(listrptcolumn);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::RptRow:
                {
                    //    QMessageBox::information(this, "RptRow", "RptRow");
                    ItemContainer<RptRow> rptrowContainer;
                    JsonSerializer::parse(wrapper.getData(), rptrowContainer);
                    QList<RptRow> listrptrow = rptrowContainer.getItemsList();
                    setlistRow(listrptrow);
                    emit ready();
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case ModelWrapper::Command::CALL_PROCEDURE:
        {
            //QMessageBox::information(this, "CALL_PROCEDURE", "CALL_PROCEDURE");
            //Сервер вернул результат команды "LOGIN"     
            ItemContainer<ReportOut> rptoutContainer;
            JsonSerializer::parse(wrapper.getData(), rptoutContainer);
            QList<ReportOut> listresult = rptoutContainer.getItemsList();
            setlistResult(listresult);
            emit ready();
        }
            break;
        default:
            break;
    }
}


///-----------------------------------------------------------------------------
///
///         Справочник субъектов АП.
///          
///-----------------------------------------------------------------------------

void juristFrm::OnSubject() {
    nsiFrm* frm = new nsiFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    Nsi::num_ = NSI_SUBJECT;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Субъекты АП");
    frm->setSizeTbl(353, 200);
    frm->exec();
}



///-----------------------------------------------------------------------------
///
///         Генерация формы отчёта из Excel.
///          
///-----------------------------------------------------------------------------

void juristFrm::report() {
    //QMessageBox::critical(0, qApp->tr("Cannot open database"),
    //        qApp->tr("Unable to establish a database connection.\n"
    //        "This example needs SQLite support. Please read "
    //        "the Qt SQL driver documentation for information how "
    //        "to build it.\n\n"
    //        "Click Cancel to exit."), QMessageBox::Ok);

    QFile file("test2.csv");
    if (file.open(QIODevice::ReadOnly)) {
        //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
        int lineindex = 0; // file line counter
        QTextStream in(&file); // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n") 
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            //QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts); 
            QStringList lineToken = fileLine.split(";", QString::KeepEmptyParts);

            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model_->setItem(lineindex, j, item);
                item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                //item->setForeground();
                if (lineindex == 0 || lineindex == 7 || lineindex == 23 || lineindex == 26) {
                    //item->setForeground(QColor("orange"));
                    item->setFont(QFont("Times", 8, QFont::Bold, false));
                }
                if (lineindex == 1) {
                    if (j == 0) {
                        //                        item->setForeground(QColor("blue"));
                        item->setBackground(QColor("LightSkyBlue"));
                        item->setFont(QFont("Times", 8, QFont::Bold, false));
                    }
                    if (j == 8) {
                        item->setBackground(QColor("LightSkyBlue"));
                        //                        item->setForeground(QColor("red"));
                        item->setFont(QFont("Times", 8, QFont::Bold, false));
                    }
                }
                if (j == 0) {
                    if (lineindex > 1 && lineindex < 33) {
                        item->setBackground(QColor("LightGreen"));

                    }
                }
                if (j == 29) {
                    item->setBackground(QColor("LightGreen"));
                }
                if (j == 30) {
                    item->setBackground(QColor("LightPink"));
                }
                item->setToolTip("<a style='color:royalblue'> " + value + "</a>");
                item->setEditable(false);
                if (lineindex == 7 || lineindex == 23 || lineindex == 26) {
                    if (j == 0 || j == 1) {
                        item->setBackground(QColor("LightSkyBlue"));
                    }
                }
                if (lineindex == 33) {
                    item->setBackground(QColor("LightSkyBlue"));
                }

            }
            lineindex++;
        }
        file.close();
    }
    this->widget.tableView->setModel(model_);
    spanTbl();
    //this->widget.tableView->resizeColumnsToContents();
    //this->widget.tableView->resizeRowsToContents();
    //this->widget.tableView->setContentsMargins(10,10,10,10);
    //this->widget.tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //verticalResizeTableViewToContents();
    //this->widget.tableView->verticalHeader()->setsetRsetResizeMode( QHeaderView::Stretch);
    //  this->widget.tableView->horizontalHeader()->setResizeMode( QHeaderView::Stretch);
    this->widget.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->widget.tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    this->widget.tableView->rowHeight(7);
    this->widget.tableView->columnWidth(7);
    this->widget.tableView->horizontalHeader()->setDefaultSectionSize(3);
    this->widget.tableView->verticalHeader()->setDefaultSectionSize(3);
    //this->widget.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->widget.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->widget.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->widget.tableView->setColumnWidth(1, 290);

    for (int i = 16; i < 29; i++) {
        this->widget.tableView->setColumnWidth(i, 50);
    }
    for (int i = 29; i < 31; i++) {
        this->widget.tableView->setColumnWidth(i, 120);
    }
    for (int i = 0; i < 35; i++) {
        if (i > 7) {
            if (i != 10 && i != 21 && i != 22 && i != 23 && i != 24 && i != 25 && i != 26 && i != 33 && i != 34)
                this->widget.tableView->setRowHeight(i, 35);
        }
    }
    connect(this->widget.tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    //this->widget.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //this->widget.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //QString style = R"(
    //                QScrollBar:vertical {
    //                 background: #32CC99;
    //                }
    //                QScrollBar:horizontal {
    //                 background: #FF0000;
    //                }
    //               )";
}

void juristFrm::onTableClicked(const QModelIndex &index) {
    if (index.isValid()) {
        QString cellText = index.data().toString();
        if (!cellText.isEmpty()) {
            //QMessageBox::information(this, "АРМ Юриста", cellText);
        }
    }
}
///-----------------------------------------------------------------------------
///
///         Объединение ячеек таблицы.
///          
///-----------------------------------------------------------------------------

void juristFrm::spanTbl() {
    QFile file("test2.csv");
    if (file.open(QIODevice::ReadOnly)) {
        //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
        int lineindex = 0; // file line counter
        QTextStream in(&file); // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n") 
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            //QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts); 
            QStringList lineToken = fileLine.split(";", QString::KeepEmptyParts);

            // load parsed data to model accordingly
            if (lineindex < 8 || lineindex == 23 || lineindex == 26 || lineindex == 33 || lineindex == 34 || lineindex == 35) {
                int spanCol = 1;
                int j = 0;
                for (; j < lineToken.size(); j++) {
                    QString value = lineToken.at(j);
                    if (value.isEmpty()) {
                        spanCol++;
                    } else {
                        //qInfo() << QString::fromLocal8Bit(value.toStdString().c_str());
                        if (spanCol > 1) {
                            this->widget.tableView->setSpan(lineindex, j - spanCol, 1, spanCol);
                            //QString style = R"( )";
                            //this->widget.tableView->currentIndex()->child(lineindex, j - spanCol)->setStyleSheet(style);
                            spanCol = 1;
                        }
                    }
                    //QString style = R"()";
                }
                if (spanCol > 1) {
                    if (lineindex != 5) {
                        this->widget.tableView->setSpan(lineindex, j - spanCol, 1, spanCol);
                    }
                }
            }
            lineindex++;
        }

        file.close();
    }
}

///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void juristFrm::setlistMro(const QList<Mro>& mro) {
    mro_ = mro;
    this->widget.comboBox->clear();
    for (auto& t : mro_) {
        this->widget.comboBox->addItem(t.getName());
    }
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void juristFrm::setlistRow(const QList<RptRow>& listrow) {
    listrow_ = listrow;
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка результата
///          
///-----------------------------------------------------------------------------

void juristFrm::setlistResult(const QList<ReportOut>& result) {
    result_ = result;
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void juristFrm::setlistCol(const QList<RptColumn>& listcol) {
    listcol_ = listcol;
}
///-----------------------------------------------------------------------------
///
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::on_pushButton_Excel_clicked() {
    if (!pressed_) {
        pressed_ = true;
    } else {
        QMessageBox::information(this, "АРМ Юриста", "Идёт процесс формирования отчёта. Подождите, пожалуйста...");
        return;
    }
    //QMessageBox::information(this, "АРМ Юриста", "Выгрузка в Excel");
    // получаем указатель на Excel
    // [1]  Writing excel file(*.xlsx)
    QAxObject *mExcel = new QAxObject("Excel.Application", this);
    mExcel-> setProperty("Visible", true);
    // на книги
    QAxObject *workbooks = mExcel->querySubObject("Workbooks");
    // на директорию, откуда грузить книг
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", QString("d:/MyProjects_2021/ARMInspector/ARMInspectorGUI/Tmp/frm1.xlsx"));
    if (workbook == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "Open Excel error");
        return;
    }
    // на листы
    QAxObject *mSheets = workbook->querySubObject("Sheets");
    if (mSheets == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "Sheets Excel error");
        return;
    }
    // указываем, какой лист выбрать
    QAxObject *StatSheet = mSheets->querySubObject("Item(const QVariant&)", QVariant("Пинск"));
    if (StatSheet == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "StatSheet Excel error");
        return;
    }
    // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
    //QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", 1, 1);
    // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
    //cell->setProperty("Value", QVariant("Some value"));
    // освобождение памяти
    //delete cell;
    //delete StatSheet;
    //delete mSheets;
    //workbook->dynamicCall("Save()");
    //delete workbook;
    //закрываем книги
    //delete workbooks;
    //закрываем Excel
    //mExcel->dynamicCall("Quit()");
    //delete mExcel;
}


///-----------------------------------------------------------------------------
///
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

/*void juristFrm::on_pushButton_Excel_clicked() {

    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsx.saveAs("TestExcel.xlsx"); // save the document as 'Test.xlsx'
    // [2] Reading excel file(*.xlsx)
    Document xlsxR("TestExcel.xlsx");
    if (xlsxR.load()) // load excel file
    {
        int row = 1;
        int col = 1;
        Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
        if (cell != NULL) {
            QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
            qDebug() << var; // display value. it is 'Hello Qt!'.
        }
    }
    this->widget.tableView->clearFocus();
    QAxWidget* ExcelDocument = new QAxWidget("Excel.Application", this->widget.tableView);
    ExcelDocument-> setGeometry(QRect(1, 1, 1900, 1200));
    ExcelDocument->setControl("d:/MyProjects_2021/ARMInspector/ARMInspectorGUI/ExcelDocs/3.xlsx");
    ExcelDocument-> show();

}

void Window::importExcelToDatabase()
{
         QString strFilePathName = QFileDialog :: getOpenFileName (this, QStringLiteral ( "Select the Excel file"), "", tr ( "Exel file (* xls * .xlsx)").);
        if(strFilePathName.isNull())
        {
                return ;
        }
         QAxObject * excel = new QAxObject (this); // connect Excel Controls
        if(excel->setControl("Excel.Application"))
        {
        excel->setControl("Excel.Application")
        }
        else
        {
                 excel-> setControl ( "ket.Application"); // connect Excel Controls
        }
         excel-> setProperty ( "Visible", false); // do not display the form
         QAxObject * workbooks = excel-> querySubObject ( "WorkBooks"); // get a set of workbooks
         workbooks-> dynamicCall ( "Open (const QString &)", strFilePathName); // Open to open an existing workbook
         QAxObject * workbook = excel-> querySubObject ( "ActiveWorkBook"); // Get the current workbook 
         QAxObject * sheets = workbook-> querySubObject ( "Sheets"); // Get the sheet set, Sheets may be substituted therefore WorkSheets
         QAxObject * sheet = workbook-> querySubObject ( "WorkSheets (int)", 1); // Get worksheets collection sheet 1, i.e. sheet1
         QAxObject * range = sheet-> querySubObject ( "UsedRange"); // Get the scope of use of the sheet objects
        QVariant var = range->dynamicCall("Value");
        delete range;
         QVariantList varRows = var.toList (); // get all the data in the table
        if(varRows.isEmpty())
        {
                return;
        }
        const int rowCount = varRows.size();
        QStringList m_userid,m_card_id,m_action;
        for(int i = 1; i < rowCount; ++i)   //
        {
                QVariantList rowData = varRows[i].toList();
                m_userid<<rowData[0].toString();
                m_card_id<<rowData[1].toString();
                m_action<<rowData[2].toString();
        }
}
 */
///-----------------------------------------------------------------------------
///
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::on_pushButton_Report_clicked() {
    if (!pressed_) {
        pressed_ = true;
    } else {
        QMessageBox::information(this, "АРМ Юриста", "Идёт процесс формирования отчёта. Подождите, пожалуйста...");
        return;
    }
    //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
    QAxObject *mExcel = new QAxObject("Excel.Application", this);
    //mExcel-> setProperty("Visible", true);
    // на книги
    QAxObject *workbooks = mExcel->querySubObject("Workbooks");
    // на директорию, откуда грузить книг
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", QString("d:/MyProjects_2021/ARMInspector/ARMInspectorGUI/Tmp/frm1.xlsx"));
    if (workbook == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "Open Excel error");
        return;
    }
    // на листы
    QAxObject *mSheets = workbook->querySubObject("Sheets");
    if (mSheets == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "Sheets Excel error");
        return;
    }


    QJsonObject param;
    emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<RptColumn>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();


    model_->clear();
    this->showControlsFrm();
    this->report();
    //    model_->setData(model_->index(1, 8), "май 2021 года", Qt::EditRole);
    Report model;
    model.setMro(mro_.at(this->widget.comboBox->currentIndex()).getId());
    model.setMon(this->widget.dateEdit->date().month());
    model.setYear(this->widget.dateEdit->date().year());
    // указываем, какой лист выбрать
    QString mro;
    if (model.getMro() == 1) mro = "Брест";
    if (model.getMro() == 2) mro = "Барановичи";
    if (model.getMro() == 3) mro = "Пинск";
    if (model.getMro() == 4) mro = "";
    QAxObject *StatSheet = mSheets->querySubObject("Item(const QVariant&)", QVariant(mro));
    if (StatSheet == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "StatSheet Excel error");
        return;
    }

    //QMessageBox::information(this, "АРМ Юриста", "МРО:" + QString::number(model.getMro()) + "месяц:  " + QString::number(model.getMon()) + "год:" + QString::number(model.getYear()));
    ///Получить значение RadioBox
    QList<QRadioButton *> buttons;
    buttons = this->widget.groupBox->findChildren<QRadioButton *>();
    int period = 0;
    for (int i = 1; i <= buttons.size(); ++i) {
        if (buttons[i - 1]->isChecked()) {
            //user->setStatus(i);
            period = i;
            break;
        }
    }

    //QMessageBox::information(this, "АРМ Юриста", this->widget.dateEdit->date().longMonthName(model.getMon()));
    //Определение периода отчёта.
    switch (period) {

        case 1://Данные за месяц
        {
            QString prd = "";
            prd += this->widget.dateEdit->date().longMonthName(model.getMon()); //название месяца
            prd += " ";
            prd += QString::number(model.getYear()); //год
            prd += " года";
            model_->setData(model_->index(1, 8), prd, Qt::EditRole);
            model.setCummulative(0);
        }
            break;
        case 2://Данные за квартал
        {
            int kv;
            kv = model.getMon() / 3;
            if (model.getMon() % 3 > 0) {
                kv++;
            }
            QString prd = "";
            prd += QString::number(kv); //квартал
            prd += " квартал ";
            prd += QString::number(model.getYear());
            prd += " года";
            model_->setData(model_->index(1, 8), prd, Qt::EditRole);
            model.setCummulative(kv);
        }
            break;
        case 3://Данные с начала года
        {
            QString prd = "";
            prd += QString::number(model.getYear());
            prd += " год(С начала года).";
            model_->setData(model_->index(1, 8), prd, Qt::EditRole);
            model.setCummulative(11);
        }
            break;
    }
    //model.setMro(this->widget->comboBox->ge)
    //QMessageBox *msgBox = new QMessageBox();
    //msgBox->setText("Загружаются данные, пожалуйста, подождите ...");
    //msgBox->show();
    //msgBox->setAttribute(Qt::WA_DeleteOnClose);

    //QHBoxLayout *layout = new QHBoxLayout();
    //QProgressBar *progressBar = new QProgressBar();
    //progressBar->setMinimum(0);
    //progressBar->setMaximum(listrow_.size() * listcol_.size());
    //layout->addWidget(progressBar);
    //setLayout(layout);
    // QTimer::singleShot(9000, msgBox, SLOT(close()));
    //QMessageBox::information(this, "АРМ Юриста",
    //        "<br> МРО" + QString::number(model.getMro()) +
    //        "<br> отчётный месяц" + QString::number(model.getMon()) +
    //        "<br>год - " + QString::number(model.getYear())
    //       );

    myProgressBar* frmProgress = new myProgressBar(this);
    frmProgress->getUI()->progressBar->setMinimum(0);
    frmProgress->getUI()->progressBar->setMaximum(listrow_.size() * listcol_.size());
    frmProgress->setAttribute(Qt::WA_DeleteOnClose);
    frmProgress->show();
    for (int i = 0; i < listrow_.size(); i++) {
        RptRow rptrow = listrow_.at(i);
        model.setNumrow(rptrow.getRow());
        emit runServerCmd(Functor<Report>::produce(ModelWrapper::Command::CALL_PROCEDURE, model));
        emit waitReady();
        int col = 0;
        int mon_total = 0;
        double sum_total = 0;
        bool sum = false;
        if (rptrow.getRow() == 25 || rptrow.getRow() == 26) {//строки сумм штрафов
            sum = true;
        } else {
            sum = false;
        }
        for (int j = 0; j < result_.size(); j++) {
            frmProgress->getUI()->progressBar->setValue(frmProgress->getUI()->progressBar->value() + 1);
            col = j + 2;
            ReportOut rptout = result_.at(j);
            if (rptout.getCount() > 0) {
                if (rptout.getCol() < 29) {
                    if (sum) {
                        sum_total += rptout.getCount();
                    } else {
                        mon_total += rptout.getCount();
                    }
                    model_->setData(model_->index(rptrow.getRow() - 1, rptout.getCol() - 1), rptout.getCount(), Qt::EditRole);
                } else if (rptout.getCol() == 30) {
                    model_->setData(model_->index(rptrow.getRow() - 1, rptout.getCol()), rptout.getCount(), Qt::EditRole);
                }
                if (!mro.isEmpty()) {
                    // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                    QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", rptrow.getRow(), rptout.getCol());
                    // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                    cell->setProperty("Value", QVariant(rptout.getCount()));
                    delete cell;
                }

            }
        }
        if (mon_total > 0 || sum_total > 0) {
            if (sum) {
                model_->setData(model_->index(rptrow.getRow() - 1, col), QString::number(sum_total, 'f', 2), Qt::EditRole);
                if (!mro.isEmpty()) {
                    // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                    QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", rptrow.getRow(), col + 1);
                    // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                    cell->setProperty("Value", QVariant(sum_total));
                    delete cell;

                }

            } else {
                model_->setData(model_->index(rptrow.getRow() - 1, col), QString::number(mon_total), Qt::EditRole);
                if (!mro.isEmpty()) {
                    // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                    QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", rptrow.getRow(), col + 1);
                    // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                    cell->setProperty("Value", QVariant(mon_total));
                    delete cell;

                }

            }
        }
    }
    frmProgress->close();
    //msgBox->close();
    delete StatSheet;
    delete mSheets;
    //workbook->dynamicCall("Save()");
    workbook->dynamicCall("SaveAS(const QString&)", QDir::toNativeSeparators("d:/MyProjects_2021/ARMInspector/ARMInspectorGUI/Tmp/frm1.xlsx"));
    delete workbook;
    //закрываем книги
    delete workbooks;
    //закрываем Excel
    mExcel->dynamicCall("Quit()");
    delete mExcel;
    pressed_ = false;

}


///-----------------------------------------------------------------------------
///
///         Спрятать элементы формы отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::hideControlsFrm() {

    this->widget.comboBox->setHidden(true);
    this->widget.dateEdit->setHidden(true);
    this->widget.groupBox->setHidden(true);
    this->widget.tableView->setHidden(true);
    this->widget.pushButton_Excel->setHidden(true);
    this->widget.pushButton_Report->setHidden(true);
    this->widget.pushButton_Report->setHidden(true);
    this->widget.label_Data->setHidden(true);
    this->widget.label_Mro->setHidden(true);
    this->widget.label_Period->setHidden(true);
}

///-----------------------------------------------------------------------------
///
///         Показать элементы формы отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::showControlsFrm() {
    this->widget.comboBox->setVisible(true);
    this->widget.dateEdit->setVisible(true);
    this->widget.groupBox->setVisible(true);
    this->widget.tableView->setVisible(true);
    this->widget.pushButton_Excel->setVisible(true);
    this->widget.pushButton_Report->setVisible(true);
    this->widget.pushButton_Report->setVisible(true);
    this->widget.label_Data->setVisible(true);
    this->widget.label_Mro->setVisible(true);
    this->widget.label_Period->setVisible(true);

}
//  QFile styleF;
//    styleF.setFileName(":/qss/style.qss");
//    styleF.open(QFile::ReadOnly);
//    QString qssStr = styleF.readAll();
//    qApp->setStyleSheet(qssStr);
//https://www.programmersought.com/article/2906246923/

//void juristFrm::closeEvent(QCloseEvent *event) {
//    event->accept();
//    QMainWindow::closeEvent(event);
//(new DialogDestroyer())->DelayedDestruction(this);
//}