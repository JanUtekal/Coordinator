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


private:
    float myLat;
    float myLon;

    QLandmarkManager *landMan;
        QLandmark pom;
    QVector<QPointF> lineVector;

    void fixMapBug();

signals:
    void refresh();
    void refreshMyPosition();

public slots:
    void refreshPoints();
    void updateMyPosition(double lon, double lat);

    void getPointFromCentral(QVector<QPointF> coordList);
    void getLineFromCentral(QVector<QPointF> coordList);
    void updateUserPosition(QString jid, QGeoCoordinate coordinate);
    void setUserOffline(QString jid);

};

#endif // CONTROLLER_H
