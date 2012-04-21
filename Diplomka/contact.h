#ifndef CONTACT_H
#define CONTACT_H
#include <QtCore>
#include <QDebug>

class Contact
{
public:
    Contact();
    QString getJid();
    QString getLat();
    QString getLon();
    QString getStamp();
 //   bool getPresence();

    void setJid(QString jid);
    void setLat(QString lat);
    void setLon(QString lon);
    void setStamp(QString stamp);
  //  void setPresence(bool presence);

private:
    QString jid; //user name for user used by xmpp protocol
    QString lat; // latitude coordinate of a user
    QString lon; // longitude coordinate of a user
    QString stamp; // timestamp of last time received coordinate
  //  bool isPresent;


};

#endif // CONTACT_H
