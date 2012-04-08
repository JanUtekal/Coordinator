/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
 *	Manjeet Dahiya
 *
 * Source:
 *	http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include "QXmppClient.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
//#include "contact.h"
#include <QLandmark>
#include <QXmppDiscoveryManager.h>
#include <QXmppPubSubIq.h>
#include "terrainuser.h"
#include <QtXml>
#include "note.h"
QTM_USE_NAMESPACE

class XmppClient : public QXmppClient
{
    Q_OBJECT

public:
    XmppClient(QObject *parent = 0);
    ~XmppClient();

    void unregister();
    void startSubscribingToUsers(QStringList jidList);


  //  QList<Contact> cList;

private:

    int deleted;
    bool unregisterMe;
    bool subscribe;

    void eraseFile();
    void unregisterUser();
    void subscribeToUsers();
    void publishFirstLocation();
    QStringList jidList;

signals:
    void refresh(QList<QLandmark> *landmarkList);
    void updateUser(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);

public slots:

    void clientConnected();
    void messageRecv(const QXmppMessage& message);
    void presenceChanged(const QString& bareJid, const QString& resource);
    void presenceReceived(const QXmppPresence &presence);
    void iqReceived(const QXmppIq& iq);

    void sendObjectsToUsers(QList<QLandmark> *landmarks);
    void sendObjectToUsers(QString svg, QList<TerrainUser> userList);
    void sendNoteToUsers(Note note, QList<TerrainUser> userList);

    void getNewCoords(QString jid, QString lat, QString lon, QString acc);
    void subscribeLocation(QString jid);

    void subscribeToUser(QString jid);

  //  void userStateChanged(QXmppClient::State state);

    void sendMess();


};

#endif // XMPPCLIENT_H
