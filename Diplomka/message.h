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
    QString text; //text of a message
    QString time; // time the message was received
    QString from; // jid of sender
    bool received; // true if the message was received, false ifit was send

};

#endif // MESSAGE_H
