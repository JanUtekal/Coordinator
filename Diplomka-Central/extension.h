#ifndef EXTENSION_H
#define EXTENSION_H
#include <QXmppClientExtension.h>
#include <QXmppMessage.h>
#include <QXmppPresence.h>

class Extension : public QXmppClientExtension
{
    Q_OBJECT

public:
   // Extension();
    QStringList discoveryFeatures () const;
    bool handleStanza (const QDomElement&);

signals:
    void sendCoords(QString jid, QString lat, QString lon, QString acc);

};



#endif // EXTENSION_H
