#ifndef NOTE_H
#define NOTE_H

#include <QtCore>
#include <QDebug>

class Note
{
public:
    Note();
    Note(QString name, QString text, QString id);
    QString getName();
    QString getText();
    QString getId();

    void setName(QString name);
    void setText(QString text);
    void setId(QString id);

private:
    QString name; // name of the note
    QString text; // text of the note
    QString id; // id from central db of mapobject the note belongs to

};

#endif // NOTE_H
