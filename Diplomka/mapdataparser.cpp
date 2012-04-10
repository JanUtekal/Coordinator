#include "mapdataparser.h"

MapDataParser::MapDataParser(QObject *parent) :
    QObject(parent)
{
}

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

int MapDataParser::getDataType(QString data){
    int type=-1;

    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();

    if(docElement.nodeName()=="note"){
        type=0;
    } else if(docElement.nodeName()=="negativeObject") {
        type=1;
    } else {
        type=2;
    }
    return type;
}

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

QString MapDataParser::parseNegativeObjectData(QString data){
    QDomDocument doc( "myDocument" );
    doc.setContent( data );                        // myFile is a QFile

    QDomElement docElement = doc.documentElement();   // docElement now refers to the node "xml"

    return docElement.text();
}
