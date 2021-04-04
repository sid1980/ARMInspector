/****************************************************************************
 **
 **            Класс для обработки сообщений от сервера. 
 ** 
 ****************************************************************************/

/* 
 * File:   WorkerClient.h
 * Author: ASK
 *
 * Created on 14 декабря 2019 г., 19:50
 */

#ifndef WORKERCLIENT_H
#define WORKERCLIENT_H
#include <QtCore>
#include "ModelWrapper.h"
#include "JsonSerializer.h"
#include "ItemContainer.h"
#include "ModelList.h"
#include "User.h"
#include "Inspection.h"


class WorkerClient : public QObject {
    Q_OBJECT

public:

    /// Стандартный конструктор.
    /// @param apParent Родитель.
    WorkerClient(QObject *apParent = nullptr);
    /// Стандартный конструктор.
    ~WorkerClient();

    void setModelWrapperString(const QString& asWrapperString );
    const QString& getModelWrapperString() const;
    ///Основная функция потока
    void process();

public slots:

signals:
    ///Установить идентификатор клиента
    void setID(int asID);
    ///Получить список инспекций
    void getInspections();
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();

private:
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
};

#endif /* WORKERCLIENT_H */

