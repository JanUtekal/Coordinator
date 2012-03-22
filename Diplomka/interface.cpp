#include "interface.h"
#define PATH ""
Interface::Interface(QObject *parent) :
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

void Interface::setClient(xmppClient *client){
    this->client=client;
}


void Interface::refreshPoints(){
    emit refresh();

}

int Interface::getPointNum(){
    return client->cList.length();

}

QString Interface::getJidFor(int i){
    Contact c=client->cList.at(i);
    return c.getJid();
}

float Interface::getLatFor(int i){
    Contact c=client->cList.at(i);
    return c.getLat().toFloat();
}

float Interface::getLonFor(int i){
    Contact c=client->cList.at(i);

    return c.getLon().toFloat();
}

void Interface::updateMyPosition(double lon, double lat){
    myLat=lat;
    myLon=lon;
    client->sendMess(lat,lon);
    emit refreshMyPosition();

}

float Interface::getLatForMe(){
    return myLat;
}

float Interface::getLonForMe(){
    return myLon;
}

void Interface::setToVlist(QVariant v){
    vList.push_front(v);
}

QVariant Interface::getFromVlistAt(int i){
  //  qDebug()<<vList.length();
    return vList.at(i);
}

int Interface::getMapPointNum(){
    return vList.length();
}

void Interface::clearVlist(){
    vList.clear();
}

void Interface::getPointFromCentral(QString point){

    double lat=point.split(" ").at(0).split("(").at(1).toDouble();
    double lon=point.split(" ").at(1).split(")").at(0).toDouble();

    qDebug()<<"1";
    QLandmark lm;
    lm.setName("lm");
    QGeoCoordinate coord(lat,lon);
    lm.setCoordinate(coord);
    qDebug()<<"1";
    //..
    qDebug()<< landMan->saveLandmark(&lm);
    qDebug()<<landMan->errorString()<<landMan->error();

    qDebug()<<"saving landmark"<<landMan->landmarks().length();
    foreach(QLandmark l, landMan->landmarks()){
        qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

    }
 //   landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
}

void Interface::updateUserPosition(QString jid, QGeoCoordinate coordinate){
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

void Interface::fixMapBug(){//ted se nepouziva
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

void Interface::setUserOffline(QString jid){

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
