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
    QString getCentralUser();

    void setText(QString text);
    void setTime(QString time);
    void setReceived(bool received);
    void setCentralUser(QString centralUser);

private:
    QString text;
    QString time;
    bool received;
    QString centralUser;

};

#endif // MESSAGE_H
