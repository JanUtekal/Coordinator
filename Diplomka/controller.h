#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "xmppclient.h"
#include "locationwatcher.h"
#include <QLandmark>
#include <QLandmarkManagerEngine>
#include <qlandmarkmanager.h>
#include <qlandmark.h>
#include <QLandmarkNameFilter>
#include "mapobject.h"
#include "note.h"
#include <QLandmarkProximityFilter>
#include <QLandmarkIntersectionFilter>
#include "mapdataparser.h"
#include "message.h"
QTM_USE_NAMESPACE

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void setCentralUser(QString centralUser); // get jid of current central user
    void setClient(XmppClient* client); // sets reference to xmppclient object
    XmppClient* client;
    LocationWatcher watcher; // object getting users gps coordinates
    QVariantList vList;

    Q_INVOKABLE int getPointNum(); // get number of points stored
    Q_INVOKABLE QString getJidFor(int i); // gets jid of user on map
    Q_INVOKABLE float getLatFor(int i); // gets latitude of user on map
    Q_INVOKABLE float getLonFor(int i); // gets longitude of user on map
    Q_INVOKABLE float getLatForMe(); // gets lat of current user
    Q_INVOKABLE float getLonForMe(); // gets lon of current user
    Q_INVOKABLE void setToVlist(QVariant v);
    Q_INVOKABLE QVariant getFromVlistAt(int i);
    Q_INVOKABLE int getMapPointNum();//number of points in vList
    Q_INVOKABLE void clearVlist(); //erases the vlist

    Q_INVOKABLE int getLineCoordinatesNum(QString name);
    Q_INVOKABLE double getLineCoordinateLatAt(QString name,int i);
    Q_INVOKABLE double getLineCoordinateLonAt(QString name,int i);

    Q_INVOKABLE int getPolygonCoordinatesNum(QString name);
    Q_INVOKABLE double getPolygonCoordinateLatAt(QString name,int i);
    Q_INVOKABLE double getPolygonCoordinateLonAt(QString name,int i);

    Q_INVOKABLE void createMapObjectReference(QVariant paintedObject, QString name, int type, QString coordinates);
    Q_INVOKABLE QVariant getMapObjectReference(QString name);

    Q_INVOKABLE void getObjectUnderCursor(double lat, double lon);
    Q_INVOKABLE void sendMessageToUser(QString message);
    Q_INVOKABLE QString getCurrentDateTime();

    Q_INVOKABLE void reconnectMe(QString username, QString password);
private:
    float myLat; // latitude coordinate of current user
    float myLon; // longitude coordinate of current user
    QString centralUser; // jid of current central user
    QLandmarkManager *landMan; // instance of landmark manager which is handling map objects represented as landmarks
    QLandmark pom;

    QMap<QString, MapObject>* mapObjectMap; // map of currently painted objects on map. Stores some additional information and provides a way to get to the actual points, lines and polys

    void fixMapBug(); //
    QPointF getSouthestPoint(QVector<QPointF> vector); //calculates the southest point of some map object for setting the note
    void prepareMapData();
signals:
    void refresh(); //
    void refreshMyPosition(); // updates position of current user on map
    void changeNoteOf(QString name, QString note); // updates note name and text for some map object
    void displayNoteText(QVariant mapObject); // makes the appearance of a text for some note
    void hideNoteText(); // hides the text
    void updatePositionForMapUser(QVariant userPoint, double lat, double lon); // when new coordinate of some user is received, this makes his point to update
    void setMapUserOffline(QVariant userPoint); // when user goes offline this makes his point turn grey
    void sendMessage(QString jid, QString message); // provides received message to ui
    void newMessageFromUser(QString line); //
    void reconnect(QString username, QString password); // reconnects to xmpp server with other jid
public slots:
    void refreshPoints();
    void updateMyPosition(double lon, double lat);

    void getPointFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void getLineFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void getPolygonFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data);
    void getNote(Note note);
    void getNegativeObject(QString negativeObject);

    void updateUserPosition(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);

    void getReceivedMessage(Message message);

};

#endif // CONTROLLER_H
