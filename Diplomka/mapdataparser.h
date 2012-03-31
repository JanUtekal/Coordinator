#ifndef MAPDATAPARSER_H
#define MAPDATAPARSER_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QtXml>
class MapDataParser : public QObject
{
    Q_OBJECT
public:
    explicit MapDataParser(QObject *parent = 0);
    int parseData(QString data,QVector<QPointF> &coordList);
    
signals:
    
public slots:
    
};

#endif // MAPDATAPARSER_H
