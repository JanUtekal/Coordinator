/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012

 */

#include "mapdataparser.h"

//class used for parsing xml data received via xmpp protocol from central
MapDataParser::MapDataParser(QObject *parent) :
    QObject(parent)
{
}

//parses svg data received from central. Returns type of data eg. point/line/poly
//data represents SVG encoded graphics data, mapobject id is returned id of mapobject from central database, coordlist is returned list of mapobject coordinates
int MapDataParser::parseSVGData(QString data, QString &mapObjectId, QVector<QPointF> &coordList){

    int type=-1;


    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();   // docElement now refers to the node "xml"

    QDomNode node = docElement.firstChild();
  //  qDebug()<<node.isNull();
    while( !node.isNull() )
    {

        QDomElement el = node.toElement();
       // qDebug()<<el.nodeName();
        if(el.nodeName()=="title"){
            if(el.text()=="POINT"){
                type=0;
            }
            if(el.text()=="LINE"){
                type=1;
            }
            if(el.text()=="POLYGON"){
                type=2;
            }

        }


       // qDebug()<<el.nodeName();
        if(el.nodeName()=="desc"){
            mapObjectId=el.text();

        }


        if(el.nodeName()=="g"){
            if(node.hasChildNodes()){
                QDomNode node2=el.firstChild();

                while( !node2.isNull() )
                {
                    QDomElement el2 = node2.toElement();

                    if(type==0 && el2.nodeName()=="polyline"){
                        QStringList list=el2.attribute("points").trimmed().split(" ");

                        QStringList c=list.at(0).split(",");
                        QPointF point(c.at(0).toDouble(), c.at(1).toDouble());
                        coordList.append(point);


                    }
                    if(type==1 && el2.nodeName()=="polyline"){

                        QStringList list=el2.attribute("points").trimmed().split(" ");


                        foreach(QString coord, list){
                            QStringList c=coord.split(",");
                            QPointF point(c.at(0).toDouble(), c.at(1).toDouble());
                            coordList.append(point);

                        }
                    }

                    if(type==2 && el2.nodeName()=="path"){
                        QString path=el2.attribute("d");
                        path.remove("M");
                        path.remove("L");

                        QStringList list=path.trimmed().split(" ");

                        qDebug()<<"POLYLENJ"<<list.length();
                        foreach(QString coord, list){
                            QStringList c=coord.split(",");
                            QPointF point(c.at(0).toDouble(), c.at(1).toDouble());
                            coordList.append(point);

                        }
                        qDebug()<< coordList.size();

                    }
                    node2=node2.nextSibling();//!!!!!!!
                }

            }
        }
        //qDebug()<<el.text();
      /*
*/

      node = node.nextSibling();
    }




    return type;
}


// returns type of data - note, negobject, message, mapobject
int MapDataParser::getDataType(QString data){
    int type=-1;

    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();

    if(docElement.nodeName()=="note"){
        type=0;
    } else if(docElement.nodeName()=="negativeObject") {
        type=1;
    } else if(docElement.nodeName()=="mess"){
        type=2;
    } else {
        type=3;
    }
    return type;
}

//parses note data and returns corresponding note object
Note MapDataParser::parseNoteData(QString data){

    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();   // docElement now refers to the node "xml"

    QDomNode node = docElement.firstChild();

    Note note;
    note.setId(docElement.attribute("mapObjectId"));
   // note.setId();
  //  qDebug()<<node.isNull();
    while( !node.isNull() )
    {

        QDomElement el = node.toElement();

        if(el.nodeName()=="name"){
            note.setName(el.text());
        }
        if(el.nodeName()=="text"){
            note.setText(el.text());
        }

        node = node.nextSibling();
    }

    return note;
}

//returns id of object which was deleted or invalidated at central
QString MapDataParser::parseNegativeObjectData(QString data){
    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();   // docElement now refers to the node "xml"

    return docElement.text();
}

QVector<QPointF> MapDataParser::parseGeometry(QString coords){

    QStringList coordList=coords.split(",");
    QVector<QPointF> vector;

    foreach(QString coord, coordList){
        QStringList c=coord.split(" ");
        QPointF point(c.at(0).toDouble(), c.at(1).toDouble());
        vector.append(point);

    }

    return vector;
}

//returns parsed message text
QString MapDataParser::parseMessageData(QString data){
    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();   // docElement now refers to the node "xml"

    return docElement.text();
}
