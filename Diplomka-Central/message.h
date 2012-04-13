#ifndef MESSAGE_H
#define MESSAGE_H
#include <QtCore>

class Message
{
public:
    Message(QString text, QString time, bool received);
    QString getText();
    QString getTime();
    bool getReceived();

    void setText(QString text);
    void setTime(QString time);
    void setReceived(bool received);


private:
    QString text;
    QString time;
    bool received;

};

#endif // MESSAGE_H
