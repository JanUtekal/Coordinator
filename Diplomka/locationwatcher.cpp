/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012

 */

#include <QDebug>

#include "locationwatcher.h"


//this class gets users geolocation data and transmits them to controller
LocationWatcher::LocationWatcher(QObject *parent)
    : QObject(parent)
{
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        source->setUpdateInterval(6000); // time in milliseconds
        source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    }
}

//sets getting geolocation enabled
void LocationWatcher::enable()
{
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
    }
}

//sets getting geolocation disabled
void LocationWatcher::disable()
{
    if (source) {
        source->stopUpdates();
        disconnect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                   this, SLOT(positionUpdated(QGeoPositionInfo)));
    }
}

//slot getting update of the geo position
void LocationWatcher::positionUpdated(const QGeoPositionInfo &info)
{
   //qDebug()<<"update";
    if (info.isValid()) {
        emit updateMyLocation(info.coordinate().longitude(),info.coordinate().latitude());
       // qDebug()<<"WAT" << info;
    }
}
