#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCore>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QLandmark>
#include "acl.h"
#include "terrainuser.h"

QTM_USE_NAMESPACE

class DbConnection : public QObject
{
    Q_OBJECT
public:
    explicit DbConnection(QObject *parent = 0);
    void setDb(QSqlDatabase db);

    int insertPoint(double lat, double lon);
    int deletePoint(QString id);
    void getObjectsFromDB();
    QString getLastObjectIdFor(QString jid);
    QList<QLandmark> getMapObjectsNotSentFor(QString jid);
    void updateUserTerrainLastObject(QString jid, QString id);
    void insertTerrainUser(QString id, QString name, QString surname, QString jid, QString password);
    void insertAcl(QString name, QString currentCentralUser);
    QList<Acl> getAllAcls();
    QList<TerrainUser> getAllTerrainUsers();
    QList<TerrainUser> getTerrainUsersFromAcl(QString id);
    void updateUserTerrainAcl(QString idUser, QString idAcl);
    void deleteAcl(QString id);
    void deleteTerrainUser(QString id);

private:
    QSqlDatabase db;

signals:
    void sendAllObjects(QList<QLandmark> *dbLandmarks);
    
public slots:
    
};

#endif // DBCONNECTION_H
