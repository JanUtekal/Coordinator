#include "acl.h"

Acl::Acl(QString id,QString name)
{
    this->id=id;
    this->name=name;
}

QString Acl::getId(){
    return this->id;
}

QString Acl::getName(){
    return this->name;
}

QString Acl::getFrom(){
    return this->from;
}

QString Acl::getTo(){
    return this->to;
}

void Acl::setId(QString id){
    this->id=id;
}

void Acl::setName(QString name){
    this->name=name;
}

void Acl::setFrom(QString from){
    this->from=from;
}

void Acl::setTo(QString to){
    this->to=to;
}


