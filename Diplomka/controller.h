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
QTM_USE_NAMESPACE

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    void setClient(XmppClient* client);
    XmppClient* client;
    LocationWatcher watcher;
    QVariantList vList;

    Q_INVOKABLE int getPointNum();
    Q_INVOKABLE QString getJidFor(int i);
    Q_INVOKABLE float getLatFor(int i);
    Q_INVOKABLE float getLonFor(int i);
    Q_INVOKABLE float getLatForMe();
    Q_INVOKABLE float getLonForMe();
    Q_INVOKABLE void setToVlist(QVariant v);
    Q_INVOKABLE QVariant getFromVlistAt(int i);
    Q_INVOKABLE int getMapPointNum();//pocet objektu ve vListu
    Q_INVOKABLE void clearVlist();

    Q_INVOKABLE int getLineCoordinatesNum();
    Q_INVOKABLE double getLineCoordinateLatAt(int i);
    Q_INVOKABLE double getLineCoordinateLonAt(int i);

    Q_INVOKABLE int getPolygonCoordinatesNum();
    Q_INVOKABLE double getPolygonCoordinateLatAt(int i);
    Q_INVOKABLE double getPolygonCoordinateLonAt(int i);

    Q_INVOKABLE void createMapObjectReference(QVariant paintedObject, QString name, int type);
    Q_INVOKABLE QVariant getMapObjectReference(QString name);

    Q_INVOKABLE void getObjectUnderCursor(double lat, double lon);
private:
    float myLat;
    float myLon;

    QLandmarkManager *landMan;
        QLandmark pom;
    QVector<QPointF> lineVector;
    QVector<QPointF> polygonVector;
    QMap<QString, MapObject>* mapObjectMap;

    void fixMapBug();
    QPointF getSouthestPoint(QVector<QPointF> vector);
    void prepareMapData();
signals:
    void refresh();
    void refreshMyPosition();
    void changeNoteOf(QString name, QString note);
    void displayNoteText(QVariant mapObject);
    void hideNoteText();

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

};

#endif // CONTROLLER_H
