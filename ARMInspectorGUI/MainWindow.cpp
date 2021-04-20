/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainWindow.cpp
 * Author: kazun_as
 *
 * Created on 5 февраля 2021 г., 10:26
 */

#include "MainWindow.h"
#include "reportFrm.h"
#include <QStandardItemModel>
#include <QScrollBar>

MainWindow::MainWindow() {
    widget.setupUi(this);
    connect(this->widget.actionReport, SIGNAL(triggered()), this, SLOT(Report()));
    connect(this->widget.actionListUsers, SIGNAL(triggered()), this, SLOT(ListUsers()));
    reportDlg_ = new reportFrm(this);

}

MainWindow::~MainWindow() {
    delete reportDlg_;
}


///Отчёт

void MainWindow::Report() {
    //QMessageBox::critical(0, qApp->tr("Cannot open database"),
    //        qApp->tr("Unable to establish a database connection.\n"
    //        "This example needs SQLite support. Please read "
    //        "the Qt SQL driver documentation for information how "
    //        "to build it.\n\n"
    //        "Click Cancel to exit."), QMessageBox::Ok);

    QStandardItemModel *model = new QStandardItemModel;
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
            int spanCol = 0;
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }
            lineindex++;
        }

        file.close();
    }
    this->widget.tableView->setModel(model);
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
    this->widget.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->widget.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //QString style = R"(
//                QScrollBar:vertical {
//                 background: #32CC99;
//                }
//                QScrollBar:horizontal {
//                 background: #FF0000;
//                }
//               )";
    
}
///-----------------------------------------------------------------------------
///
///         Список пользователей.
///          
///-----------------------------------------------------------------------------

void MainWindow::ListUsers() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    m_pClientController->getListModels(ModelWrapper::Model::UserView);

}

void MainWindow::initClient(ClientController * clientController) {
    m_pClientController = clientController;

};

///-----------------------------------------------------------------------------
///
///         spanTbl.
///          
///-----------------------------------------------------------------------------

void MainWindow::spanTbl() {
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
            if (lineindex < 7) {
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
                            spanCol = 1;
                        }
                    }
                }
                if (spanCol > 1) {
                    this->widget.tableView->setSpan(lineindex, j - spanCol, 1, spanCol);
                }
            }
            lineindex++;
        }

        file.close();
    }
}


