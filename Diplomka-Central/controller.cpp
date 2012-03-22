#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    landMan= new QLandmarkManager(this);
    landMan->removeLandmarks(landMan->landmarks());



}

void Controller::getRootObject(QObject *obj){

    this->object=obj;

}

void Controller::addPoint(double lat, double lon){
    deselectCurrentObject();

    int dbId=dbConnection->insertPoint(lat,lon);

    if(dbId!=-1){

        QLandmark lm;
        lm.setName("lm");
        QGeoCoordinate coord(lat,lon);
        lm.setCoordinate(coord);
        lm.setName(QString::number(dbId));
        //..
        landMan->saveLandmark(&lm);

        foreach(QLandmark l, landMan->landmarks()){
            qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

        }


    } else {
        qDebug()<<"error in sql point insert";

    }

  //  emit sendObjects(&landMan->landmarks());



    //  qDebug()<< landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
    //  qDebug()<< landMan->error()<<landMan->errorString();

}

void Controller::selectObject(double lat, double lon){

    QLandmarkIntersectionFilter filter;
    QLandmarkProximityFilter proximityFilter;
    QGeoCoordinate center;
    center.setLatitude(lat);
    center.setLongitude(lon);
    proximityFilter.setCenter(center);
    proximityFilter.setRadius(10);
    filter.append(proximityFilter);



    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length();

    if(lms.length()>0){
        actualLandmark=lms.at(0);

    } else {
        deselectCurrentObject();
    }

}

void Controller::deselectCurrentObject(){
    qDebug()<<"deselecting";
    QLandmark lm;
    lm.setName("");
    QGeoCoordinate coord(0,0);
    lm.setCoordinate(coord);

    actualLandmark=lm;

}

void Controller::deleteCurrentObject(){


    if(actualLandmark.name()!=""){
        int result=dbConnection->deletePoint(actualLandmark.name());

        if(result!=-1){
            landMan->removeLandmark(actualLandmark);
            actualLandmark=pom;
            qDebug()<<"sql point delete succesful";
        } else {
            qDebug()<<"sql point delete failed";
        }
    }

}

void Controller::deselectObject(){
    qDebug()<<"object deselected";
    deselectCurrentObject();
}

void Controller::setSelectedMapObject(QVariant object){
    // qDebug()<<object;
    this->selectedMapObject=object;

}

QVariant Controller::getSelectedMapObject(){
    return this->selectedMapObject;
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

void Controller::createDb(QSqlDatabase db){
    dbConnection= new DbConnection(this);

    connect(dbConnection,SIGNAL(sendAllObjects(QList<QLandmark>*)),this,SLOT(getAllObjects(QList<QLandmark>*)));

    dbConnection->setDb(db);


}


void Controller::getAllObjects(QList<QLandmark> *dbLandmarks){

    qDebug()<<"saving landmarks" << landMan->saveLandmarks(dbLandmarks);
}

void Controller::getConnectedUsers(QList<QLandmark> *userLandmarks){
    qDebug()<<"saving user landmarks" << landMan->saveLandmarks(userLandmarks);
}

void Controller::updateUserPosition(QString jid, QGeoCoordinate coordinate){
    QLandmarkNameFilter filter;
    filter.setName(jid);
    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length()<<coordinate.latitude()<<coordinate.longitude()<<jid;
    if(lms.length()==0){
        QLandmark *lm = new QLandmark();
        lm->setName(jid);
        lm->setCoordinate(coordinate);
        lm->setPhoneNumber("1");
        landMan->saveLandmark(lm);
    } else {

        fixMapBug();
       // QLandmarkId id=lms.first().landmarkId();
        qDebug()<< landMan->removeLandmark( lms.at(0));
        QLandmark *updatedLm = new QLandmark();
      // updatedLm->setLandmarkId(id);
        updatedLm->setName(jid);
        updatedLm->setPhoneNumber("1");
        updatedLm->setCoordinate(coordinate);
        qDebug()<< landMan->saveLandmark(updatedLm);



    }
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

void Controller::sendMapObjects(){
    QStringList list;
    list.append("h.a.n.s@jabber.cz");//provizorni seznam online kontaktu

    foreach(QString jid, list){

        QList<QLandmark> lmList=dbConnection->getMapObjectsNotSentFor(jid);
        if (lmList.length()>0){

            emit sendObjects(&lmList);

        }
    }
}

void Controller::testButtonOperation(){
    sendMapObjects();
}

void Controller::createNewTerrainUser(QString id, QString name, QString surname, QString jid, QString password){
    //qDebug()<<name<<surname<<jid<<password;
    dbConnection->insertTerrainUser(id, name,surname,jid,password);

}

void Controller::createNewAcl(QString name){
   // qDebug()<<name;
    QString currentCentralUser="1";

    dbConnection->insertAcl(name, currentCentralUser);
}

void Controller::prepareAclList(){
    this->aclList=dbConnection->getAllAcls();

    emit aclListReady();
}

int Controller::getAclNum(){
    return this->aclList.length();
}

QString Controller::getAclNameAt(int i){
    return ((Acl)aclList.at(i)).getName();
}

void Controller::prepareTerrainUserList(){
    this->terrainUserList=dbConnection->getAllTerrainUsers();

    emit terrainUserListReady();
}

int Controller::getTerrainUserNum(){
    return this->terrainUserList.length();
}

QString Controller::getTerrainUserNameAt(int i){
    //qDebug()<<((TerrainUser)terrainUserList.at(i)).getId();

    return ((TerrainUser)terrainUserList.at(i)).getName();
}

QString Controller::getTerrainUserSurnameAt(int i){
    return ((TerrainUser)terrainUserList.at(i)).getSurname();
}

void Controller::prepareTerrainUserFromAclList(int i){

    if(i==-1){
        this->terrainUserFromAclList.clear();

    } else {
        QString id =((Acl)aclList.at(i)).getId();
        this->terrainUserFromAclList=dbConnection->getTerrainUsersFromAcl(id);
    }
    emit terrainUserFromAclListReady();
}

int Controller::getTerrainUserFromAclNum(){
    return this->terrainUserFromAclList.length();
}

QString Controller::getTerrainUserFromAclNameAt(int i){
    return ((TerrainUser)terrainUserFromAclList.at(i)).getName();
}

QString Controller::getTerrainUserFromAclSurnameAt(int i){
    return ((TerrainUser)terrainUserFromAclList.at(i)).getSurname();
}

void Controller::setTerrainUserAcl(int i, int j){
    QString idUser=((TerrainUser)terrainUserList.at(i)).getId();

    QString idAcl=((Acl)aclList.at(j)).getId();
    dbConnection->updateUserTerrainAcl(idUser,idAcl);
}

void Controller::unsetTerrainUserAcl(int i){
    QString idUser=((TerrainUser)terrainUserFromAclList.at(i)).getId();

    dbConnection->updateUserTerrainAcl(idUser,"NULL");
}

void Controller::removeAcl(int i){
    QString idAcl=((Acl)aclList.at(i)).getId();
    //qDebug()<<idAcl;
    this->prepareTerrainUserFromAclList(-1);
    dbConnection->deleteAcl(idAcl);
}

void Controller::removeTerrainUser(int i){
    QString id=((TerrainUser)terrainUserList.at(i)).getId();

    dbConnection->deleteTerrainUser(id);
}
