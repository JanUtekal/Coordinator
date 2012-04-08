#ifndef NOTE_H
#define NOTE_H

#include <QtCore>
#include <QDebug>

class Note
{
public:
    Note(QString name, QString text, QString id);
    QString getName();
    QString getText();
    QString getId();

    void setName(QString name);
    void setText(QString text);
    void setId(QString id);

private:
    QString name;
    QString text;
    QString id;

};

#endif // NOTE_H
