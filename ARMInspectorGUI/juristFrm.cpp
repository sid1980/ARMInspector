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

juristFrm::juristFrm() {
    widget.setupUi(this);
    model_ = new QStandardItemModel;
    m_pMenuBar = new QMenuBar(this);
    this->setMenuBar(m_pMenuBar);
    QMenu * menu1 = m_pMenuBar->addMenu("&Журнал");
    QMenu * menu = m_pMenuBar->addMenu("&Отчеты по АП");
    //menu->setLayoutDirection(Qt::RightToLeft); // Display menu bar to the right
    // New
    QAction * action = new QAction("&Отчёт Приложение 1", this);
    action->setIcon(QPixmap("Icons/icons8-file-48.png"));
    connect(action, &QAction::triggered, this, &juristFrm::OnGenerateReport);
    menu->addAction(action);
    // Open
    action = new QAction("&Отчёт Приложение 2", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnGenerateReprt2);
    menu->addAction(action);
    // Save
    action = new QAction("&Выход", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnExit);
    menu->addAction(action);
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

juristFrm::~juristFrm() {
    delete m_pMenuBar;
    delete model_;
}

QMenuBar * juristFrm::getMenuBar() {
    return m_pMenuBar;
}

void juristFrm::OnGenerateReport() {
    //QVBoxLayout *layout = new QVBoxLayout;
    //ayout->addWidget(widget->tableView);
    this->showControlsFrm();
    report();
    //QMessageBox::information(0, "Menu", "Отчёт Приложение 1");
}

void juristFrm::OnGenerateReprt2() {
    model_->clear();
    this->hideControlsFrm();

}

void juristFrm::OnExit() {

    QMessageBoxEx::StandardButton reply;
    reply = QMessageBoxEx::question(this, "Завершение работы АРМ Инспектор",
            "Вы действительно хотите завершить работу ? ",
            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        qApp->quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}




///-----------------------------------------------------------------------------
///
///         Отчёт.
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

    for (int i = 16; i < 27; i++) {
        this->widget.tableView->setColumnWidth(i, 50);
    }
    for (int i = 27; i < 29; i++) {
        this->widget.tableView->setColumnWidth(i, 120);
    }
    for (int i = 0; i < 34; i++) {
        if (i > 6) {
            if (i != 9 && i != 20 && i != 21 && i != 22 && i != 23 && i != 24 && i != 25 && i != 32 && i != 33)
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
            if (lineindex < 7 || lineindex == 22 || lineindex == 25 || lineindex == 32 || lineindex == 33) {
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
                    if (lineindex != 4) {
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
///         Инициализация ссылки на контроллер клиента.
///          
///-----------------------------------------------------------------------------

void juristFrm::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    // Сигнально-слотовое соединение, сигнализирующее, что   контроллер комманд
    // готов вернуть  результат  выполнения запроса к серверу.
    connect(m_pClientController, SIGNAL(listMroReady(const QList<Mro>&)),
            this, SLOT(setlistMro(const QList<Mro>&)));

};
///-----------------------------------------------------------------------------
///
///         Инициализация ссылки на контроллер клиента.
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