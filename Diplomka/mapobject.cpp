/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012

 */

#include "mapobject.h"
#include <QDebug>
#include <QVector>
#include <QPointF>
//this class represents object to be saved into landmarks and displayed on map
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

void MapObject::setGeometry(QVector<QPointF> geometry){
    this->geometry=geometry;
}

QVector<QPointF> MapObject::getGeometry(){
    return this->geometry;
}

