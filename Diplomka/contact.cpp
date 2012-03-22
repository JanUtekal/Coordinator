#include "contact.h"

Contact::Contact()
{
    //this->isPresent=true;

  /*  connect(&timer,SIGNAL(timeout()),this,SLOT(timeToChangePresence()));
    timer.setInterval(8000);
    timer.start();*/
}

void Contact::setJid(QString jid){
   this->jid=jid;
}

void Contact::setLat(QString lat){
    this->lat=lat;
}

void Contact::setLon(QString lon){
    this->lon=lon;
}

void Contact::setStamp(QString stamp){
    this->stamp=stamp;
}

QString Contact::getJid(){
    return this->jid;
}

QString Contact::getLat(){
    return this->lat;
}

QString Contact::getLon(){
    return this->lon;
}

QString Contact::getStamp(){
    return this->stamp;
}
/*
void Contact::setPresence(bool presence){
    this->isPresent=presence;
}

bool Contact::getPresence(){
    return this->isPresent;
}*/


