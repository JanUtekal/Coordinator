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

    landMan= new QLandmarkManager(this);
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

void Controller::setToVlist(QVariant v){
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

void Controller::getPointFromCentral(QVector<QPointF> coordList){


    QLandmark lm;
    lm.setName("lm");
    qDebug()<<coordList.at(0).y();
    QGeoCoordinate coord(coordList.at(0).x(),coordList.at(0).y());
    lm.setCoordinate(coord);
  //  qDebug()<<"1";
    //..
    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();

    qDebug()<<"saving landmark"<<landMan->landmarks().length();
    foreach(QLandmark l, landMan->landmarks()){
  //      qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

    }
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

void Controller::getLineFromCentral(QVector<QPointF> coordList){

    QLandmark lm;
    //lm.setDescription(line);
    lm.setName("line");
    lm.setPhoneNumber("10");
    lineVector=coordList;
    lm.setCoordinate(QGeoCoordinate(lineVector.at(0).x(), lineVector.at(1).y()));
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
        lm->setPhoneNumber("1");
        landMan->saveLandmark(lm);
    } else {

        fixMapBug();
        QLandmarkId id=lms.first().landmarkId();
        qDebug()<< landMan->removeLandmark( lms.at(0));
        QLandmark *updatedLm = new QLandmark();
      // updatedLm->setLandmarkId(id);
        updatedLm->setName(jid);
        updatedLm->setPhoneNumber("1");
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
    pom2.setPhoneNumber("0");
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
        updatedLm->setPhoneNumber("2");
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
    qDebug()<<"getting y"<<i<<y;

    if(i==lineVector.size()-1){

        lineVector.clear();
        //addLineFromDB();
    }

    return y;

}
