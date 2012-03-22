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

void Acl::setId(QString id){
    this->id=id;
}

void Acl::setName(QString name){
    this->name=name;
}

