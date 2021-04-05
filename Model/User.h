
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

class User : public JsonSerializable {
public:
    User();
    virtual ~User();
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
    void read(const QJsonObject &jsonObj);
    void write(QJsonObject &jsonObj) const;

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "ФИО", "Инспекция",
            "Имя пользователя", "Пароль", "Статус", "Роль", "Доступ", "Требование", "Должность"};
        return jsonArray;
    }

    static const QString getModelName() {
        return QString("User");
    }
    QVariant getData(int position) const;
    //QVariant getFieldValue() {
    //    return QVariant();
    //};

private:
    qint64 id_;
    QString fio_;
    qint64 inspection_;
    QString name_;
    QString password_;
    qint64 status_;
    qint64 role_;
    qint64 access_;
    qint64 claim_;
    qint64 position_;

};

#endif /* USER_H */

