#ifndef DATAPREPARATOR_H
#define DATAPREPARATOR_H

#include <QObject>
#include <QSvgGenerator>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QStaticText>
class DataPreparator : public QObject
{
    Q_OBJECT
public:
    explicit DataPreparator(QObject *parent = 0);
    QString prepareData(QVector<QPointF> coordList, QString id, int type);
    
signals:
    
public slots:
    
};

#endif // DATAPREPARATOR_H
