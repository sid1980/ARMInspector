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
    
    
    this->widget.tableView->resizeRowsToContents();
    this->widget.tableView->resizeColumnsToContents();
    QHeaderView* horHeader = this->widget.tableView->horizontalHeader();
    QHeaderView* verHeader = this->widget.tableView->verticalHeader();
    int rows = model->rowCount();
    int cols = model->columnCount();
    int x = horHeader->sectionViewportPosition(cols - 1) + horHeader->offset()
            + horHeader->sectionSize(cols - 1) + 1;
    int y = verHeader->sectionViewportPosition(rows - 1) + verHeader->offset()
            + verHeader->sectionSize(rows - 1) + 1;
    QPoint p = this->widget.tableView->viewport()->mapToParent(QPoint(x, y));
    QRect g = this->widget.tableView->geometry();
    g.setSize(QSize(p.x(), p.y()));
    this->widget.tableView->setGeometry(g);
}
///Список пользователей

void MainWindow::ListUsers() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    m_pClientController->getListModels(ModelWrapper::Model::UserView);

}

void MainWindow::initClient(ClientController * clientController) {
    m_pClientController = clientController;

};

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

void MainWindow::verticalResizeTableViewToContents() {
    int count = this->widget.tableView->verticalHeader()->count();
    int scrollBarH = this->widget.tableView->horizontalScrollBar()->height();
    int horizontalHeaderHeight = this->widget.tableView->horizontalHeader()->height();
    int rowTotalHeight = 0;
    for (int i = 0; i < count; ++i) {
        // 2018-03 edit: only account for row if it is visible
        if (!this->widget.tableView->verticalHeader()->isSectionHidden(i)) {
            rowTotalHeight += this->widget.tableView->verticalHeader()->sectionSize(i);
        }
    }
    this->widget.tableView->setMinimumHeight(horizontalHeaderHeight + rowTotalHeight + scrollBarH);
}