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

#include "datapreparator.h"
#include "mapobject.h"
#include "jabberregistrationtool.h"
#include "xmppclient.h"
#include "note.h"

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
    Q_INVOKABLE void addPoint(double lat, double lon, int selectedAcl);
    Q_INVOKABLE void addLinePoint(double lat, double lon);
    Q_INVOKABLE void lineReady(int selectedAcl);
    Q_INVOKABLE void addPolygonPoint(double lat, double lon);
    Q_INVOKABLE void polygonReady(int selectedAcl);
    Q_INVOKABLE void createMapObjectReference(QVariant paintedObject, QString name, int type);

    Q_INVOKABLE void addNoteTo(QString name, QString text, QString id);

    Q_INVOKABLE void selectObject(QString name);
    Q_INVOKABLE void deselectObject();

    Q_INVOKABLE void deleteCurrentObject();


    Q_INVOKABLE void setSelectedMapObject(QVariant object);
    Q_INVOKABLE QVariant getSelectedMapObject();

    Q_INVOKABLE void testButtonOperation();
    Q_INVOKABLE void testButtonOperation2();
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

    Q_INVOKABLE QString getCaptchaUrl();



  //  Q_INVOKABLE QList<QGeoCoordinate *> getLineGeometry(QString textGeometry);

    Q_INVOKABLE int getLineCoordinatesNum();
    Q_INVOKABLE double getLineCoordinateLatAt(int i);
    Q_INVOKABLE double getLineCoordinateLonAt(int i);

    Q_INVOKABLE int getPolygonCoordinatesNum();
    Q_INVOKABLE double getPolygonCoordinateLatAt(int i);
    Q_INVOKABLE double getPolygonCoordinateLonAt(int i);

    Q_INVOKABLE QVariant findObjectUnderCursor(double lat, double lon);
    Q_INVOKABLE void prepareRegistration();
    Q_INVOKABLE void registerUser(QString name, QString password, QString captcha);
    Q_INVOKABLE QString getErrorMessage();
    Q_INVOKABLE void stopRegistration();





private:
    QObject *object;
    QVariant selectedMapObject;
   // int recentlyAddedLine;//while adding lines from db it is necessary to do it one after another

    DbConnection *dbConnection;
    QList<Acl> aclList;
    QList<TerrainUser> terrainUserList;
    QList<TerrainUser> terrainUserFromAclList;
    QVector<QPointF> lineVector;
    QVector<QPointF> polygonVector;
    QList<QLandmark> *dbLineLandmarks;
    QList<QLandmark> *dbPolygonLandmarks;
    QMap<QString, MapObject>* mapObjectMap;
    QString captcha;
    QString errorMessage;
    QString server;

    void deselectCurrentObject();
    void fixMapBug();
    void sendMapObjects();
    void makeRosterForUser(QString jid, QString password);
    QPointF getSouthestPoint(QVector<QPointF> vector);

    QList<TerrainUser> prepareCustomTerrainUserFromAclList(int i);
    //QString prepareSvg(QVector<QPointF> coordList, int type);

    JabberRegistrationTool *registrationTool;

    XmppClient cl;
signals:
    void sendObjects(QList<QLandmark> *landmarks);
    void sendMapObject(QString svg, QList<TerrainUser> userList);
    void sendNote(Note note, QList<TerrainUser> userList);
    void sendNegativeObject(QString id, QList<TerrainUser> userList);
    void aclListReady();
    void terrainUserListReady();
    void terrainUserFromAclListReady();
    void subscribeToUser(QString userJid);
    void test();
    void captchaReady();
    void registrationError();
    void registrationSuccess();
    void disconnectUser();
    void subscribeToLocation(QString jid);
    
public slots:
    void getAllPoints(QList<QLandmark> *dbLandmarks);
    void getAllLines(QList<QLandmark> *dbLandmarks);
    void getAllPolygons(QList<QLandmark> *dbLandmarks);
    void getConnectedUsers(QList<QLandmark> *userLandmarks);

    void updateUserPosition(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);

    void addLineFromDB();
    void addPolygonFromDB();

    void getCaptchaRegistrationUrl(QString captcha);
    void getError(QString error);
    void getSuccess();
};

#endif // CONTROLLER_H
