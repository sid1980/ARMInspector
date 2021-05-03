/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientController_IMPL.h
 * Author: kazun_as
 *
 * Created on 3 мая 2021 г., 11:07
 */

#ifndef CLIENTCONTROLLER_IMPL_H
#define CLIENTCONTROLLER_IMPL_H
// Nothing changed here

///-----------------------------------------------------------------------------
///
///             Получить список моделей.
///
///-----------------------------------------------------------------------------

/// Выполнить Sql запрос для объекта класса Т. T - шаблон модели для которй 
/// выполняется запрос. Результат работы запроса упаковывается в секцию данных
/// командной обёртки m_pModellWrapper.

template<typename T> void ClientController::addModel(T& model) {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    //Проверить , открыта ли  база данных. 
    //if (!connectDB<T>()) {
    //    return;
   // }
    //getAllRecordS<T>();
    //return;
        // Сигнально-слотовое соединение для полуяения  сведений о   пользователе из  базы данных.
        connect(m_pWorkerClient, SIGNAL(setModel(const T&)), SLOT(setModel<T>(const T&)));

}
#endif /* CLIENTCONTROLLER_IMPL_H */

