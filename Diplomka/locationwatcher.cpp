#include <QDebug>

#include "locationwatcher.h"

LocationWatcher::LocationWatcher(QObject *parent)
    : QObject(parent)
{
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        source->setUpdateInterval(6000); // time in milliseconds
        source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    }
}

void LocationWatcher::enable()
{
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
    }
}

void LocationWatcher::disable()
{
    if (source) {
        source->stopUpdates();
        disconnect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                   this, SLOT(positionUpdated(QGeoPositionInfo)));
    }
}

void LocationWatcher::positionUpdated(const QGeoPositionInfo &info)
{
   // qDebug()<<"update";
    if (info.isValid()) {
        emit updateMyLocation(info.coordinate().longitude(),info.coordinate().latitude());
       // qDebug()<<"WAT" << info;
    }
}
