#ifndef TERRAINUSER_H
#define TERRAINUSER_H
#include <QtCore>
#include <QDebug>
class TerrainUser
{
public:
    TerrainUser(QString id, QString name, QString surname, QString password, QString username, QString server);

    void setId(QString id);
    void setName(QString name);
    void setSurname(QString surname);
    void setPassword(QString password);
    void setUsername(QString username, QString server);
    void setJid(QString jid);

    QString getId();
    QString getName();
    QString getSurname();
    QString getPassword();
    QString getUsername();
    QString getJid();

private:
    QString id;
    QString name;
    QString surname;
    QString password;
    QString username;
    QString jid;
};

#endif // TERRAINUSER_H
