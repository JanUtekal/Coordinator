#include "terrainuser.h"

TerrainUser::TerrainUser(QString id,QString name, QString surname, QString jid)
{
    this->id=id;
    this->name=name;
    this->surname=surname;
    this->jid=jid;
}

QString TerrainUser::getId(){
    return this->id;
}

QString TerrainUser::getName(){
    return this->name;
}

QString TerrainUser::getSurname(){
    return this->surname;
}

QString TerrainUser::getJid(){
    return this->jid;
}

void TerrainUser::setId(QString id){
    this->id=id;
}

void TerrainUser::setName(QString name){
    this->name=name;
}

void TerrainUser::setSurname(QString surname){
    this->surname=surname;
}

void TerrainUser::setJid(QString jid){
    this->jid=jid;
}
