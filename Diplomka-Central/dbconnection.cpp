#include "dbconnection.h"

#define CURRENTCENTRALUSER 1

DbConnection::DbConnection(QObject *parent) :
    QObject(parent)
{

    zoomRadius=100;
}

void DbConnection::setDb(QSqlDatabase db){
    this->db=db;

    qDebug()<<"db set";

    getObjectsFromDB();


}



QString DbConnection::generateNowAndUntil(int validity){
    QDateTime dt=QDateTime::currentDateTime();
    QString outputFormat="yyyy-MM-dd hh:mm:ss";
    return "'"+dt.toString(outputFormat)+"'"+", "+"'"+dt.addSecs(validity*3600).toString(outputFormat)+"'";
}

int DbConnection::insertPoint(double lat, double lon, QString acl){

    int insertedId=-1;

    QSqlQuery query(db);

    QString q;

    if(acl!="-1"){
        q=QString("INSERT INTO point (coordinates, acl) VALUES (ST_GeographyFromText('SRID=4326;POINT(%1 %2)'), %3) RETURNING id").arg(lon).arg(lat).arg(acl);

    } else {
        q=QString("INSERT INTO point (coordinates) VALUES (ST_GeographyFromText('SRID=4326;POINT(%1 %2)')) RETURNING id").arg(lon).arg(lat);

    }

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        //  int id = query.value(0).toInt();
        //  QString name= query.value(1).toString();

        qDebug()<<query.value(0).toInt();

        insertedId=query.value(0).toInt();
    }

    return insertedId;
}

int DbConnection::deleteObject(QString id){

    QSqlQuery query(db);

    QString q=QString("DELETE FROM mapobject WHERE id=%1").arg(id);

    query.prepare(q);



    if(query.exec()){
        return 0;
    }

    qDebug()<<query.executedQuery();

    return -1;

}

int DbConnection::insertLine(QVector<QPointF> lineVector, QString acl){
    int insertedId=-1;

    QSqlQuery query(db);

    QString q;

    if(acl!="-1"){
        q=QString("INSERT INTO line (coordinates, acl) VALUES (ST_GeographyFromText('SRID=4326;LINESTRING(");

    } else {
        q=QString("INSERT INTO line (coordinates) VALUES (ST_GeographyFromText('SRID=4326;LINESTRING(");
    }


    int i=0;
    foreach(QPointF point, lineVector){
        i++;
        q+=QString::number(point.y());
        q+=" ";
        q+=QString::number(point.x());

        if(i<lineVector.size()){
            q+=",";
        }
    }

    if(acl!="-1"){
        q+=QString(")'), %1) RETURNING id").arg(acl);
    } else {
        q+=QString(")')) RETURNING id");
    }

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        //  int id = query.value(0).toInt();
        //  QString name= query.value(1).toString();

        qDebug()<<query.value(0).toInt();

        insertedId=query.value(0).toInt();
    }

    return insertedId;
}

int DbConnection::insertPolygon(QVector<QPointF> polygonVector, QString acl){
    int insertedId=-1;

    QSqlQuery query(db);

    QString q;

    if(acl!="-1"){
        q=QString("INSERT INTO polygon (coordinates,acl) VALUES (ST_GeographyFromText('SRID=4326;POLYGON((");
    } else {
        q=QString("INSERT INTO polygon (coordinates) VALUES (ST_GeographyFromText('SRID=4326;POLYGON((");
    }




    int i=0;
    foreach(QPointF point, polygonVector){
        i++;
        q+=QString::number(point.y());
        q+=" ";
        q+=QString::number(point.x());
        q+=",";

    }
    QPointF closingPoint=polygonVector.at(0);
    q+=QString::number(closingPoint.y());
    q+=" ";
    q+=QString::number(closingPoint.x());

    if(acl!="-1"){
        q+=QString("))'),%1) RETURNING id").arg(acl);
    } else {
        q+=QString("))')) RETURNING id");
    }


    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        //  int id = query.value(0).toInt();
        //  QString name= query.value(1).toString();

        qDebug()<<query.value(0).toInt();

        insertedId=query.value(0).toInt();
    }

    return insertedId;
}

QString DbConnection::insertOrUpdateNote(QString mapObjectId, QString name, QString text){
    QString insertedId="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM note WHERE mapobject=%1").arg(mapObjectId);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {

        insertedId=query.value(0).toString();
    }

    QString nId="-1";

    if(insertedId=="-1"){
        nId=insertNote(mapObjectId,name,text);
    } else {
        nId=updateNote(insertedId,name,text);
    }

    return nId;
}

QString DbConnection::insertNote(QString mapObjectId, QString name, QString text){
    QString insertedId="-1";

    QSqlQuery query(db);

    QString q=QString("INSERT INTO note (name, text,mapobject) VALUES ('%1','%2', %3) RETURNING id").arg(name).arg(text).arg(mapObjectId);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {

        insertedId=query.value(0).toString();
    }

    return insertedId;
}

QString DbConnection::updateNote(QString noteId, QString name, QString text){
    QString dbId="-1";

    QSqlQuery query(db);

    QString q=QString("UPDATE note SET name='%2', text='%3' WHERE id=%1 RETURNING id").arg(noteId).arg(name).arg(text);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    if(query.next()){
       dbId = query.value(0).toString();
    }



    return dbId;
}


void DbConnection::getObjectsFromDB(){

    QList<QLandmark> *dbLandmarks = new QList<QLandmark>();

    QSqlQuery query(db);

    //point query
    QString q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM point WHERE acl IN (SELECT id FROM acl WHERE validity = true)");

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("POINT")){

            double lon=location.split(" ").at(0).split("(").at(1).toDouble();
            double lat=location.split(" ").at(1).split(")").at(0).toDouble();


            QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);

            //qDebug()<<lat<< lon<<coordinate.latitude();

            lm.setCoordinate(coordinate);
        }



        dbLandmarks->append(lm);

    }

    emit sendAllPoints(dbLandmarks);



    //line query
    QList<QLandmark> *dbLandmarks2 = new QList<QLandmark>();
    q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM line WHERE acl IN (SELECT id FROM acl WHERE validity = true)");
    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        //qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("LINESTRING")){

            QString coords=location.remove(0,11);//=location.split("LINESTRING(").
            coords.chop(1);

    //  qDebug()<<coords;
            lm.setDescription(coords);
            lm.setRadius(10);
            //QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);


          //  lm.setCoordinate(coordinate);
        }

        dbLandmarks2->append(lm);

    }


    qDebug()<<"sending";

    emit sendAllLines(dbLandmarks2);



    //line query
    QList<QLandmark> *dbLandmarks3 = new QList<QLandmark>();
    q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM polygon WHERE acl IN (SELECT id FROM acl WHERE validity = true)");
    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        //qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("POLYGON")){

            QString coords=location.remove(0,9);//=location.split("LINESTRING(").
            coords.chop(2);

    //  qDebug()<<coords;
            lm.setDescription(coords);
            lm.setRadius(20);
            //QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);


          //  lm.setCoordinate(coordinate);
        }

        dbLandmarks3->append(lm);

    }


    qDebug()<<"sending polys"<<dbLandmarks3->length();

    emit sendAllPolygons(dbLandmarks3);






}

QString DbConnection::getLastObjectIdFor(QString jid){

    QSqlQuery query(db);

    QString q=QString("SELECT lastobject FROM terrainuser WHERE jid=\'%1\'").arg(jid);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    QString id="0";

    while (query.next()) {
        id = query.value(0).toString();

    }
    return id;
}

QList<QLandmark> DbConnection::getMapObjectsNotSentFor(QString jid){
    QString id=getLastObjectIdFor(jid);

    //  qDebug()<<id;

    QList<QLandmark> dbLandmarks;


    QSqlQuery query(db);

    QString q=QString("SELECT id, ST_AsText(coordinates::geometry) FROM point WHERE id>%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();




    QString lastId;

    bool hadNext=false;

    while (query.next()) {
        hadNext=true;

        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("POINT")){

            double lon=location.split(" ").at(0).split("(").at(1).toDouble();
            double lat=location.split(" ").at(1).split(")").at(0).toDouble();


            QGeoCoordinate coordinate(lat,lon);


           // qDebug()<<lat<< lon<<coordinate.latitude();

            lm.setCoordinate(coordinate);
        }

        dbLandmarks.append(lm);

        lastId=id;//nastavuje se posledni ziskane id

    }

    if(hadNext){
        updateTerrainUserLastObject(jid,lastId);//nastavuje se nova hodnota pro posledni odeslany objekt
    }

    return dbLandmarks;

}

void DbConnection::updateTerrainUserLastObject(QString jid, QString id){
    QSqlQuery query(db);

    QString q=QString("UPDATE terrainuser SET lastobject=%1 WHERE jid=\'%2'").arg(id).arg(jid);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

void DbConnection::insertTerrainUser(QString id, QString name, QString surname, QString jid, QString password){

    QSqlQuery query(db);

    QString q=QString("INSERT INTO terrainuser (id, name, surname, jid, password, lastobject) VALUES (%1, \'%2\', \'%3\', \'%4\', \'%5\', 0)").arg(id).arg(name).arg(surname).arg(jid).arg(password);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

}

void DbConnection::insertAcl(QString name, QString currentCentralUser, int validity){
    QSqlQuery query(db);

    QString q=QString("INSERT INTO acl (name, centraluser, insertiontime, validuntil) VALUES (\'%1\', %2, %3)").arg(name).arg(currentCentralUser).arg(generateNowAndUntil(validity));

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

}

QList<Acl> DbConnection::getAllAcls(){


    QList<Acl> aclList;

    QSqlQuery query(db);

    QString q=QString("SELECT id,name FROM acl");

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();

        Acl acl(id,name);

        aclList.append(acl);

    }
    qDebug()<<"acl list length"<<aclList.length();
    return aclList;

}

QList<Acl> DbConnection::getValidAcls(){




    QList<Acl> aclList;

    QSqlQuery query(db);

    QString q=QString("SELECT id,name FROM acl WHERE validity = true");

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();

        Acl acl(id,name);

        aclList.append(acl);

    }
    qDebug()<<"acl list length"<<aclList.length();
    return aclList;

}

QList<TerrainUser> DbConnection::getAllTerrainUsers(){


    QList<TerrainUser> terrainUserList;

    QSqlQuery query(db);

    QString q=QString("SELECT id,name,surname, password, jid FROM terrainuser ORDER BY name");

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();
        QString surname= query.value(2).toString();
        QString password= query.value(3).toString();
        QString jid=query.value(4).toString();

        QString username=jid.split("@").at(0);
        QString server=jid.split("@").at(1);
        TerrainUser user(id,name,surname, password, username,server);

        terrainUserList.append(user);

    }

    return terrainUserList;

}

QList<TerrainUser> DbConnection::getTerrainUsersFromAcl(QString id){


    QList<TerrainUser> terrainUserList;

    QSqlQuery query(db);

    QString q=QString("SELECT id, name, surname, password, jid FROM terrainuser WHERE id IN (SELECT terrainuserid FROM terrainuseracl WHERE aclid=%1)").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();
        QString surname= query.value(2).toString();
        QString password= query.value(3).toString();
        QString jid=query.value(4).toString();
        QString username=jid.split("@").at(0);
        QString server=jid.split("@").at(1);
        TerrainUser user(id, name, surname, password, username, server);


        terrainUserList.append(user);

    }

    return terrainUserList;

}

void DbConnection::updateTerrainUserAcl(QString idUser, QString idAcl){
    QString updatedAclId;

    QSqlQuery query(db);


    QString q=QString("SELECT id FROM acl WHERE id=(SELECT aclid FROM terrainuseracl WHERE terrainuserid=%1 AND validity=true)").arg(idUser);
    query.prepare(q);

    qDebug()<< query.exec()<<query.executedQuery();

    bool hasValidAcl=false;

    if(query.next()){
        hasValidAcl=true;
        updatedAclId=query.value(0).toString();
    }

    if(hasValidAcl){
        QSqlQuery query(db);

        QString q=QString("UPDATE terrainuseracl SET aclid=%1 WHERE terrainuserid=%2 AND aclid=%3").arg(idAcl).arg(idUser).arg(updatedAclId);

        query.prepare(q);

        qDebug()<< query.exec()<<query.executedQuery();
    } else {
        QSqlQuery query(db);

        QString q=QString("INSERT INTO terrainuseracl (terrainuserid, aclid) VALUES (%1, %2)").arg(idUser).arg(idAcl);

        query.prepare(q);

        qDebug()<< query.exec()<<query.executedQuery();
    }






}

void DbConnection::deleteAcl(QString id){
    this->removeUserPositionsForAcl(id);

    this->deleteTerrainUserAcl("",id);

    QList<TerrainUser> terrainUserList=this->getTerrainUsersFromAcl(id);

    foreach(TerrainUser user, terrainUserList){

        this->updateTerrainUserAcl(user.getId(),"NULL");
    }

    QSqlQuery query(db);

    QString q=QString("DELETE FROM acl WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

void DbConnection::deleteTerrainUser(QString id){

    this->removeUserPositionsForUser(id);

    this->deleteTerrainUserAcl(id,"");

    QSqlQuery query(db);

    QString q=QString("DELETE FROM terrainuser WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

void DbConnection::deleteTerrainUserAcl(QString terrainuserId, QString aclId){

    QSqlQuery query(db);

    QString q;

    if(terrainuserId.length()>0){
        q=QString("DELETE FROM terrainuseracl WHERE terrainuserid=%1").arg(terrainuserId);
    }

    if(aclId.length()>0){
        q=QString("DELETE FROM terrainuseracl WHERE aclid=%1").arg(aclId);
    }

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

QString DbConnection::getPolygonIdAtCoordinates(double lat, double lon){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM polygon AS pol WHERE St_DWithin(pol.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'),1) AND (acl IN (SELECT id FROM acl WHERE validity = true)) ORDER BY ST_Distance(pol.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat);

    query.prepare(q);



    //qDebug()<< query.exec()<<query.executedQuery();

    query.exec();
    query.executedQuery();


    if(query.next()){
       id = query.value(0).toString();
    }



    return id;
}

QString DbConnection::getLineIdAtCoordinates(double lat, double lon){

    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM line AS lin where ST_Distance(lin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))<%3 AND (acl IN (SELECT id FROM acl WHERE validity = true)) ORDER BY ST_Distance(lin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat).arg(zoomRadius);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    query.exec();
    query.executedQuery();

    if(query.next()){
       id = query.value(0).toString();
    }



    return id;
}

QString DbConnection::getPointIdAtCoordinates(double lat, double lon){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM point AS poin where ST_Distance(poin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))<%3 AND (acl IN (SELECT id FROM acl WHERE validity = true)) ORDER BY ST_Distance(poin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat).arg(zoomRadius*3);

    query.prepare(q);



  //  qDebug()<< query.exec()<<query.executedQuery();

    query.exec();
    query.executedQuery();

    if(query.next()){
       id = query.value(0).toString();
    }



    return id;
}

QStringList DbConnection::getAllJids(){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT jid FROM terrainuser UNION SELECT jid FROM centraluser");

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    QStringList jidList;

    while(query.next()){
       QString jid = query.value(0).toString();
       jidList.append(jid);
    }



    return jidList;
}

QPair<QString, QString> DbConnection::getNoteForMapObject(QString id){

    QSqlQuery query(db);

    QString q=QString("SELECT name, text FROM note as n WHERE n.mapobject=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    QString name;
    QString text;

    while(query.next()){
       name=query.value(0).toString();
       text=query.value(1).toString();
    }

    return QPair<QString,QString>(name,text);

}

int DbConnection::deleteNote(QString id){

    QSqlQuery query(db);

    QString q=QString("DELETE FROM note WHERE mapobject=%1").arg(id);

    query.prepare(q);



    if(query.exec()){
        return 0;
    }

    qDebug()<<query.executedQuery();

    return -1;

}

QString DbConnection::getMapObjectAcl(QString mapObjectId){
    QString acl="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT acl FROM mapobject WHERE id=%1").arg(mapObjectId);

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();


    while(query.next()){
        acl=query.value(0).toString();
    }

    return acl;
}

void DbConnection::validateMapObjects(){

    this->invalidateAcls();

    QStringList ids;

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM mapobject WHERE acl IN (SELECT id FROM acl WHERE validuntil > (SELECT lastvalidation FROM centraluser WHERE id=%1) AND validity=false)").arg(CURRENTCENTRALUSER);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



    while(query.next()){
        ids.append(query.value(0).toString());

    }

    updateUserAcls();
    updateCentraluserLastValidation(getNow());
    emit sendOutdatedObjects(ids);


}

void DbConnection::updateCentraluserLastValidation(QString lastValidation){
    QSqlQuery query(db);

    QString q=QString("UPDATE centraluser SET lastvalidation=('%1') WHERE id=%2").arg(lastValidation).arg(CURRENTCENTRALUSER);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



}

QString DbConnection::getNow(){
    QDateTime dt=QDateTime::currentDateTime();
    QString outputFormat="yyyy-MM-dd hh:mm:ss";
    return dt.toString(outputFormat);
}

void DbConnection::insertUserPosition(QString jid, double lat, double lon){
    QSqlQuery query(db);

    QString q=QString("INSERT INTO userposition (terrainuser, useracl, coordinates, time) VALUES ((SELECT id FROM terrainuser WHERE jid='%1'), (SELECT aclid FROM terrainuseracl WHERE terrainuserid=(SELECT id FROM terrainuser WHERE jid='%1') AND validity=true), ST_GeographyFromText('SRID=4326;POINT(%2 %3)'), '%4')").arg(jid).arg(lon).arg(lat).arg(getNow());

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();



}

void DbConnection::setZoomRatio(int zoom){


    zoomRadius=100/pow(2,(zoom-14));
}

QString DbConnection::getAclNameForUser(QString id){
    QString name;



    QSqlQuery query(db);

    QString q=QString("SELECT name FROM acl AS a WHERE a.id=(SELECT aclid FROM terrainuseracl WHERE terrainuserid=%1 AND validity=true)").arg(id);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



    while(query.next()){
        name=query.value(0).toString();

    }

    return name;
}

QStringList DbConnection::getInvalidAcls(){
    QStringList ids;


    QString now=getNow();
    QSqlQuery query(db);

    QString q=QString("SELECT id FROM acl WHERE id IN (SELECT id FROM acl WHERE validuntil > (SELECT lastvalidation FROM centraluser WHERE id=%1) AND validity=false)").arg(CURRENTCENTRALUSER);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



    while(query.next()){
        ids.append(query.value(0).toString());

    }

    return ids;
}

void DbConnection::updateUserAcls(){
    bool wasUpdated=false;
    QStringList invalidAcls=this->getInvalidAcls();
    qDebug()<<invalidAcls.length()<<"invalidacls";
    foreach(QString aclId, invalidAcls){
        QList<TerrainUser> terrainUserList=this->getTerrainUsersFromAcl(aclId);
        qDebug()<<terrainUserList.length()<<"userlist";
        foreach(TerrainUser user, terrainUserList){
            wasUpdated=true;
            this->updateTerrainUserAcl(user.getId(),"NULL");
        }
    }
    if(wasUpdated){
        emit userAclUpdated();
    }
}

void DbConnection::removeUserPositionsForAcl(QString id){
    QSqlQuery query(db);

    QString q=QString("DELETE FROM userposition WHERE useracl=%1").arg(id);

    query.prepare(q);





    qDebug()<< query.exec()<<query.executedQuery();

}

void DbConnection::removeUserPositionsForUser(QString id){
    QSqlQuery query(db);

    QString q=QString("DELETE FROM userposition WHERE terrainuser=%1").arg(id);

    query.prepare(q);





    qDebug()<< query.exec()<<query.executedQuery();

}

int DbConnection::saveReceivedMessage(QString message, QString jid, QString currentUserJid){


    QSqlQuery query(db);

    QString q=QString("INSERT INTO message (text, terrainuser, centraluser, time, received) VALUES ('%1', (SELECT id FROM terrainuser WHERE jid='%2'), (SELECT id FROM centraluser WHERE jid='%3'), '%4', %5 )").arg(message).arg(jid).arg(currentUserJid).arg(getNow()).arg("true");


    query.prepare(q);



    qDebug()<<query.executedQuery();
    if(query.exec()){
        return 0;
    }

    return -1;
}

int DbConnection::saveSentMessage(QString message, QString jid, QString currentUserJid){


    QSqlQuery query(db);

    QString q=QString("INSERT INTO message (text, terrainuser, centraluser, time, received) VALUES ('%1', (SELECT id FROM terrainuser WHERE jid='%2'), (SELECT id FROM centraluser WHERE jid='%3'), '%4', %5 )").arg(message).arg(jid).arg(currentUserJid).arg(getNow()).arg("false");


    query.prepare(q);



    qDebug()<<query.executedQuery();
    if(query.exec()){
        return 0;
    }

    return -1;
}

QList<Message> DbConnection::getMessagesFor(QString terrainUserId, QString centralUserName){
    QList<Message> messages;

    QDateTime dt=QDateTime::currentDateTime();
    QString outputFormat="yyyy-MM-dd hh:mm:ss";
    QString beforeHour= dt.addSecs(-7200).toString(outputFormat);

    QSqlQuery query(db);

    QString q=QString("SELECT text, time, received FROM message WHERE terrainuser=%1 AND centraluser=(SELECT id FROM centraluser WHERE jid='%2') AND time > '%3'").arg(terrainUserId).arg(centralUserName).arg(beforeHour);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



    while(query.next()){
        QString text=query.value(0).toString();
        QString time=query.value(1).toString();
        bool recv=query.value(2).toBool();
        Message mess(text,time,recv);
        messages.append(mess);
    }

    return messages;
}

void DbConnection::invalidateAcls(){
    QStringList slist;

    QSqlQuery query(db);//

    QString q=QString("SELECT id FROM acl WHERE validuntil > (SELECT lastvalidation FROM centraluser WHERE id=%1) AND validuntil < '%2'").arg(CURRENTCENTRALUSER).arg(getNow());



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while(query.next()){
        QString id=query.value(0).toString();
        slist.append(id);
    }

    foreach(QString id, slist){
        QString q=QString("UPDATE acl SET validity=false WHERE id=%1").arg(id);



        query.prepare(q);


        qDebug()<< query.exec()<<query.executedQuery();

        this->invalidateTerrainUserAcl(id);

    }

    if(slist.length()>0){
        emit userAclUpdated();
    }
}

void DbConnection::invalidateTerrainUserAcl(QString aclid){
    QString q=QString("UPDATE terrainuseracl SET validity=false WHERE aclid=%1").arg(aclid);


    QSqlQuery query(db);//
    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();


}

QList<Acl> DbConnection::getAclsBetweenDates(QDateTime from, QDateTime to){


    QList<Acl> aclList;

    QSqlQuery query(db);

    QString q=QString("SELECT id, name, insertiontime, validuntil FROM acl WHERE insertiontime > '%1' AND validuntil < '%2' ORDER BY insertiontime").arg(getDate(from)).arg(getDate(to));

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();

        Acl acl(id,name);

        acl.setFrom(query.value(2).toString());
        acl.setTo(query.value(3).toString());

        aclList.append(acl);

    }
    qDebug()<<"acl list length"<<aclList.length();
    return aclList;

}

QString DbConnection::getDate(QDateTime date){

    QString outputFormat="yyyy-MM-dd hh:mm:ss";
    return date.toString(outputFormat);
}

QList<Message> DbConnection::getMessagesForBetweenDates(QString terrainUserIdo, QString aclId){
    QList<Message> messages;

    QSqlQuery query(db);

    QString q=QString("SELECT text, time, received, (SELECT jid from centraluser WHERE id=message.centraluser) FROM message WHERE terrainuser=%1 AND time > (SELECT insertiontime FROM acl WHERE id =%2) AND time < (SELECT validuntil FROM acl WHERE id =%2) ORDER BY time").arg(terrainUserIdo).arg(aclId);



    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();



    while(query.next()){
        QString text=query.value(0).toString();
        QString time=query.value(1).toString();
        bool recv=query.value(2).toBool();
        QString centralUser=query.value(3).toString();
        Message mess(text,time,recv);
        mess.setCentralUser(centralUser);
        messages.append(mess);
    }

    return messages;
}

void DbConnection::getObjectsFromDBForAcl(QString id){

    QList<QLandmark> *dbLandmarks = new QList<QLandmark>();

    QSqlQuery query(db);

    //point query
    QString q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM point WHERE acl=%1").arg(id);

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("POINT")){

            double lon=location.split(" ").at(0).split("(").at(1).toDouble();
            double lat=location.split(" ").at(1).split(")").at(0).toDouble();


            QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);

            //qDebug()<<lat<< lon<<coordinate.latitude();

            lm.setCoordinate(coordinate);
        }



        dbLandmarks->append(lm);

    }

    emit sendAllPoints(dbLandmarks);



    //line query
    QList<QLandmark> *dbLandmarks2 = new QList<QLandmark>();
    q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM line WHERE acl=%1").arg(id);

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        //qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("LINESTRING")){

            QString coords=location.remove(0,11);//=location.split("LINESTRING(").
            coords.chop(1);

    //  qDebug()<<coords;
            lm.setDescription(coords);
            lm.setRadius(10);
            //QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);


          //  lm.setCoordinate(coordinate);
        }

        dbLandmarks2->append(lm);

    }


    qDebug()<<"sending";

    emit sendAllLines(dbLandmarks2);



    //line query
    QList<QLandmark> *dbLandmarks3 = new QList<QLandmark>();
    q=QString("SELECT id,ST_AsText(coordinates::geometry) FROM polygon WHERE acl=%1").arg(id);

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString location= query.value(1).toString();

        //qDebug()<<id<<location;

        QLandmark lm;
        lm.setName(id);

        if(location.contains("POLYGON")){

            QString coords=location.remove(0,9);//=location.split("LINESTRING(").
            coords.chop(2);

    //  qDebug()<<coords;
            lm.setDescription(coords);
            lm.setRadius(20);
            //QGeoCoordinate coordinate(lat,lon);

            QPair<QString, QString> note=getNoteForMapObject(id);
            lm.setPhoneNumber(note.first+"////"+note.second);


          //  lm.setCoordinate(coordinate);
        }

        dbLandmarks3->append(lm);

    }


    qDebug()<<"sending polys"<<dbLandmarks3->length();

    emit sendAllPolygons(dbLandmarks3);






}

QLandmark DbConnection::getTrajectoryForUserInAcl(QString userId, QString aclId){

    QLandmark lm;

    QSqlQuery query(db);

    //point query
    QString q=QString("SELECT ST_AsText(coordinates::geometry) FROM userposition WHERE terrainuser=%1 AND useracl=%2").arg(userId).arg(aclId);

    query.prepare(q);


    qDebug()<< query.exec()<<query.executedQuery();

    QString coordinates;

    while (query.next()) {

        QString location= query.value(0).toString();
qDebug()<<location;

        if(location.contains("POINT")){

            QString point = location.remove(0,6);
            point.chop(1);
            coordinates+=point;
            coordinates+=",";

        }

    }

    coordinates.chop(1);

    QString name="user";
    name+=userId;
    lm.setName(name);
    lm.setDescription(coordinates);
    lm.setRadius(15);
    lm.setPhoneNumber(name);

qDebug()<<coordinates;


   return lm;
}

void DbConnection::invalidateAcl(QString id){


    QSqlQuery query(db);

    QString q=QString("UPDATE acl SET validity=false WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();


}
