#include "terrainuser.h"

TerrainUser::TerrainUser(QString id,QString name, QString surname, QString password, QString username, QString server)
{
    this->id=id;
    this->name=name;
    this->surname=surname;
    this->password=password;
    this->username=username;
    QString jid=username;
    jid+="@";
    jid+=server;
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

QString TerrainUser::getPassword(){
    return this->password;
}

QString TerrainUser::getUsername(){
    return this->username;
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

void TerrainUser::setPassword(QString password){
    this->password=password;
}

void TerrainUser::setUsername(QString username, QString server){
    this->username=username;
    QString jid=username;
    jid+="@";
    jid+=server;
    setJid(jid);
}

void TerrainUser::setJid(QString jid){
    this->jid=jid;
}
