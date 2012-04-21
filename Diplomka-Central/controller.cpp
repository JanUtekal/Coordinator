#include "controller.h"
#define POINT 0
#define LINE  1
#define POLYGON 2
#define VALIDATIONINTERVAL 15000


Controller::Controller(QObject *parent) :
    QObject(parent)
{
    landMan= new QLandmarkManager(this);
    landMan->removeLandmarks(landMan->landmarks());

    dbLineLandmarks =new QList<QLandmark>();
    dbPolygonLandmarks =new QList<QLandmark>();
    mapObjectMap =new QMap<QString, MapObject>();


    registrationTool = new JabberRegistrationTool(this);
    connect(registrationTool, SIGNAL(sendCaptcha(QString)),this,SLOT(getCaptchaRegistrationUrl(QString)));
    connect(registrationTool, SIGNAL(sendError(QString)),this,SLOT(getError(QString)));
    connect(registrationTool, SIGNAL(sendSuccess()),this,SLOT(getSuccess()));

    server="jabber.cz";

    noDbMode=false;


    //
}

void Controller::getRootObject(QObject *obj){

    this->object=obj;

}

void Controller::setNoDbMode(){
    noDbMode=true;
    dbConnection= new DbConnection(this);
    qDebug()<<"nodbmode";
    QTimer::singleShot(1000,this,SLOT(sendNoDbSig()));
}

void Controller::sendNoDbSig(){
    emit noDbModeSig();
}

void Controller::addPoint(double lat, double lon, int selectedAcl){

    deselectCurrentObject();
    QString aclId = "-1";
    if(selectedAcl!=-1 && !noDbMode){

        aclId=((Acl)aclList.at(selectedAcl)).getId();
    }
    int dbId=dbConnection->insertPoint(lat,lon,aclId);

    if(dbId!=-1 || noDbMode){

        QLandmark lm;

        QGeoCoordinate coord(lat,lon);
        lm.setCoordinate(coord);
        lm.setName(QString::number(dbId));
        lm.setRadius(0);
        //..
        landMan->saveLandmark(&lm);

        qDebug()<<"adding point";
        //  QString aclId=((Acl)aclList.at(selectedAcl)).getId();
        if(selectedAcl!=-1){

            QList<TerrainUser> userList= prepareCustomTerrainUserFromAclList(selectedAcl);
            QVector<QPointF> coordList;
            coordList.append(QPointF(lat,lon));
            DataPreparator *preparator=new DataPreparator();
            qDebug()<<"a";
            QString data=preparator->prepareData(coordList, QString::number(dbId), POINT);
            qDebug()<<"b";
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
        QString aclId = "-1";
        if(selectedAcl!=-1 && !noDbMode){
            aclId=((Acl)aclList.at(selectedAcl)).getId();
        }
        int dbId=dbConnection->insertLine(lineVector, aclId);

        if(dbId!=-1 || noDbMode){

            QLandmark lm;

            if(lineVector.size()>0){
                QPointF point=getSouthestPoint(lineVector);
                QGeoCoordinate coord(point.x(),point.y());
                lm.setCoordinate(coord);
            } else {
                qDebug()<<"lineVector empty";
            }

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
            lm.setRadius(10);
            //..
            landMan->saveLandmark(&lm);

            if(selectedAcl!=-1){

                QList<TerrainUser> userList= prepareCustomTerrainUserFromAclList(selectedAcl);
                DataPreparator *preparator=new DataPreparator();
                QString data=preparator->prepareData(lineVector, QString::number(dbId), LINE);
                emit sendMapObject(data,userList);
                delete preparator;

            } else {
                qDebug()<<"neoznacen zadny Acl, neposilam";
            }

        }


        //lineVector.clear();

    }


}

void Controller::addPolygonPoint(double lat, double lon){
    polygonVector.append(QPointF(lat,lon));
}

void Controller::polygonReady(int selectedAcl){
    qDebug()<<"polygon ready";

    /*   foreach(QPointF point, lineVector){
        qDebug()<<point.x()<<point.y();
    }*/


    if(polygonVector.size()>2){
        QString aclId = "-1";
        if(selectedAcl!=-1 && !noDbMode){
            aclId=((Acl)aclList.at(selectedAcl)).getId();
        }
        int dbId=dbConnection->insertPolygon(polygonVector,aclId);

        if(dbId!=-1 || noDbMode){

            QLandmark lm;
            if(polygonVector.size()>0){
                QPointF point=getSouthestPoint(polygonVector);
                QGeoCoordinate coord(point.x(),point.y());
                lm.setCoordinate(coord);
            } else {
                qDebug()<<"polygonvector empty";
            }
            lm.setName(QString::number(dbId));
        //not necessary for this moment
            QString coords;

            foreach(QPointF p, polygonVector){
               coords+=QString::number(p.x());
               coords+=" ";
               coords+=QString::number(p.y());
               coords+=",";
            }
            coords.chop(1);
            lm.setDescription(coords);
           // qDebug()<<lm.description();
            lm.setRadius(20);
            //..
            landMan->saveLandmark(&lm);

            if(selectedAcl!=-1){

                QList<TerrainUser> userList= prepareCustomTerrainUserFromAclList(selectedAcl);
                DataPreparator *preparator=new DataPreparator();
                QString data=preparator->prepareData(polygonVector, QString::number(dbId), POLYGON);
                emit sendMapObject(data,userList);
                delete preparator;

            } else {
                qDebug()<<"neoznacen zadny Acl, neposilam";
            }

        }


        //lineVector.clear();

    }



}

void Controller::createMapObjectReference(QVariant paintedObject, QString name, int type){
    MapObject mapObject;
    mapObject.setName(name);
    mapObject.setPaintedObject(paintedObject);
    mapObject.setType(type);
    mapObject.setAclId(dbConnection->getMapObjectAcl(name));




    mapObjectMap->insert(name,mapObject);

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
  //  QGeoCoordinate coord(0,0);
  //  lm.setCoordinate(coord);

    actualLandmark=lm;

}

void Controller::deleteCurrentObject(){


    if(actualLandmark.name()!=""){
        QString id=actualLandmark.name();
        MapObject obj=mapObjectMap->value(actualLandmark.name());
        QString aclId=obj.getAClId();
        int result=dbConnection->deleteObject(id);

        if(result!=-1){
            dbConnection->deleteNote(actualLandmark.name());
            mapObjectMap->remove(actualLandmark.name());
            landMan->removeLandmark(actualLandmark);
            actualLandmark=pom;
            qDebug()<<"sql point delete succesful";

            QList<TerrainUser> userList= dbConnection->getTerrainUsersFromAcl(aclId);

            emit sendNegativeObject(id, userList);





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
    pom2.setRadius(0);
    //..
    landMan->saveLandmark(&pom2);

    pom=pom2;
}

void Controller::createDb(QSqlDatabase db){
    dbConnection= new DbConnection(this);

    connect(dbConnection,SIGNAL(sendAllPoints(QList<QLandmark>*)),this,SLOT(getAllPoints(QList<QLandmark>*)));
    connect(dbConnection,SIGNAL(sendAllLines(QList<QLandmark>*)),this,SLOT(getAllLines(QList<QLandmark>*)));
    connect(dbConnection,SIGNAL(sendAllPolygons(QList<QLandmark>*)),this,SLOT(getAllPolygons(QList<QLandmark>*)));
    connect(dbConnection,SIGNAL(sendOutdatedObjects(QStringList)),this,SLOT(getOutdatedObjects(QStringList)));
    connect(dbConnection,SIGNAL(userAclUpdated()),this,SLOT(getUserAclUpdated()));

    dbConnection->setDb(db);
    prepareTerrainUserList();
    validationTimer=new QTimer(this);
    connect(validationTimer,SIGNAL(timeout()), dbConnection,SLOT(validateMapObjects()));
    validationTimer->setInterval(VALIDATIONINTERVAL);
    validationTimer->start();
}


void Controller::getAllPoints(QList<QLandmark> *dbLandmarks){

    landMan->saveLandmarks(dbLandmarks);
}

void Controller::getAllLines(QList<QLandmark> *dbLandmarks){

  //  qDebug()<<"got LINES";
    dbLineLandmarks=dbLandmarks;
    addLineFromDB();



}

void Controller::getAllPolygons(QList<QLandmark> *dbLandmarks){

    qDebug()<<"got LINES";
    dbPolygonLandmarks=dbLandmarks;
    qDebug()<<"got polys";
    addPolygonFromDB();



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
        if(lineVector.size()>0){
            QPointF point=getSouthestPoint(lineVector);
            QGeoCoordinate coord(point.x(),point.y());
            lm.setCoordinate(coord);
        } else {
            qDebug()<<"lineVector empty";
        }


        landMan->saveLandmark(&lm);


    }

}

void Controller::addPolygonFromDB(){
    if(dbPolygonLandmarks->length()>0){
        QLandmark lm=dbPolygonLandmarks->takeFirst();
        QString coords=lm.description();
//qDebug()<<coords;
        QStringList coordList=coords.split(",");


        foreach(QString coord, coordList){
            QStringList c=coord.split(" ");
            QPointF point(c.at(1).toDouble(), c.at(0).toDouble());
            polygonVector.append(point);

        }

        if(polygonVector.size()>0){
            QPointF point=getSouthestPoint(polygonVector);
            QGeoCoordinate coord(point.x(),point.y());
            lm.setCoordinate(coord);
        } else {
            qDebug()<<"polygonvector empty";
        }


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
        lm->setRadius(1);
        landMan->saveLandmark(lm);


    } else {
        QLandmark lm=lms.first();
        lm.setCoordinate(coordinate);
        qDebug()<< landMan->saveLandmark(&lm);
        MapObject obj=mapObjectMap->value(jid);
        emit updatePositionForMapUser(obj.getPaintedObject(),coordinate.latitude(),coordinate.longitude());
        dbConnection->insertUserPosition(jid,coordinate.latitude(),coordinate.longitude());

    }
}

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
    qDebug()<<"test";
   // emit test();
   // emit subscribeToUser("terrainuser2@jabber.sh.cvut.cz");

    //


   // registrationTool->cancelRegistration(jid,"jabber.cz");
 /*   QStringList jidList=dbConnection->getAllJids();

    QXmppConfiguration config;

    config.setJid("terrainuser3@jabber.cz");
    config.setPassword("asasasd");
    config.setAutoAcceptSubscriptions(true);
   // config.setIgnoreAuth(true);
  //  emit disconnectUser();
    cl.connectToServer(config);
    cl.startSubscribingToUsers(jidList);*/
  //  emit subscribeToLocation("terrainuser1@jabber.cz/QXmpp");



}


void Controller::testButtonOperation2(){
    // sendMapObjects();
 /*   qDebug()<<"test2";
    QStringList jidList=dbConnection->getAllJids();
   // emit test();
    QXmppConfiguration config;

    config.setJid("terrainuser4@jabber.cz");
    config.setPassword("asasasd");
    config.setAutoAcceptSubscriptions(true);
   // config.setIgnoreAuth(true);
  //  emit disconnectUser();
    cl.connectToServer(config);
    cl.startSubscribingToUsers(jidList);*/

}

void Controller::createNewTerrainUser(QString id, QString name, QString surname, QString username, QString password){
    //qDebug()<<name<<surname<<jid<<password;
    QString jid=username;
    jid+="@";
    jid+=server;

    dbConnection->insertTerrainUser(id, name,surname,jid,password);

    this->makeRosterForUser(jid,password);

}

void Controller::createNewAcl(QString name, int validity){

    QString currentCentralUser="1";
    if(validity==0){
        validity=999;
    }

    dbConnection->insertAcl(name, currentCentralUser, validity);
}

void Controller::prepareAclList(){
    this->aclList=dbConnection->getValidAcls();
    qDebug()<<"acls got"<<aclList.length();

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
    QString jid=((TerrainUser)terrainUserList.at(i)).getJid();
    QString password=((TerrainUser)terrainUserList.at(i)).getPassword();

    qDebug()<<"removing user"<<jid;
   // registrationTool->cancelRegistration(jid,"jabber.cz");
    QXmppConfiguration config;
    qDebug()<<jid;
    config.setJid(jid);
    config.setPassword(password);
    config.setAutoAcceptSubscriptions(true);
   // config.setIgnoreAuth(true);
  //  emit disconnectUser();
    cl.connectToServer(config);

    cl.unregister();

    dbConnection->deleteTerrainUser(id);
}

QList<TerrainUser> Controller::prepareCustomTerrainUserFromAclList(int i){

    if(!noDbMode){
        QString id =((Acl)aclList.at(i)).getId();
        return dbConnection->getTerrainUsersFromAcl(id);
    } else{
       QList<TerrainUser> list;
       TerrainUser t("","","","","","");
       t.setJid("terrainuser5@jabber.cz");
       list.append(t);
       return list;
    }

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

int Controller::getPolygonCoordinatesNum(){
    qDebug()<<"poly SIZE"<<polygonVector.size();
    return polygonVector.size();
}

double Controller::getPolygonCoordinateLatAt(int i){

    return polygonVector.at(i).x();



}

double Controller::getPolygonCoordinateLonAt(int i){

    double y=polygonVector.at(i).y();


    if(i==polygonVector.size()-1){

        polygonVector.clear();
        addPolygonFromDB();
    }

    return y;

}

QVariant Controller::findObjectUnderCursor(double lat, double lon){

    QString id=dbConnection->getPointIdAtCoordinates(lat,lon);

    if(id=="-1"){
        id=dbConnection->getLineIdAtCoordinates(lat,lon);
    }

    if(id=="-1"){
        id=dbConnection->getPolygonIdAtCoordinates(lat,lon);
    }


    MapObject obj=mapObjectMap->value(id);

    return obj.getPaintedObject();
}

void Controller::getCaptchaRegistrationUrl(QString captcha){

    this->captcha=captcha;
    emit captchaReady();

}

QString Controller::getCaptchaUrl(){
    return this->captcha;
}

void Controller::prepareRegistration(){
    registrationTool->connectToServer();
}

void Controller::registerUser(QString name, QString password, QString captcha){
    registrationTool->registerUser(name,password,captcha);
}

void Controller::getError(QString error){
    this->errorMessage=error;
    qDebug()<<"errorget";
    emit registrationError();
}

QString Controller::getErrorMessage(){
    return this->errorMessage;
}

void Controller::getSuccess(){
    emit registrationSuccess();
}

void Controller::stopRegistration(){
    registrationTool->closeStream();
}

void Controller::makeRosterForUser(QString jid, QString password){
    QStringList jidList=dbConnection->getAllJids();


    QXmppConfiguration config;

    config.setJid(jid);
    config.setPassword(password);
    config.setAutoAcceptSubscriptions(true);

    cl.connectToServer(config);
    cl.startSubscribingToUsers(jidList);

}

void Controller::addNoteTo(QString name, QString text, QString id){
    QString dbId=dbConnection->insertOrUpdateNote(id, name, text);

    if(dbId!="-1" || noDbMode){

        QLandmarkNameFilter filter;
        filter.setName(id);
        QList<QLandmark> lms=landMan->landmarks(filter);
        if(lms.length()>0){
           // fixMapBug();
            // QLandmarkId id=lms.first().landmarkId();

            QLandmark lm=lms.first();
            lm.setPhoneNumber(name+"////"+text);

            landMan->saveLandmark(&lm);




        } else{
            qDebug()<<"didnt find landmark for note - error";
        }

    }

    MapObject obj=mapObjectMap->value(id);
    QList<TerrainUser> userList= dbConnection->getTerrainUsersFromAcl(obj.getAClId());
    emit sendNote(Note(name,text,id),userList);




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

void Controller::getOutdatedObjects(QStringList mapObjects){


    prepareAclList();

    qDebug()<<"got invalids"<<mapObjects.length();
    foreach(QString name, mapObjects){
        QLandmarkNameFilter filter;
        filter.setName(name);
        QList<QLandmark> lms=landMan->landmarks(filter);
        if(lms.length()>0){
            qDebug()<< landMan->removeLandmark(lms.at(0));
            qDebug()<< landMan->error()<<landMan->errorString();

            MapObject obj=mapObjectMap->value(name);
            QString aclId=obj.getAClId();
            QList<TerrainUser> userList= dbConnection->getTerrainUsersFromAcl(aclId);

            emit sendNegativeObject(name,userList);

        }


    }


}

void Controller::setZoomRatio(int zoom){
    dbConnection->setZoomRatio(zoom);
}

QString Controller::getAclNameForUserAt(int i){
    QString id=((TerrainUser)terrainUserList.at(i)).getId();

    return dbConnection->getAclNameForUser(id);
}

void Controller::getUserAclUpdated(){
    emit userAclUpdated();
}

void Controller::sendMessageToUserAt(QString message, int i){

    if(i!=-1){
        QString jid=((TerrainUser)terrainUserList.at(i)).getJid();

        DataPreparator *preparator=new DataPreparator(this);
        QString newMessage=preparator->prepareMessage(message);
        delete preparator;

        emit sendMessage(newMessage,jid);





    }
}

void Controller::setCurrentUser(QString currentUser){
    this->currentUser=currentUser;
}

QString Controller::getCurrentDateTime(){
    QDateTime t=QDateTime::currentDateTime();
    QString outputFormat="hh:mm:ss";
    return t.toString(outputFormat);

}

void Controller::getReceivedMessage(QString message, QString jid){
    dbConnection->saveReceivedMessage(message,jid,currentUser);
    int i=0;
    int j=-1;
    foreach(TerrainUser u, terrainUserList){
        if(u.getJid()==jid){
            j=i;
            break;
        }

        i++;
    }


    if(j!=-1){


        QString line=getCurrentDateTime();
        line+=" ";
        line+=jid.split("@").at(0);
        line+=": ";
        line+=message;

        emit newMessageFromUserAt(j, line);
    }

}

void Controller::setSentMessage(QString message, int i){
    if(i!=-1){
        QString jid=((TerrainUser)terrainUserList.at(i)).getJid();
        dbConnection->saveSentMessage(message,jid,currentUser);
    }
}


void Controller::prepareMessageList(int i){
    messageList.clear();

    QString id=((TerrainUser)terrainUserList.at(i)).getId();
    QString username=((TerrainUser)terrainUserList.at(i)).getUsername();
    QList<Message> messList=dbConnection->getMessagesFor(id,currentUser);
    foreach(Message m,messList){

        QString line=m.getTime().split("T").at(1);
        line+=" ";

        if(m.getReceived()){
            line+=username;//the message was received
            line+=": ";
        } else {
            line+="Me: ";//the message was sent
        }

        line+=m.getText();

       this->messageList.append(line);
    }


    emit messagesReady();
}

int Controller::getMessagesNum(){
    return messageList.length();
}

QString Controller::getMessageLineAt(int i){
    return messageList.at(i);
}
