/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserV1.cpp
 * Author: kazun_as
 * 
 * Created on 5 апреля 2021 г., 10:41
 */

#include "UserV1.h"

UserV1::UserV1() {
}

UserV1::~UserV1() {
}

void UserV1::setId(const qint64& id) {
    id_ = id;
};

void UserV1::setFio(const QString& fio) {
    fio_ = fio;
};

void UserV1::setInspection(const QString& inspection) {
    inspection_ = inspection;
};

void UserV1::setName(const QString& name) {
    name_ = name;
};

const qint64& UserV1::getId() const {
    return id_;
};

const QString& UserV1::getFio() const {
    return fio_;
};

const QString& UserV1::getInspection() const {
    return inspection_;
};

const QString& UserV1::getName() const {
    return name_;
};

void UserV1::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setFio(jsonObj["fio"].toString());
    this->setInspection(jsonObj["name_i"].toString());
    this->setName(jsonObj["name"].toString());
};

void UserV1::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["fio"] = this->getFio();
    jsonObj["name_i"] = this->getInspection();
    jsonObj["name"] = this->getName();

};

QVariant UserV1::getData(int position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getFio();
        case 2:
            return this->getInspection();
        case 3:
            return this->getName();
        default:
            return 0;
            break;
    }

};

