#ifndef MAPDATAPARSER_H
#define MAPDATAPARSER_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QtXml>
#include "note.h"
class MapDataParser : public QObject
{
    Q_OBJECT
public:
    explicit MapDataParser(QObject *parent = 0);
    int getDataType(QString data);
    int parseSVGData(QString data, QString &mapObjectId, QVector<QPointF> &coordList);
    QString parseNegativeObjectData(QString data);
    Note parseNoteData(QString data);
    QVector<QPointF> parseGeometry(QString coords);

    
signals:
    
public slots:
    
};

#endif // MAPDATAPARSER_H
