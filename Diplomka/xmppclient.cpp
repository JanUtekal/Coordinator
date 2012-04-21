/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012


 */


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

#include <iostream>

#include "QXmppMessage.h"
#include "QXmppRosterManager.h"

#include "xmppClient.h"
#include <QXmlStreamWriter>

#define PATH ""
//#define USERNAME "terrainuser1@jabber.cz"

//#define PASSWORD "asasasd"


//this class handles connection via xmpp protocol
XmppClient::XmppClient(QObject *parent)
    : QXmppClient(parent)
{
    bool check = connect(this, SIGNAL(connected()),
                         SLOT(clientConnected()));
    Q_ASSERT(check);


    /// Then QXmppRoster::presenceChanged() is emitted whenever presence of someone
    /// in roster changes
     check = connect(&this->rosterManager(),
                    SIGNAL(presenceChanged(QString,QString)),
        SLOT(presenceChanged(QString,QString)));

    Q_ASSERT(check);

       check = connect(this, SIGNAL(messageReceived(QXmppMessage)), SLOT(messageRecv(QXmppMessage)));

    Q_ASSERT(check);


       check = connect(this, SIGNAL(presenceReceived(QXmppPresence)), SLOT(presenceReceived(QXmppPresence)));

    Q_ASSERT(check);

       check = connect(this, SIGNAL(presenceReceived(QXmppPresence)), SLOT(presenceReceived(QXmppPresence)));

    Q_ASSERT(check);

  /*  connect(&timer,SIGNAL(timeout()),this,SLOT(timeToCheckPresence()));
    timer.setInterval(10000);
      timer.start();

    connect(&contactTimer,SIGNAL(timeout()),this,SLOT(timeToChangePresence()));
    contactTimer.setInterval(11000);
    contactTimer.start();*/
    //  QTimer::s:setInterval()
       deleted=0;

   //subscribeLocation();
}

XmppClient::~XmppClient()
{

}



void XmppClient::clientConnected()
{
    std::cout<<"CONNECTED"<<std::endl;
}


//handles change of presence for some user
void XmppClient::presenceChanged(const QString& bareJid,
                                 const QString& resource)
{
    qDebug()<<"presence changed"<<bareJid<<resource<<this->rosterManager().getPresence(bareJid,resource).type();
    if(this->rosterManager().getPresence(bareJid,resource).type()==QXmppPresence::Unavailable){
        emit setUserOffline(bareJid.toLower());
    }


}

//handles received message from some user
//parses the content of the message with mapdataparser and acts accordingly
void XmppClient::messageRecv(const QXmppMessage& message){
      //  qDebug()<<message.body();

        MapDataParser * parser=new MapDataParser();

        int dataType=parser->getDataType(message.body());

        if(dataType==0){

            Note note=parser->parseNoteData(message.body());
            emit sendNote(note);
            qDebug()<<"sending noote";

        }

        if(dataType==1){

            QString negativeObject=parser->parseNegativeObjectData(message.body());
            emit sendNegativeObject(negativeObject);
            qDebug()<<"sending negobj";

        }

        if(dataType==2){
            QString text=parser->parseMessageData(message.body());
            QString from=message.from().split("@").at(0);

            QDateTime t=QDateTime::currentDateTime();
            QString outputFormat="hh:mm:ss";
            QString time=   t.toString(outputFormat);

            Message m(text,from,time,true);

            emit sendReceivedMessage(m);
        }

        if(dataType==3){
            QVector<QPointF> coords;
            QString mapObjectId;


            int type=parser->parseSVGData(message.body(),mapObjectId,coords);

            if(type==-1){
                return;
            }
            if(type==0){
                emit sendPointFromCentral(coords, mapObjectId, message.body());
            }
            if(type==1){
                emit sendLineFromCentral(coords, mapObjectId, message.body());
            }

            if(type==2){
                emit sendPolygonFromCentral(coords, mapObjectId, message.body());
            }
        }

        delete parser;
  /*  if(message.body().contains("POINT")){
        qDebug()<<message.body();
       // emit sendPointFromCentral(message.body());
    } else if(message.body().contains("LINESTRING")) {
        QString coords=message.body().remove(0,11);//=location.split("LINESTRING(").
        coords.chop(1);
     //   emit sendLineFromCentral(coords);
    } else {

    }*/
}

//handles received presence
void XmppClient::presenceReceived(const QXmppPresence &presence){
    qDebug()<<"presence rcvd"<<presence.from()<<presence.type();
    if(presence.type()==4){//subscribed
        subscribeLocation(presence.from());

    }
}

//deprecated - experimantalni metoda
void XmppClient::sendMess(float lat, float lon){

    QXmppIq iq;

    iq.setFrom(this->configuration().jid());
    iq.setType(QXmppIq::Set);
    iq.setId("publish1111");
   // iq.setTo("asasasd@jabber.cz");

    QXmppElement pubsub;
    pubsub.setTagName("pubsub");
    pubsub.setAttribute("xmlns","http://jabber.org/protocol/pubsub");

    QXmppElement publish;
    publish.setTagName("publish");
    publish.setAttribute("node","http://jabber.org/protocol/geoloc");

    pubsub.appendChild(publish);

    QXmppElement elItem;
    elItem.setTagName("item");
    publish.appendChild(elItem);

    QXmppElement elGeoloc;
    elGeoloc.setTagName("geoloc");
    elGeoloc.setAttribute("xmlns","http://jabber.org/protocol/geoloc");
    elGeoloc.setAttribute("xml:lang","en");
    elItem.appendChild(elGeoloc);

    QXmppElement elLat;
    elLat.setTagName("lat");
    QString slat;
    slat.setNum(lat);
    elLat.setValue(slat);
    elGeoloc.appendChild(elLat);

    QXmppElement elLon;
    elLon.setTagName("lon");
    QString slon;
    slon.setNum(lon);
    //  qDebug()<<"IIIIIIIIIIIIIIIIIII"<<lon<<slon;
    elLon.setValue(slon);
    elGeoloc.appendChild(elLon);

    QXmppElement elAlt;
    elAlt.setTagName("alt");
    elAlt.setValue("nan");
    elGeoloc.appendChild(elAlt);

    QXmppElement elAccuracy;
    elAccuracy.setTagName("accuracy");
    elAccuracy.setValue("1880.590000");
    elGeoloc.appendChild(elAccuracy);


    QXmppElementList elList;
    elList.append(pubsub);


    iq.setExtensions(elList);
    //   mess.setType(QXmppMessage::Normal);
    // sendMessage("asasasd@jabber.cz","bla");
    sendPacket(iq);



}

//deprecated - promaze log soubor
void XmppClient::eraseFile(){
    QString path=PATH;
    path+="QXmppClientLog.log";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<< "";
    file.close();
}

//gets new coordinates of some user received via extension
void XmppClient::getNewCoords(QString jid, QString lat, QString lon, QString acc){
  qDebug()<<jid<<lat<<lon<<acc;

    QGeoCoordinate coordinate(lat.toDouble(), lon.toDouble());

    emit updateUser(jid,coordinate);
}

//subscribes to all users to receive their geolocation
void XmppClient::subscribeLocation(QString jid){

    QStringList l=this->rosterManager().getRosterBareJids();

    foreach(QString jid, l){

        QXmppPubSubIq iq;
        iq.setTo(jid);
        QString userName=this->configuration().jidBare();
        userName+="/QXmpp";

        iq.setFrom(userName);
        iq.setType(QXmppIq::Set);
        iq.setQueryType(QXmppPubSubIq::SubscribeQuery);
        iq.setQueryJid("asasasd@jabber.cz/QXmpp");
        iq.setQueryNode("http://jabber.org/protocol/geoloc");
     //   iq.setItems(items);
        this->sendPacket (iq);


    }

}

//send message from current user to central user
void XmppClient::getMessageToSend(QString jid, QString message){

    this->sendMessage(jid,message);
}

//reconnects with provided username and password
void XmppClient::reconnectGet(QString username, QString password){
    this->disconnectFromServer();
    QXmppConfiguration config;
    config.setJid(username);
    config.setPassword(password);
    config.setAutoAcceptSubscriptions(true);
    config.setIgnoreSslErrors(true);

   // QXmppPresence pr;
   // pr.setCapabilityNode("http://jabber.org/protocol/geoloc");
   // client.addProperCapability(pr);
  //  QXmppDiscoveryManager d;
   // d.setClientCapabilitiesNode("http://jabber.org/protocol/geoloc");

    this->connectToServer(config);
}
