/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Inspection.cpp
 * Author: kazun
 * 
 * Created on 3 апреля 2021 г., 21:58
 */

#include "Inspection.h"

Inspection::Inspection() {
}

//Inspection::Inspection(const Inspection& orig) {
//}

Inspection::~Inspection() {
}

void Inspection::setId(const qint64& id) {
    id_ = id;
};

void Inspection::setName(const QString& name) {
    name_ = name;
};

void Inspection::setMro(const qint64& mro) {
    mro_ = mro;
};
    const qint64& Inspection::getId()const{
        return id_;
    };
    const QString&  Inspection::getName()const{
        return name_;
    };
    const qint64& Inspection::getMro()const{
        return mro_;
    };

void Inspection::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setName(jsonObj["name_i"].toString());
    this->setMro(jsonObj["id_mro"].toInt());
};

void Inspection::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["name_i"] = this->getName();
    jsonObj["id_mro"] = this->getMro();
};
    
    QVariant Inspection::getData(int position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getName();
        case 2:
            return this->getMro();
        default:
            return 0;
            break;
    }


};
