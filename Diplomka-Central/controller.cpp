#include "controller.h"

#define POINT 0
#define LINE  1
#define POLYGON 2

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    landMan= new QLandmarkManager(this);
    landMan->removeLandmarks(landMan->landmarks());

}

void Controller::getRootObject(QObject *obj){

    this->object=obj;

}

void Controller::addPoint(double lat, double lon, int selectedAcl){
    deselectCurrentObject();

    int dbId=dbConnection->insertPoint(lat,lon);

    if(dbId!=-1){

        QLandmark lm;
        lm.setName("lm");
        QGeoCoordinate coord(lat,lon);
        lm.setCoordinate(coord);
        lm.setName(QString::number(dbId));
        lm.setPhoneNumber("0");
        //..
        landMan->saveLandmark(&lm);


        //  QString aclId=((Acl)aclList.at(selectedAcl)).getId();
        if(selectedAcl!=-1){

            QList<TerrainUser> userList= prepareCustomTerrainUserFromAclList(selectedAcl);
            QVector<QPointF> coordList;
            coordList.append(QPointF(lat,lon));
            DataPreparator *preparator=new DataPreparator();
            QString data=preparator->prepareData(coordList, POINT);
            emit sendMapObject(data,userList);
            delete preparator;
        } else {
            qDebug()<<"neoznacen zadny Acl, neposilam";
        }


        /*     foreach(QLandmark l, landMan->landmarks()){
            qDebug()<<l.name()<<l.coordinate().latitude()<<l.coordinate().longitude();

        }*/


    } else {
        qDebug()<<"error in sql point insert";

    }

    //  emit sendObjects(&landMan->landmarks());



    //  qDebug()<< landMan->exportLandmarks("landmarks",QLandmarkManager::Lmx);
    //  qDebug()<< landMan->error()<<landMan->errorString();

}


void Controller::addLinePoint(double lat, double lon){
    lineVector.append(QPointF(lat,lon));

}

void Controller::lineReady(int selectedAcl){
    qDebug()<<"line ready";

    /*   foreach(QPointF point, lineVector){
        qDebug()<<point.x()<<point.y();
    }*/
    if(lineVector.size()>1){

        int dbId=dbConnection->insertLine(lineVector);

        if(dbId!=-1){

            QLandmark lm;
            lm.setName("lm");
            QGeoCoordinate coord(QPointF(lineVector.at(0)).x(),QPointF(lineVector.at(0)).y());
            lm.setCoordinate(coord);
            lm.setName(QString::number(dbId));
        //not necessary for this moment
            QString coords;

            foreach(QPointF p, lineVector){
               coords+=QString::number(p.x());
               coords+=" ";
               coords+=QString::number(p.y());
               coords+=",";
            }
            coords.chop(1);
            lm.setDescription(coords);
           // qDebug()<<lm.description();
            lm.setPhoneNumber("10");
            //..
            landMan->saveLandmark(&lm);

            if(selectedAcl!=-1){

                QList<TerrainUser> userList= prepareCustomTerrainUserFromAclList(selectedAcl);
                DataPreparator *preparator=new DataPreparator();
                QString data=preparator->prepareData(lineVector, LINE);
                emit sendMapObject(data,userList);
                delete preparator;

            } else {
                qDebug()<<"neoznacen zadny Acl, neposilam";
            }

        }


        //lineVector.clear();

    }


}

void Controller::selectObject(QString name){

   /* QLandmarkIntersectionFilter filter;
    QLandmarkProximityFilter proximityFilter;
    QGeoCoordinate center;
    center.setLatitude(lat);
    center.setLongitude(lon);
    proximityFilter.setCenter(center);
    proximityFilter.setRadius(10);
    filter.append(proximityFilter);



    QList<QLandmark> lms=landMan->landmarks(filter);
    qDebug()<<"found on this coords"<<lms.length();
*/
    QLandmarkNameFilter filter;
    filter.setName(name);
    QList<QLandmark> lms=landMan->landmarks(filter);
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
        int result=dbConnection->deleteObject(actualLandmark.name());

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

    connect(dbConnection,SIGNAL(sendAllPoints(QList<QLandmark>*)),this,SLOT(getAllPoints(QList<QLandmark>*)));
    connect(dbConnection,SIGNAL(sendAllLines(QList<QLandmark>*)),this,SLOT(getAllLines(QList<QLandmark>*)));

    dbConnection->setDb(db);


}


void Controller::getAllPoints(QList<QLandmark> *dbLandmarks){

    landMan->saveLandmarks(dbLandmarks);
}

void Controller::getAllLines(QList<QLandmark> *dbLandmarks){

  //  qDebug()<<"got LINES";
    dbLineLandmarks=dbLandmarks;
    addLineFromDB();



}

void Controller::addLineFromDB(){
    if(dbLineLandmarks->length()>0){
        QLandmark lm=dbLineLandmarks->takeFirst();
        QString coords=lm.description();

        QStringList coordList=coords.split(",");


        foreach(QString coord, coordList){
            QStringList c=coord.split(" ");
            QPointF point(c.at(1).toDouble(), c.at(0).toDouble());
            lineVector.append(point);

        }
        lm.setCoordinate(QGeoCoordinate(lineVector.at(0).x(), lineVector.at(1).y()));
        landMan->saveLandmark(&lm);


    }

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
    // sendMapObjects();
    emit test();
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
    dbConnection->updateTerrainUserAcl(idUser,idAcl);
}

void Controller::unsetTerrainUserAcl(int i){
    QString idUser=((TerrainUser)terrainUserFromAclList.at(i)).getId();

    dbConnection->updateTerrainUserAcl(idUser,"NULL");
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

QList<TerrainUser> Controller::prepareCustomTerrainUserFromAclList(int i){


    QString id =((Acl)aclList.at(i)).getId();
    return dbConnection->getTerrainUsersFromAcl(id);

}
/*
QList<QGeoCoordinate *> Controller::getLineGeometry(QString textGeometry){

        QStringList points=textGeometry.split("/");
        QList<QGeoCoordinate* > coordinates;

        foreach(QString point, points){
            qDebug()<<point;
            QStringList coords=point.split(",");

            QGeoCoordinate* coordinate = new QGeoCoordinate();


            coordinate->setLatitude(coords.at(0).toDouble());

            coordinate->setLongitude(coords.at(1).toDouble());

            coordinates.append(coordinate);
qDebug()<<"2";
        }




        return coordinates;
}
*/

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
        addLineFromDB();
    }

    return y;

}
