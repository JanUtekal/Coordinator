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
#include "contact.h"
#include <QLandmark>
#include <QXmppDiscoveryManager.h>
#include <QXmppPubSubIq.h>
#include "mapdataparser.h"
#include "message.h"
#include <QDateTime>

QTM_USE_NAMESPACE

class XmppClient : public QXmppClient
{
    Q_OBJECT

public:
    XmppClient(QObject *parent = 0);
    ~XmppClient();

    void sendMess(float lat, float lon);
    QList<Contact> cList;

private:

    int deleted;

    void eraseFile();



signals:
    void refresh();
    void sendPointFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void sendLineFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void sendPolygonFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void sendNote(Note note);
    void sendNegativeObject(QString negativeObject);

    void updateUser(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);
    void sendReceivedMessage(Message message);

public slots:
    void clientConnected();
    void messageRecv(const QXmppMessage& message);
    void presenceChanged(const QString& bareJid, const QString& resource);
    void presenceReceived(const QXmppPresence &presence);
    void getNewCoords(QString jid, QString lat, QString lon, QString acc);
    void subscribeLocation(QString jid);
    void getMessageToSend(QString jid, QString message);
    void reconnectGet(QString username, QString password);
};

#endif // XMPPCLIENT_H
