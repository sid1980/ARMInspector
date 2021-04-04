/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MainWindow.h"

bool MainWindow::event(QEvent* ev) {
        if (ev->type() == QEvent::LayoutRequest) {
            setFixedSize(sizeHint());
        }
        return result = QMainWindow::event(ev);
    }