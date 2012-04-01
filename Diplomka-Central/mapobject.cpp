#include "mapobject.h"
#include <QDebug>
MapObject::MapObject(){
}

void MapObject::setPaintedObject(QVariant object){
    this->paintedObject=object;

}

void MapObject::setType(int type){
    this->type=type;
}

void MapObject::setName(QString name){
    this->name=name;
}

QVariant MapObject::getPaintedObject(){
    return this->paintedObject;
}

int MapObject::getType(){
    return this->type;
}

QString MapObject::getName(){
    return this->name;
}
