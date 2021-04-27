/****************************************************************************
 **
 **             Класс модели пользователя User.
 **
 ****************************************************************************/

/* 
 * File:   User.h
 * Author: 1
 *
 * Created on 20 ноября 2019 г., 15:47
 */

#ifndef USER_H
#define USER_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <array>
using namespace std;
class User : public JsonSerializable, Model {
    
public:
    
    ///Конструктор
    User();
    ///Деструктор
    virtual ~User();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setFio(const QString& fio);
    void setInspection(const qint64& inspection);
    void setName(const QString& name);
    void setPassword(const QString& password);
    void setStatus(const qint64& status);
    void setRole(const qint64& role);
    void setAccess(const qint64& access);
    void setClaim(const qint64& claim);
    void setPosition(const qint64& position);
    const qint64& getId()const;
    const QString& getFio()const;
    const qint64& getInspection()const;
    const QString& getName()const;
    const QString& getPassword()const;
    const qint64& getStatus()const;
    const qint64& getRole()const;
    const qint64& getAccess()const;
    const qint64& getClaim()const;
    const qint64& getPosition()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "ФИО",
            "Инспекция",
            "Имя пользователя",
            "Пароль",
            "Статус",
            "Роль",
            "Доступ",
            "Требование",
            "Должность"
        };
        return jsonArray;
    }

    ///Список названий полей базы
     array<QString, 10>  getFields() {
        return fld_;
    }


    ///название модели
    static const QString getModelName() {
        return QString("User");
    }
    ///SQL запрос вывода данных

    static const QString getQuery() {
        return QString("Select *  from user ");
    }
    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from user ");
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);

private:
    enum Column {
            ID =0,
            FIO,
            ID_INSPECTION,
            NAME,
            PASSWORD,
            STATUS,
            ROLE,
            ACCESS,
            CLAIM,
            POSITION
    };     
    array<QString, 10> fld_= {
            "id",
            "fio",
            "id_inspection",
            "name",
            "password",
            "status",
            "role",
            "access",
            "claim",
            "position"
        };
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///ФИО пользователя
    QString fio_;
    ///Идентификатор инспекции
    qint64 inspection_;
    ///Имя пользователя при въходе в задачу
    QString name_;
    ///Пароль
    QString password_;
    ///Идентификатор статуса
    qint64 status_;
    ///Идентификатор роли
    qint64 role_;
    ///Доступ (чтение.запись)
    qint64 access_;
    ///Резервный идентификатор
    qint64 claim_;
    ///Идентификатор должности
    qint64 position_;
};

#endif /* USER_H */
