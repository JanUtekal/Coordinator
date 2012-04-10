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

    int insertPoint(double lat, double lon, QString acl);
    int deleteObject(QString id);

    int insertLine(QVector<QPointF> lineVector, QString acl);
    int insertPolygon(QVector<QPointF> polygonVector, QString acl);

    QString insertOrUpdateNote(QString mapObjectId, QString name, QString text);
    QString insertNote(QString mapObjectId, QString name, QString text);
    QString updateNote(QString noteId, QString name, QString text);

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
    int deleteNote(QString id);
    QString getPolygonIdAtCoordinates(double lat, double lon);
    QString getLineIdAtCoordinates(double lat, double lon);
    QString getPointIdAtCoordinates(double lat, double lon);
    QStringList getAllJids();
    QPair<QString, QString> getNoteForMapObject(QString id);
    QString getMapObjectAcl(QString mapObjectId);



private:
    QSqlDatabase db;

signals:
    void sendAllPoints(QList<QLandmark> *dbLandmarks);
    void sendAllLines(QList<QLandmark> *dbLandmarks2);
    void sendAllPolygons(QList<QLandmark> *dbLandmarks3);

public slots:
    
};

#endif // DBCONNECTION_H
