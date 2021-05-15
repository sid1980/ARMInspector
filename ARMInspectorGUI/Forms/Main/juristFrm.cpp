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
#include "QMessageBoxEx.h"
#include <QFile>
#include <QTextStream>
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
    //QMessageBox::information(this, "АРМ Юриста", "OnInspection()");
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
                default:
                    break;
            }
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
                item->setEditable(false);
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
    //connect(this->widget.tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
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
        QMessageBox::information(this, "АРМ Юриста", cellText);

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
            if (lineindex < 8 || lineindex == 23 || lineindex == 26 || lineindex == 33 || lineindex == 34|| lineindex == 35) {
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
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

void juristFrm::on_pushButton_Report_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
    model_->clear();
    this->showControlsFrm();
    this->report();
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