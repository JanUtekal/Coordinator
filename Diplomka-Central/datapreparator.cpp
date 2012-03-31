#include "datapreparator.h"

DataPreparator::DataPreparator(QObject *parent) :
    QObject(parent)
{
}

QString DataPreparator::prepareData(QVector<QPointF> coordList, int type){
    //![configure SVG generator]
        QString name="object.svg";

        QSvgGenerator generator;

     //   generator.setSize(QSize(200, 200));
     //   generator.setViewBox(QRect(0, 0, 200, 200));
        QString typeName;
        generator.setFileName(name);
        switch ( type ) {
          case 0 :{

            typeName="POINT";

        }
            break;

          case 1 :
            typeName="LINE";

            break;

          case 2 :
            typeName="POLYGON";
            break;

          default :
            ;
        }
        generator.setTitle(typeName);

        generator.setDescription(tr(""));
        QPainter painter;
        painter.begin(&generator);

    //    painter.setPen(Qt::NoPen);


      //  points.append(QPointF(10.5, 5.33));
     //   points.append(QPointF(50.5, 25.33));
                //points.append(QPoint(50.5, 25.33));


        switch ( type ) {
          case 0 :{
//qDebug()<<coordList.at(0).x();
//qDebug()<<coordList.at(0).y();
            coordList.append(QPointF(coordList.at(0).x()+0.1,coordList.at(0).y()));
            painter.drawPolyline(coordList);
           // coordList.append(coordList.at(0));
          //  painter.drawPolyline(coordList);
        }
            break;

          case 1 :

            painter.drawPolyline(coordList);
            break;

          case 2 :

            break;

          default :
            ;
        }


        painter.end();

        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"error reading svg file";
        }

        QByteArray content;
        while (!file.atEnd()) {
            content+= file.readLine();

        }
        file.close();
        file.remove();

        qDebug()<<content;

        return QString(content);
}
