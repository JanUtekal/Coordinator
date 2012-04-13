#ifndef MESSAGE_H
#define MESSAGE_H
#include <QtCore>

class Message
{
public:
    Message(QString text, QString from, QString time, bool received);
    QString getText();
    QString getTime();
    QString getFrom();
    bool getReceived();

    void setText(QString text);
    void setTime(QString time);
    void setFrom(QString from);
    void setReceived(bool received);


private:
    QString text;
    QString time;
    QString from;
    bool received;

};

#endif // MESSAGE_H
