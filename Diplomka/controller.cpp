#include "Controller.h"
#define PATH ""
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
    //prepareMapData();

     landMan->removeLandmarks(landMan->landmarks());


}

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

void Controller::updateMyPosition(double lon, double lat){
    myLat=lat;
    myLon=lon;
    client->sendMess(lat,lon);
    emit refreshMyPosition();

}

float Controller::getLatForMe(){
    return myLat;
}

float Controller::getLonForMe(){
    return myLon;
}

void Controller::setToVlist(QVariant v){//deprecated
    vList.push_front(v);
}

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

void Controller::getPointFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){


    QLandmark lm;
    lm.setName(mapObjectId);
    qDebug()<<coordList.at(0).y();
    QGeoCoordinate coord(coordList.at(0).x(),coordList.at(0).y());
    lm.setCoordinate(coord);
  //  lm.setDescription(data);

  //  qDebug()<<"1";
    //..
    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();

    qDebug()<<"saving landmark"<<landMan->landmarks().length();

 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

void Controller::getLineFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){

    QLandmark lm;
    //lm.setDescription(line);
    lm.setName(mapObjectId);
    lm.setRadius(10);

    lineVector=coordList;
    if(lineVector.size()>0){
        QPointF point=getSouthestPoint(lineVector);
        QGeoCoordinate coord(point.x(),point.y());
        lm.setCoordinate(coord);
    } else {
        qDebug()<<"polygonVector empty";
    }
    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

void Controller::getPolygonFromCentral(QVector<QPointF> coordList, QString mapObjectId, QString data){

    QLandmark lm;
    //lm.setDescription(line);
    lm.setName(mapObjectId);
    lm.setRadius(20);
    polygonVector=coordList;
 //   lm.setDescription(data.replace("\"","\\\""));
    if(polygonVector.size()>0){
        QPointF point=getSouthestPoint(polygonVector);
        QGeoCoordinate coord(point.x(),point.y());
        lm.setCoordinate(coord);
    } else {
        qDebug()<<"polygonVector empty";
    }

    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

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

        fixMapBug();
        QLandmarkId id=lms.first().landmarkId();
        qDebug()<< landMan->removeLandmark( lms.at(0));
        QLandmark *updatedLm = new QLandmark();
      // updatedLm->setLandmarkId(id);
        updatedLm->setName(jid);
        updatedLm->setRadius(1);
        updatedLm->setCoordinate(coordinate);
        qDebug()<< landMan->saveLandmark(updatedLm);



    }

    foreach(QLandmark l, landMan->landmarks()){
        qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

    }
}

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

void Controller::setUserOffline(QString jid){

    QLandmarkNameFilter filter;
    filter.setName(jid);
    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length()<<jid;
    if(lms.length()==0){

    } else {

        fixMapBug();
      //  QLandmarkId id=lms.first().landmarkId();
        qDebug()<< landMan->removeLandmark( lms.at(0));
        QLandmark *updatedLm = new QLandmark();
      // updatedLm->setLandmarkId(id);
        updatedLm->setName(jid);
        updatedLm->setRadius(2);
        updatedLm->setCoordinate(lms.at(0).coordinate());
        qDebug()<< landMan->saveLandmark(updatedLm);



    }
}

int Controller::getLineCoordinatesNum(){
    qDebug()<<"SIZE"<<lineVector.size();
    return lineVector.size();
}

double Controller::getLineCoordinateLatAt(int i){

    return lineVector.at(i).x();



}

double Controller::getLineCoordinateLonAt(int i){

    double y=lineVector.at(i).y();


    if(i==lineVector.size()-1){

        lineVector.clear();
        //addLineFromDB();
    }

    return y;

}

int Controller::getPolygonCoordinatesNum(){

    return polygonVector.size();
}

double Controller::getPolygonCoordinateLatAt(int i){

    return polygonVector.at(i).x();



}

double Controller::getPolygonCoordinateLonAt(int i){

    double y=polygonVector.at(i).y();


    if(i==polygonVector.size()-1){

        polygonVector.clear();
        //addLineFromDB();
    }

    return y;

}

void Controller::createMapObjectReference(QVariant paintedObject, QString name, int type){
    MapObject mapObject;
    mapObject.setName(name);
    mapObject.setPaintedObject(paintedObject);
    mapObject.setType(type);
    mapObjectMap->insert(name,mapObject);

}

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

QVariant Controller::getMapObjectReference(QString name){

    MapObject obj=mapObjectMap->value(name);

    return obj.getPaintedObject();
}

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

void Controller::prepareMapData(){
    QList<QLandmark> lms=landMan->landmarks();
    landMan->removeLandmarks(landMan->landmarks());
    MapDataParser * parser=new MapDataParser();


    foreach(QLandmark lm, lms){
      //  qDebug()<<lm.description();

        QVector<QPointF> coords;
        QString name;


        int type=parser->parseSVGData(lm.description(),name,coords);

        MapObject mapObject;
        mapObject.setName(name);
       // mapObject.setPaintedObject(paintedObject);
        mapObject.setType(type);
        mapObjectMap->insert(name,mapObject);

        landMan->saveLandmark(&lm);
    }
}

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
