#include "note.h"

Note::Note(QString name, QString text, QString id)
{
    this->name=name;
    this->text=text;
    this->id=id;
}

QString Note::getId(){
    return this->id;
}

QString Note::getName(){
    return this->name;
}

QString Note::getText(){
    return this->text;
}

void Note::setId(QString id){
    this->id=id;
}

void Note::setName(QString name){
    this->name=name;
}

void Note::setText(QString text){
    this->text=text;
}
