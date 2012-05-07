/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012

 */

#include "extension.h"
#include <QDebug>
#include <QDomElement>

//handles xep 0080 stanza with geolocation and provides coordinates to Controller
bool Extension::handleStanza (const QDomElement& stanza)
{
    QDomElement docElement =stanza;   // docElement now refers to the node "xml"
  //  Contact contact;
  //  contact.setJid(jid);
    QString latitude;
    QString longitude;
    QString accuracy;
    QString jid;
    bool geolocStanza=false;

    jid=docElement.attribute("from");
   // qDebug()<<docElement.attribute("from");


    QDomNodeList nodeList= docElement.firstChild().firstChild().firstChild().firstChild().childNodes();

    for(int j=0; j< nodeList.length();j++){
        QDomNode node=nodeList.at(j);

        QDomElement elem = node.toElement();

        if(elem.tagName()=="lat"){
            latitude=elem.text();
        }

        if(elem.tagName()=="lon"){
            longitude=elem.text();
        }

        if(elem.tagName()=="accuracy"){
            accuracy=elem.text();
        }


        geolocStanza=true;

      //  qDebug()<<elem.tagName()<<elem.text();
    }

    if(geolocStanza){
        if(latitude!="" && longitude!=""){
            qDebug()<<"SENDING COORDS"<<latitude<<longitude;
            emit sendCoords(jid.toLower(), latitude, longitude, accuracy);
        }
    }


 /*   for(int i=0; i< nodeList.length();i++){
        QDomNode node=nodeList.at(i);

        QDomElement elem = node.toElement();

        //qDebug()<<elem.tagName()<<elem.childNodes().length();

        QDomNode node2=elem.firstChild();

        QDomElement elem2 = node2.toElement();

     //   qDebug()<<elem2.tagName()<<elem2.childNodes().length();

        QDomNode node3=elem2.firstChild();

        QDomElement elem3 = node3.toElement();

   //     qDebug()<<elem3.tagName()<<elem3.childNodes().length();

        QDomNode node4=elem3.firstChild();

        QDomElement elem4 = node4.toElement();

      //  qDebug()<<elem4.tagName()<<elem4.childNodes().length();


        QDomNodeList nodeList2=   elem4.childNodes();


        for(int j=0; j< nodeList2.length();j++){
            QDomNode node5=nodeList2.at(j);

            QDomElement elem5 = node5.toElement();

            qDebug()<<elem5.tagName()<<elem5.text();
        }
    }*/
 /*   foreach(QDomNode node, docElement.firstChild().childNodes()){
        QDomElement elem = node.toElement();

        qDebug()<<elem.tagName();


    }*/


    return false;
}

//ads features to xmpp client
QStringList Extension::discoveryFeatures () const
{
    QStringList result;
    result << "http://jabber.org/protocol/geoloc";
    result << "http://jabber.org/protocol/pubsub";
    return result;
}
