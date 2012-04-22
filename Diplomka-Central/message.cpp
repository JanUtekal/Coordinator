#include "message.h"

Message::Message(QString text, QString time, bool received)
{
    this->text=text;
    this->time=time;
    this->received=received;
}

QString Message::getText(){
    return this->text;
}

QString Message::getTime(){
    return this->time;
}

bool Message::getReceived(){
    return this->received;
}

QString Message::getCentralUser(){
    return this->centralUser;
}

void Message::setReceived(bool received){
    this->received=received;
}

void Message::setText(QString text){
    this->text=text;
}

void Message::setTime(QString time){
    this->time=time;
}

void Message::setCentralUser(QString centralUser){
    this->centralUser=centralUser;
}
