#ifndef TERRAINUSER_H
#define TERRAINUSER_H
#include <QtCore>
#include <QDebug>
class TerrainUser
{
public:
    TerrainUser(QString id, QString name, QString surname, QString jid);
    void setId(QString id);
    void setName(QString name);
    void setSurname(QString surname);
    void setJid(QString jid);

    QString getId();
    QString getName();
    QString getSurname();
    QString getJid();

private:
    QString id;
    QString name;
    QString surname;
    QString jid;
};

#endif // TERRAINUSER_H
