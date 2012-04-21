/*
  Multiuser mapping application for mobile device
  Autor: Jan Utekal
  VUT FIT 2012

 */

#include "Controller.h"
#define PATH ""

//class responsible for managing ui as well as using all back end classes
Controller::Controller(QObject *parent) :
    QObject(parent)
{
    QString path=PATH;
    path+="QXmppClientLog.log";
    QFile::remove(path);

    watcher.enable();
    connect(&watcher,SIGNAL(updateMyLocation(double,double)),this,SLOT(updateMyPosition(double, double)));
    myLat=0.0;
    myLon=0.0;
    mapObjectMap =new QMap<QString, MapObject>();
    landMan= new QLandmarkManager(this);
  //  prepareMapData();

     landMan->removeLandmarks(landMan->landmarks());


}

//sets xmppclient reference
void Controller::setClient(XmppClient *client){
    this->client=client;
}


void Controller::refreshPoints(){
    emit refresh();

}

int Controller::getPointNum(){
    return client->cList.length();

}

QString Controller::getJidFor(int i){
    Contact c=client->cList.at(i);
    return c.getJid();
}

float Controller::getLatFor(int i){
    Contact c=client->cList.at(i);
    return c.getLat().toFloat();
}

float Controller::getLonFor(int i){
    Contact c=client->cList.at(i);

    return c.getLon().toFloat();
}

//updates position of curret user
void Controller::updateMyPosition(double lon, double lat){
    myLat=lat;
    myLon=lon;
    client->sendMess(lat,lon); //provides the change for all subscribed users via xep 0080
    emit refreshMyPosition(); // change appears in ui

}

//returns latitude of current user
float Controller::getLatForMe(){
    return myLat;
}

//returns longitude of current user
float Controller::getLonForMe(){
    return myLon;
}

//
void Controller::setToVlist(QVariant v){//deprecated
    vList.push_front(v);
}

//
QVariant Controller::getFromVlistAt(int i){
  //  qDebug()<<vList.length();
    return vList.at(i);
}

int Controller::getMapPointNum(){
    return vList.length();
}

void Controller::clearVlist(){
    vList.clear();
}

//saves point map object received from central as a landmark
//coordlist has only one member, mapobjectid is an id of mapobject from central database, data are xml data for an object - assures persistance
void Controller::getPointFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){


    QLandmark lm;
    lm.setName(mapObjectId);
    qDebug()<<coordList.at(0).y();
    QGeoCoordinate coord(coordList.at(0).x(),coordList.at(0).y());
    lm.setCoordinate(coord);

    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();

    qDebug()<<"saving landmark"<<landMan->landmarks().length();

 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

//saves line map object received from central as a landmark
//coordlist represents points the line consists of, mapobjectid is an id of mapobject from central database, data are xml data for an object - assures persistance
void Controller::getLineFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){

    QLandmark lm;
    //lm.setDescription(line);
    lm.setName(mapObjectId);
    lm.setRadius(10);

    if(coordList.size()>0){
        QPointF point=getSouthestPoint(coordList);
        QGeoCoordinate coord(point.x(),point.y());
        lm.setCoordinate(coord);
        QString coords;

        foreach(QPointF p, coordList){
           coords+=QString::number(p.x());
           coords+=" ";
           coords+=QString::number(p.y());
           coords+=",";
        }
        coords.chop(1);
        lm.setDescription(coords);

    } else {
        qDebug()<<"lineVector empty";
    }
    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

//saves polygon map object received from central as a landmark
//coordlist represents points the line consiss of, mapobjectid is an id of mapobject from central database, data are xml data for an object - assures persistance
void Controller::getPolygonFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){

    QLandmark lm;
    //lm.setDescription(line);
    lm.setName(mapObjectId);
    lm.setRadius(20);

 //   lm.setDescription(data.replace("\"","\\\""));
    if(coordList.size()>0){
        QPointF point=getSouthestPoint(coordList);
        QGeoCoordinate coord(point.x(),point.y());
        lm.setCoordinate(coord);
        QString coords;

        foreach(QPointF p, coordList){
           coords+=QString::number(p.x());
           coords+=" ";
           coords+=QString::number(p.y());
           coords+=",";
        }
        coords.chop(1);
        lm.setDescription(coords);

    } else {
        qDebug()<<"polygonVector empty";
    }

    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

//updates some users point in landmark database
//jid identifies the user, coordinate represents lat and lon
void Controller::updateUserPosition(QString jid, QGeoCoordinate coordinate){
    QLandmarkNameFilter filter;
    filter.setName(jid);
    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length()<<coordinate.latitude()<<coordinate.longitude();
    if(lms.length()==0){
        QLandmark *lm = new QLandmark();
        lm->setName(jid);
        lm->setCoordinate(coordinate);
        lm->setRadius(1);
        landMan->saveLandmark(lm);


    } else {
        QLandmark lm=lms.first();
        lm.setCoordinate(coordinate);
        qDebug()<< landMan->saveLandmark(&lm);
        MapObject obj=mapObjectMap->value(jid);
        emit updatePositionForMapUser(obj.getPaintedObject(),coordinate.latitude(),coordinate.longitude());
      /*  fixMapBug();
        // QLandmarkId id=lms.first().landmarkId();
        qDebug()<< landMan->removeLandmark( lms.at(0));
        QLandmark *updatedLm = new QLandmark();
        // updatedLm->setLandmarkId(id);
        updatedLm->setName(jid);
        updatedLm->setRadius(1);
        updatedLm->setCoordinate(coordinate);
        qDebug()<< landMan->saveLandmark(updatedLm);
*/


    }

   // foreach(QLandmark l, landMan->landmarks()){
    //    qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

   // }
}

//
void Controller::fixMapBug(){//ted se nepouziva
    landMan->removeLandmark(pom);


    QLandmark pom2;



    pom2.setName("pom");
    QGeoCoordinate coord2(0,0);
    pom2.setCoordinate(coord2);
    pom2.setRadius(0);
    //..
    landMan->saveLandmark(&pom2);

    pom=pom2;
}


//gets user as jid from landmarks and sets his point to be grey on the map
void Controller::setUserOffline(QString jid){

    QLandmarkNameFilter filter;
    filter.setName(jid);
    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length()<<jid;
    if(lms.length()==0){

    } else {

        MapObject obj=mapObjectMap->value(jid);
        emit setMapUserOffline(obj.getPaintedObject());

    }
}

//returns number of points that a line consists of
//name represents the id from central database
int Controller::getLineCoordinatesNum(QString name){

    MapObject obj=mapObjectMap->value(name);


    return obj.getGeometry().size();
}

//returns latitude coordinate for ith point of line geometry
//name represents the id from central database
double Controller::getLineCoordinateLatAt(QString name, int i){
    MapObject obj=mapObjectMap->value(name);

    return obj.getGeometry().at(i).x();



}

//returns longitude coordinate for ith point of line geometry
//name represents the id from central database
double Controller::getLineCoordinateLonAt(QString name, int i){
    MapObject obj=mapObjectMap->value(name);
    double y=obj.getGeometry().at(i).y();

    return y;

}

//returns number of points that a polygon consists of
//name represents the id from central database
int Controller::getPolygonCoordinatesNum(QString name){
    MapObject obj=mapObjectMap->value(name);

    qDebug()<<"SIZE"<<obj.getGeometry().size();
    return obj.getGeometry().size();
}

//returns latitude coordinate for ith point of polygon geometry
//name represents the id from central database

double Controller::getPolygonCoordinateLatAt(QString name, int i){

    MapObject obj=mapObjectMap->value(name);

    return obj.getGeometry().at(i).x();



}

//returns latitude coordinate for ith point of polygon geometry
//name represents the id from central database
double Controller::getPolygonCoordinateLonAt(QString name, int i){

    MapObject obj=mapObjectMap->value(name);
    double y=obj.getGeometry().at(i).y();

    return y;

}

//adds reference to actually painted mapObject to mapObjectMap
//paintedobject stands for the painted map object, name is an id from central database, type stands for point/line/poly, coordinates are string representation of objects coordinates
void Controller::createMapObjectReference(QVariant paintedObject, QString name, int type, QString coordinates){
    MapObject mapObject;
    mapObject.setName(name);
    mapObject.setPaintedObject(paintedObject);
    mapObject.setType(type);
    qDebug()<<"koordinaty"<<coordinates;
    if(coordinates!=""){
        MapDataParser *parser=new MapDataParser();

        mapObject.setGeometry(parser->parseGeometry(coordinates));
        qDebug()<<"GEOMETRY"<<mapObject.getGeometry().size();
    }
    mapObjectMap->insert(name,mapObject);
   // delete parser;

}

//sets note to mapObject
void Controller::getNote(Note note){

    QLandmarkNameFilter filter;
    filter.setName(note.getId());
    QList<QLandmark> lms=landMan->landmarks(filter);
    if(lms.length()>0){
       // fixMapBug();
        // QLandmarkId id=lms.first().landmarkId();

        QLandmark lm=lms.first();
        lm.setPhoneNumber(note.getName()+"////"+note.getText());

        landMan->saveLandmark(&lm);

        emit changeNoteOf(note.getId(), note.getName()+"////"+note.getText());//the change has to be done from qml(mymap)

    } else{
        qDebug()<<"didnt find landmark for note - error";
    }
}

//returns painted map object
QVariant Controller::getMapObjectReference(QString name){

    MapObject obj=mapObjectMap->value(name);

    return obj.getPaintedObject();
}

//returns the southest point of some map objects geometry - used for displaying a note at its coordinate
QPointF Controller::getSouthestPoint(QVector<QPointF> vector){


    float lat=vector.at(0).x();
    float lon=vector.at(0).y();

    foreach(QPointF point, vector){
        if(lat>point.x()){
            lat=point.x();
            lon=point.y();
        }
    }

    return QPointF(lat,lon);


}

//used for clincing at notes for displaying its text
//filters all landmarks and checks whether there is one at coordinates lat/lon
void Controller::getObjectUnderCursor(double lat, double lon){
    QLandmarkIntersectionFilter filter;
    QLandmarkProximityFilter proximityFilter;
    QGeoCoordinate center;
    center.setLatitude(lat);
    center.setLongitude(lon);
    proximityFilter.setCenter(center);
    proximityFilter.setRadius(200);
    filter.append(proximityFilter);



    QList<QLandmark> lms=landMan->landmarks(filter);
   // qDebug()<<"found on this coords"<<lms.length();
    if(lms.length()>0){
           MapObject obj=mapObjectMap->value(lms.at(0).name());
           emit displayNoteText(obj.getPaintedObject());

    } else {
        emit hideNoteText();
    }
}

//
void Controller::prepareMapData(){
    QList<QLandmark> lms=landMan->landmarks();
    qDebug()<<"landmarky"<<lms.length()<<landMan->landmarks().length();
    landMan->removeLandmarks(landMan->landmarks());
    qDebug()<<"landmarky2"<<lms.length()<<landMan->landmarks().length();
    foreach(QLandmark lm, lms){
        qDebug()<<lm.description();

        QLandmark *lm2;
        lm2->setCoordinate(lm.coordinate());
      //  lm2->

        qDebug()<< landMan->saveLandmark(&lm);
            qDebug()<<landMan->errorString()<<landMan->error();
    }
}

//receives id of object that was deleted or invalidated and removes its landmark and reference
void Controller::getNegativeObject(QString negativeObject){
    QLandmarkNameFilter filter;
    filter.setName(negativeObject);
    QList<QLandmark> lms=landMan->landmarks(filter);

    if(lms.length()==0){
        qDebug()<<"no object to negate";
    } else {
        QLandmark lm=lms.at(0);

        landMan->removeLandmark(lm);
        mapObjectMap->remove(negativeObject);

    }
}

//receives message received from central user and provides it to ui
void Controller::getReceivedMessage(Message message){
    QString line=message.getTime();
    line+=" ";
    line+=message.getFrom().split("@").at(0);
    line+=": ";
    line+=message.getText();

    emit newMessageFromUser(line);
}

//sets central user jid
void Controller::setCentralUser(QString centralUser){
    this->centralUser=centralUser;
}

//sends message to central user
void Controller::sendMessageToUser(QString message){
    QString newMessage="<mess>%1</mess>";

    emit sendMessage(centralUser, newMessage.replace("%1",message));
}

//returns time in format
QString Controller::getCurrentDateTime(){
    QDateTime t=QDateTime::currentDateTime();
    QString outputFormat="hh:mm:ss";
    return t.toString(outputFormat);

}

//reconnects user with jid and password
void Controller::reconnectMe(QString username, QString password){
    emit reconnect(username, password);
}
