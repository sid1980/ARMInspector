/****************************************************************************
 **
 **         Реализация методов класса  Seance.
 **
 ****************************************************************************/

/* 
 * File:   Seance.cpp
 * Author: kazun_as
 * 
 * Created on 16 декабря 2019 г., 11:39
 */

#include "Seance.h"
#include <QDebug>

///Список сеансов.
QVector<Seance*> Seance::m_aInstances;
/// Конструктор.
/// @param asModelWrapper Данны, полученные от клиента,
///обёрнутые в командную оболочку и сериализованные в строку.  

Seance::Seance(QString asModelWrapper) {
    //Сохранить указатель на экземпляр класса Seance в списке.
    m_aInstances.push_back(this);
    //Записать данные.
    m_aModelWrapperString = asModelWrapper;
}

///Деструктор.

Seance::~Seance() {
    ///Искать сеанс в списке.
    QVector<Seance*>::iterator p = std::find(m_aInstances.begin(), m_aInstances.end(), this);
    ///Если сеанс найдена, убрать его из списка.
    if (p != m_aInstances.end()) {
        m_aInstances.erase(p);
    }
    //Удалить поток.
    if (m_pThread != nullptr) {
        qDebug() << "Stop Thread";
        m_pThread->quit();
        m_pThread->wait();
    }
}


/// Создать новый поток.

void Seance::addThread() {
    //Создать командную обёртку . 
    //Она необходима  для передачи  сообщения сессии в случае   
    //возникновения ошибки.
    ModelWrapper wrapper;
    //Задать  функцию для установки сообщения об ошибке.
    auto setResult = [ &wrapper](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        wrapper.setMessage(result.str);
        wrapper.setSuccess(result.success);
    };

    //Создать новый поток.
    m_pThread = std::unique_ptr<QThread>(new QThread());
    if (m_pThread == nullptr) {
        ///Не удалось создать поток в сеансе
        setResult(Message::FAILED_CREATE_THREAD);
        //Завернуть ответ в   командную обёртку.
        QString asErrorString = JsonSerializer::serialize(wrapper);
        //Сигнализировать  сессии, что обработка запроса завершена;
        emit onReadyResult(this, asErrorString);
        return;
    }


    //Поток создан.
    //Создать объект класса Worker, который выполняет основную работу
    //с базой данных
    m_pWorker = std::unique_ptr<Worker>(new Worker());
    if (m_pWorker == nullptr) {
        ///Не удалось создать экземпляр класса, подсоединяемого к потоку. 
        setResult(Message::FAILED_CREATE_WORKER);
        //Завернуть ответ в   командную обёртку.
        QString asErrorString = JsonSerializer::serialize(wrapper);
        //Сигнализировать  сессии, что обработка запроса завершена;
        emit onReadyResult(this, asErrorString);
        return;
    }

    //Экземпляр класса Worker создан.
    //Переместить данные в Worker.
    m_pWorker->setModelWrapperString(m_aModelWrapperString);
    //Переместить Worker  во вновь созданный поток.
    m_pWorker.get()->moveToThread(m_pThread.get());
    connect(m_pWorker.get(), &Worker::error, this, &Seance::errorString);
    //Создать соединение, которое запустит Worker::process() при старте нового потока. 
    connect(m_pThread.get(), &QThread::started, m_pWorker.get(), &Worker::process);
    //Создать соединение, которое обработает возвращенный результат. 
    connect(m_pWorker.get(), &Worker::finished, this, &Seance::handleResult);
    //Создать соединение, которое остановит работу  нового потока. 
    connect(m_pWorker.get(), &Worker::finished, m_pThread.get(), &QThread::quit);
    //Создать соединение, которое удалит  поток. 
    connect(m_pThread.get(), &QThread::finished, m_pThread.get(), &QThread::deleteLater);
    //Стартовать поток.
    m_pThread->start();
    return;
}

/// Обработать возвращённый результат  запроса.
/// @param asQuery возвращенные Worker. 

void Seance::handleResult(QString asQuery) {
    qDebug() << "Session::handleResult";
    //Сигнализировать  сессии, что обработка запроса завершена;
    emit onReadyResult(this, asQuery);
}


///Сообщение об ошибке при работе с потоками.
/// @param asError Ошибка апри работе с потоками.

void Seance::errorString(QString asError) {

    qCritical() << QString("addThread FAILURE:  %s").arg(asError);

}
