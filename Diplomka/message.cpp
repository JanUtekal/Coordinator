#include "message.h"

Message::Message(QString text, QString from, QString time, bool received)
{
    this->text=text;
    this->from=from;
    this->time=time;
    this->received=received;
}

QString Message::getText(){
    return this->text;
}

QString Message::getTime(){
    return this->time;
}

QString Message::getFrom(){
    return this->from;
}

bool Message::getReceived(){
    return this->received;
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

void Message::setFrom(QString from){
    this->from=from;
}
