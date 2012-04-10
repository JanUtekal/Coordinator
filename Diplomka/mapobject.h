#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QPointF>

class MapObject
{

public:
    explicit MapObject();

    void setPaintedObject(QVariant object);
    void setType(int type);
    void setName(QString name);
    void setGeometry(QVector<QPointF> geometry);

    QVariant getPaintedObject();
    int getType();
    QString getName();
    QVector<QPointF> getGeometry();


private:
    QVariant paintedObject;
    int type;
    QString name;
    QVector<QPointF> geometry;
signals:

public slots:

};

#endif // MAPOBJECT_H
