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
    void setAclId(QString aclId);

    QVariant getPaintedObject();
    int getType();
    QString getName();
    QString getAClId();

    void setGeometry(QVector<QPointF> geometry);

    QVector<QPointF> getGeometry();

private:
    QVariant paintedObject;
    int type;
    QString name;
    QString aclId;
    QVector<QPointF> geometry;
    
signals:
    
public slots:
    
};

#endif // MAPOBJECT_H
