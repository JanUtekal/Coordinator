#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QVariant>

class MapObject
{

public:
    explicit MapObject();

    void setPaintedObject(QVariant object);
    void setType(int type);
    void setName(QString name);

    QVariant getPaintedObject();
    int getType();
    QString getName();

private:
    QVariant paintedObject;
    int type;
    QString name;
    
signals:
    
public slots:
    
};

#endif // MAPOBJECT_H
