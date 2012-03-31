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

#define USERNAME "centraluser1@jabber.cz"

#define PASSWORD "asasasd"


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

   /*    check = connect(this, SIGNAL(stateChanged(State)), SLOT(userStateChanged(State)));

    Q_ASSERT(check);*/

  /*  connect(&timer,SIGNAL(timeout()),this,SLOT(timeToCheckPresence()));
    timer.setInterval(10000);
      timer.start();

    connect(&contactTimer,SIGNAL(timeout()),this,SLOT(timeToChangePresence()));
    contactTimer.setInterval(11000);
    contactTimer.start();*/
    //  QTimer::s:setInterval()
       deleted=0;


}

XmppClient::~XmppClient()
{

}

void XmppClient::clientConnected()
{
    std::cout<<"CONNECTED"<<std::endl;
}


void XmppClient::presenceChanged(const QString& bareJid,
                                 const QString& resource)
{


    qDebug()<<"presence changed"<<bareJid<<resource<<this->rosterManager().getPresence(bareJid,resource).type();
    if(this->rosterManager().getPresence(bareJid,resource).type()==QXmppPresence::Unavailable){
        emit setUserOffline(bareJid.toLower());
    }


   // notifyChange();

 /*   for(int i=0;i<cList.length();i++){
        Contact c=cList.at(i);
        qDebug()<<"presence"<<c.getJid();
    }*/
    //checkPresence();

}

void XmppClient::messageRecv(const QXmppMessage& message){
    //todo
 //   qDebug()<<"msgget"<<message.body()<<message.from()<<message.extensions().length();
  //getGeoLoc();
}

void XmppClient::presenceReceived(const QXmppPresence &presence){
   // qDebug()<<"presence"<<presence.from();

}


void XmppClient::sendObjectsToUsers(QList<QLandmark> *landmarks){

    QStringList l=this->rosterManager().getRosterBareJids();


    foreach(QLandmark lm, *landmarks){

        QString message=QString("POINT(%1 %2)").arg(lm.coordinate().latitude()).arg(lm.coordinate().longitude());

        foreach(QString s, l){
            QXmppClient::sendMessage("h.a.n.s@jabber.cz/QXmpp",message);

        }
       // foreach(Contact c, cList){


          //  qDebug()<<c.getJid();
          //

    //    }


    }
  //  sendMess();

}

void XmppClient::sendObjectToUsers(QString svg, QList<TerrainUser> userList){


    foreach(TerrainUser user, userList){
        /*QString message;
        if(landmark.phoneNumber().toInt()<10){
            message=QString("POINT(%1 %2)").arg(landmark.coordinate().latitude()).arg(landmark.coordinate().longitude());
        } else {
            message="LINESTRING(";
            message+=landmark.description();
            message+=")";
        }*/

        QXmppClient::sendMessage(user.getJid(),svg);


    }
  //qDebug()<<svg;
}

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


void XmppClient::iqReceived(const QXmppIq &iq){
  //  qDebug()<<"iqrecv"<<iq.type()<<iq.from();
}


void XmppClient::sendMess(){

  /*  QXmppIq iq;

    iq.setType(QXmppIq::Set);
    iq.setId("update");

    QXmppElement query;
    query.setTagName("query");
    query.setAttribute("xmlns","jabber:iq:private");

    QXmppElement subscriptions;
    subscriptions.setTagName("subscriptions");
    subscriptions.setAttribute("xmlns","storage:pubsubs");
    query.appendChild(subscriptions);

    QXmppElement subscription;
    subscription.setTagName("subscription");
    subscription.setAttribute("user","H.a.n.s@jabber.cz");
    subscription.setAttribute("jid","pubsub.jabber.cz");
    subscription.setAttribute("node","H.a.n.s/geoloc");
    subscription.setAttribute("targetns","http://jabber.org/protocol/geoloc+notify");
    subscription.setAttribute("subscription","subscribed");
    subscriptions.appendChild(subscription);





    QXmppElementList elList;
    elList.append(query);


    iq.setExtensions(elList);
    //sendPacket(iq);*/
  /*  QXmppIq iq;

        iq.setType(QXmppIq::Get);
        iq.setId("retrieve1");

        QXmppElement query;
        query.setTagName("query");
        query.setAttribute("xmlns","jabber:iq:private");

        QXmppElement subscriptions;
        subscriptions.setTagName("subscriptions");
        subscriptions.setAttribute("xmlns","storage:pubsubs");
        query.appendChild(subscriptions);



        QXmppElementList elList;
        elList.append(query);


*/
/*

QXmppIq iq2;
    iq2.setType(QXmppIq::Get);
    iq2.setId("nodes1");
    iq2.setFrom("asasasd@jabber.cz");
    iq2.setTo("asasasd@jabber.cz/QXmpp");

    QXmppElement query2;
    query2.setTagName("query");
    query2.setAttribute("xmlns","http://jabber.org/protocol/disco#info");






    QXmppElementList elList2;
    elList2.append(query2);

*/
/*
    QXmppPresence iq2;

        iq2.setFrom("asasasd@jabber.cz/QXmpp");


        QXmppElement c;
        c.setTagName("c");
        c.setAttribute("xmlns","http://jabber.org/protocol/caps");
        c.setAttribute("hash","sha-1");

        c.setAttribute("node","http://www.chatopus.com");
        c.setAttribute("ver","zHyEOgxTrkpSdGcQKH8EFPLsriY=");



        QXmppElementList elList2;
        elList2.append(c);
*/

/*
            QXmppIq iq2;
                iq2.setType(QXmppIq::Set);
                iq2.setId("bla");
            //    iq2.setFrom("asasasd@jabber.cz");
                iq2.setTo("pubsub.jabber.cz");

                QXmppElement query2;
                query2.setTagName("query");
                query2.setAttribute("xmlns","http://jabber.org/protocol/geoloc+notify");


                QXmppElement activate;
                activate.setTagName("activate");
                activate.setValue("asasasd@jabber.cz/QXmpp");

                query2.appendChild(activate);




                QXmppElementList elList2;
                elList2.append(query2);*/
   /* QXmppIq iq;
        iq.setType(QXmppIq::Set);
        iq.setId("abc");
        iq.setFrom("asasasd@jabber.cz/QXmpp");
        iq.setTo("notify.jabber.cz");

        QXmppElement pubsub;
        pubsub.setTagName("pubsub");
        pubsub.setAttribute("xmlns","http://jabber.org/protocol/pubsub");



        QXmppElement subscribe;
        subscribe.setTagName("subscribe");
        subscribe.setAttribute("node","geoloc");
     //   subscribe.setAttribute("jid","H.a.n.s@jabber.cz");
        pubsub.appendChild(subscribe);



        QXmppElementList elList;
        elList.append(pubsub);*/

    //   mess.setType(QXmppMessage::Normal);
    // sendMessage("asasasd@jabber.cz","bla");
//   iq2.setExtensions(elList2);
//   sendPacket(iq2);
/*
    QXmppPubSubIq iq;
    iq.setTo("H.a.n.s@jabber.cz");
    iq.setType(QXmppIq::Get);
    iq.setQueryType(QXmppPubSubIq::ItemsQuery);
    iq.setQueryNode("http://jabber.org/protocol/geoloc");
    qDebug()<< this->sendPacket(iq);
*/

/*    QXmppElement item;
    item.setTagName ("item");
    item.setAttribute ("id", "blabla");

    QXmppElement items;
    items.setTagName ("items");
    items.setAttribute ("node", "http://jabber.org/protocol/geoloc");
    items.appendChild (item);

    QXmppElement pubsub;
    pubsub.setTagName ("pubsub");
    pubsub.setAttribute ("xmlns", "http://jabber.org/protocol/pubsub");
    pubsub.appendChild (items);

    QXmppIq iq (QXmppIq::Get);
    iq.setTo ("H.a.n.s@jabber.cz");
    iq.setExtensions (pubsub);
    this->sendPacket (iq);

*/

    QXmppPubSubIq iq;
    iq.setTo("terrainuser1@jabber.cz/");
    iq.setFrom("centraluser1@jabber.cz/QXmpp");
    iq.setType(QXmppIq::Set);
    iq.setQueryType(QXmppPubSubIq::SubscribeQuery);
    iq.setQueryJid("terrainuser1@jabber.cz/QXmpp");
    iq.setQueryNode("http://jabber.org/protocol/geoloc");
 //   iq.setItems(items);
    this->sendPacket (iq);

    qDebug()<<"sent";

 // QXmppDiscoveryManager m;
  //qDebug()<< m.requestInfo("H.a.n.s@jabber.cz","geoloc");





}

void XmppClient::getNewCoords(QString jid, QString lat, QString lon, QString acc){
  //qDebug()<<jid<<lat<<lon<<acc;

    QGeoCoordinate coordinate(lat.toDouble(), lon.toDouble());

    emit updateUser(jid.toLower(),coordinate);
}

void XmppClient::subscribeLocation(){

    QStringList l=this->rosterManager().getRosterBareJids();

    foreach(QString jid, l){

        QXmppPubSubIq iq;
        iq.setTo(jid);
        QString userName=USERNAME;
        userName+="/QXmpp";

        iq.setFrom(userName);
        iq.setType(QXmppIq::Set);
        iq.setQueryType(QXmppPubSubIq::SubscribeQuery);
        iq.setQueryJid("terrainuser@jabber.cz/QXmpp");
        iq.setQueryNode("http://jabber.org/protocol/geoloc");
     //   iq.setItems(items);
        this->sendPacket (iq);


    }

}


