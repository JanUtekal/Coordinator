#include "mapdataparser.h"

MapDataParser::MapDataParser(QObject *parent) :
    QObject(parent)
{
}

int MapDataParser::parseData(QString data, QVector<QPointF> &coordList){

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
                    node2=node.nextSibling();
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
