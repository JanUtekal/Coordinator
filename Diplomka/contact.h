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
    QString jid;
    QString lat;
    QString lon;
    QString stamp;
  //  bool isPresent;


};

#endif // CONTACT_H
