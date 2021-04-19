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
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

juristFrm::juristFrm() {
    widget.setupUi(this);
    m_pMenuBar = new QMenuBar(this);
    this->setMenuBar(m_pMenuBar);
    QMenu * menu = m_pMenuBar->addMenu("&Отчеты по АП");
    // New
    QAction * action = new QAction("&Отчёт Приложение 1", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnFileNew);
    menu->addAction(action);
    // Open
    action = new QAction("&Отчёт Приложение 2", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnFileOpen);
    menu->addAction(action);
    // Save
    action = new QAction("&Выход", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnFileSave);
    menu->addAction(action);
    QString style = R"(
QMenuBar {
    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 lightgray, stop:1 darkgray);
    spacing: 3px; /* spacing between menu bar items */
}

QMenuBar::item {
    padding: 1px 4px;
    background: transparent;
    border-radius: 4px;
}

QMenuBar::item:selected { /* when selected using mouse or keyboard */
    background: #a8a8a8;
}

QMenuBar::item:pressed {
    background: #888888;
}
               )";
    m_pMenuBar->setStyleSheet(style);

    QString style1 = R"(
QMenu {
    background-color: white;
    margin: 2px; /* some spacing around the menu */
}

QMenu::item {
    padding: 2px 25px 2px 20px;
    border: 1px solid transparent; /* reserve space for selection border */
}

QMenu::item:selected {
    border-color: darkblue;
    background: rgba(100, 100, 100, 150);
}

QMenu::icon:checked { /* appearance of a 'checked' icon */
    background: gray;
    border: 1px inset gray;
    position: absolute;
    top: 1px;
    right: 1px;
    bottom: 1px;
    left: 1px;
}

QMenu::separator {
    height: 2px;
    background: lightblue;
    margin-left: 10px;
    margin-right: 5px;
}

QMenu::indicator {
    width: 13px;
    height: 13px;
}

/* non-exclusive indicator = check box style indicator (see QActionGroup::setExclusive) */
QMenu::indicator:non-exclusive:unchecked {
    image: url(:/images/checkbox_unchecked.png);
}

QMenu::indicator:non-exclusive:unchecked:selected {
    image: url(:/images/checkbox_unchecked_hover.png);
}

QMenu::indicator:non-exclusive:checked {
    image: url(:/images/checkbox_checked.png);
}

QMenu::indicator:non-exclusive:checked:selected {
    image: url(:/images/checkbox_checked_hover.png);
}

/* exclusive indicator = radio button style indicator (see QActionGroup::setExclusive) */
QMenu::indicator:exclusive:unchecked {
    image: url(:/images/radiobutton_unchecked.png);
}

QMenu::indicator:exclusive:unchecked:selected {
    image: url(:/images/radiobutton_unchecked_hover.png);
}

QMenu::indicator:exclusive:checked {
    image: url(:/images/radiobutton_checked.png);
}

QMenu::indicator:exclusive:checked:selected {
    image: url(:/images/radiobutton_checked_hover.png);
}
               )";
    menu->setStyleSheet(style1);
    //m_pMenuBar->setStyle();
}

juristFrm::~juristFrm() {
    delete m_pMenuBar;
}

QMenuBar * juristFrm::getMenuBar() {
    return m_pMenuBar;
}

void juristFrm::OnFileNew() {
    //QVBoxLayout *layout = new QVBoxLayout;
    //ayout->addWidget(widget->tableView);
    report();
    //QMessageBox::information(0, "Menu", "Отчёт Приложение 1");
}

void juristFrm::OnFileSave() {
    QMessageBox::information(0, "Menu", "Выход");

}

void juristFrm::OnFileOpen() {
    QMessageBox::information(0, "Menu", "Отчёт Приложение 2");

}



///Отчёт

void juristFrm::report() {
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
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
                item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                item->setEditable(false);
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
void juristFrm::onTableClicked(const QModelIndex &index){
    if (index.isValid()) {
        QString cellText = index.data().toString(); 
        QMessageBox::information(this, "АРМ Юриста", cellText);
        
    }
}
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
//  QFile styleF;
//    styleF.setFileName(":/qss/style.qss");
//    styleF.open(QFile::ReadOnly);
//    QString qssStr = styleF.readAll();
//    qApp->setStyleSheet(qssStr);
//https://www.programmersought.com/article/2906246923/