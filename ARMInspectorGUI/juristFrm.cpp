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

juristFrm::juristFrm() {
    widget.setupUi(this);
    m_pMenuBar = new QMenuBar(this);
    this->setMenuBar(m_pMenuBar);
    QMenu * menu = m_pMenuBar->addMenu("&File");
    // New
    QAction * action = new QAction("&New", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnFileNew);
    menu->addAction(action);
    // Open
    action = new QAction("&Open", this);
    connect(action, &QAction::triggered, this, &juristFrm::OnFileOpen);
    menu->addAction(action);
    // Save
    action = new QAction("&Save", this);
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
    QMessageBox::information(0, "Menu", "FileNew");

}

void juristFrm::OnFileSave() {
    QMessageBox::information(0, "Menu", "FileSave");

}

void juristFrm::OnFileOpen() {
    QMessageBox::information(0, "Menu", "FileOpen");

}
