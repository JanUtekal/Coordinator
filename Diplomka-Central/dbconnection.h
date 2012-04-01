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
    int deleteObject(QString id);

    int insertLine(QVector<QPointF> lineVector);
    int insertPolygon(QVector<QPointF> polygonVector);

    void getObjectsFromDB();
    QString getLastObjectIdFor(QString jid);
    QList<QLandmark> getMapObjectsNotSentFor(QString jid);
    void updateTerrainUserLastObject(QString jid, QString id);
    void insertTerrainUser(QString id, QString name, QString surname, QString jid, QString password);
    void insertAcl(QString name, QString currentCentralUser);
    QList<Acl> getAllAcls();
    QList<TerrainUser> getAllTerrainUsers();
    QList<TerrainUser> getTerrainUsersFromAcl(QString id);
    void updateTerrainUserAcl(QString idUser, QString idAcl);
    void deleteAcl(QString id);
    void deleteTerrainUser(QString id);
    QString getPolygonIdAtCoordinates(double lat, double lon);

private:
    QSqlDatabase db;

signals:
    void sendAllPoints(QList<QLandmark> *dbLandmarks);
    void sendAllLines(QList<QLandmark> *dbLandmarks2);
    void sendAllPolygons(QList<QLandmark> *dbLandmarks3);

public slots:
    
};

#endif // DBCONNECTION_H
