#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLandmarkManager>
#include <QLandmark>
#include <QLandmarkManagerEngine>
#include <qlandmarkmanager.h>
#include <qlandmark.h>
#include <QDebug>
#include <QLandmarkProximityFilter>
#include <QLandmarkIntersectionFilter>
#include <QSqlDatabase>
#include "dbconnection.h"
#include <QLandmarkNameFilter>
#include "acl.h"
#include "terrainuser.h"

QTM_USE_NAMESPACE

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void getRootObject(QObject *obj);
    void createDb(QSqlDatabase db);

    QLandmarkManager *landMan;
    QLandmark actualLandmark;
    QLandmark pom;
    Q_INVOKABLE void addPoint(double lat, double lon);
    Q_INVOKABLE void selectObject(double lat, double lon);
    Q_INVOKABLE void deselectObject();

    Q_INVOKABLE void deleteCurrentObject();


    Q_INVOKABLE void setSelectedMapObject(QVariant object);
    Q_INVOKABLE QVariant getSelectedMapObject();

    Q_INVOKABLE void testButtonOperation();
    Q_INVOKABLE void createNewTerrainUser(QString id, QString name, QString surname, QString jid, QString password);
    Q_INVOKABLE void createNewAcl(QString name);


    //aclList methods
    Q_INVOKABLE void prepareAclList();
    Q_INVOKABLE int getAclNum();
    Q_INVOKABLE QString getAclNameAt(int i);
    Q_INVOKABLE void removeAcl(int i);

    //terrainuserList methods
    Q_INVOKABLE void prepareTerrainUserList();
    Q_INVOKABLE int getTerrainUserNum();
    Q_INVOKABLE QString getTerrainUserNameAt(int i);
    Q_INVOKABLE QString getTerrainUserSurnameAt(int i);
    Q_INVOKABLE void removeTerrainUser(int i);

    //terrainuserFromAclList methods
    Q_INVOKABLE void prepareTerrainUserFromAclList(int i);
    Q_INVOKABLE int getTerrainUserFromAclNum();
    Q_INVOKABLE QString getTerrainUserFromAclNameAt(int i);
    Q_INVOKABLE QString getTerrainUserFromAclSurnameAt(int i);
    Q_INVOKABLE void setTerrainUserAcl(int i, int j);
    Q_INVOKABLE void unsetTerrainUserAcl(int i);

private:
    QObject *object;
    QVariant selectedMapObject;

    DbConnection *dbConnection;
    QList<Acl> aclList;
    QList<TerrainUser> terrainUserList;
    QList<TerrainUser> terrainUserFromAclList;

    void deselectCurrentObject();
    void fixMapBug();
    void sendMapObjects();




signals:
    void sendObjects(QList<QLandmark> *landmarks);
    void aclListReady();
    void terrainUserListReady();
    void terrainUserFromAclListReady();
    
public slots:
    void getAllObjects(QList<QLandmark> *dbLandmarks);
    void getConnectedUsers(QList<QLandmark> *userLandmarks);

    void updateUserPosition(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);
    
};

#endif // CONTROLLER_H
