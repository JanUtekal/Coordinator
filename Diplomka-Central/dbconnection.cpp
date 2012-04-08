#include "dbconnection.h"

DbConnection::DbConnection(QObject *parent) :
    QObject(parent)
{


}

void DbConnection::setDb(QSqlDatabase db){
    this->db=db;

    qDebug()<<"db set";

    getObjectsFromDB();

}

int DbConnection::insertPoint(double lat, double lon){

    int insertedId=-1;

    QSqlQuery query(db);

    QString q=QString("INSERT INTO point (coordinates) VALUES (ST_GeographyFromText('SRID=4326;POINT(%1 %2)') ) RETURNING id").arg(lon).arg(lat);

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

int DbConnection::insertLine(QVector<QPointF> lineVector){
    int insertedId=-1;

    QSqlQuery query(db);

    QString q=QString("INSERT INTO line (coordinates) VALUES (ST_GeographyFromText('SRID=4326;LINESTRING(");

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

    q+=")')) RETURNING id";
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

int DbConnection::insertPolygon(QVector<QPointF> polygonVector){
    int insertedId=-1;

    QSqlQuery query(db);

    QString q=QString("INSERT INTO polygon (coordinates) VALUES (ST_GeographyFromText('SRID=4326;POLYGON((");

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
    q+="))')) RETURNING id";
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
    QString q=QString("SELECT id,ST_AsText(coordinates::geometry) from point");

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
    q=QString("SELECT id,ST_AsText(coordinates::geometry) from line");

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
    q=QString("SELECT id,ST_AsText(coordinates::geometry) from polygon");

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

void DbConnection::insertAcl(QString name, QString currentCentralUser){
    QSqlQuery query(db);

    QString q=QString("INSERT INTO acl (name, centraluser) VALUES (\'%1\', %2)").arg(name).arg(currentCentralUser);

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

QList<TerrainUser> DbConnection::getAllTerrainUsers(){


    QList<TerrainUser> terrainUserList;

    QSqlQuery query(db);

    QString q=QString("SELECT id,name,surname, password, jid FROM terrainuser");

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

    QString q=QString("SELECT id, name, surname, password, jid FROM terrainuser WHERE acl=%1").arg(id);

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

    QSqlQuery query(db);

    QString q=QString("UPDATE terrainuser SET acl=%1 WHERE id=%2").arg(idAcl).arg(idUser);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();


}

void DbConnection::deleteAcl(QString id){
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

    QSqlQuery query(db);

    QString q=QString("DELETE FROM terrainuser WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

QString DbConnection::getPolygonIdAtCoordinates(double lat, double lon){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM polygon AS pol where St_DWithin(pol.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'),1) ORDER BY ST_Distance(pol.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    if(query.next()){
       id = query.value(0).toString();
    }



    return id;
}

QString DbConnection::getLineIdAtCoordinates(double lat, double lon){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM line AS lin where ST_Distance(lin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))<100 ORDER BY ST_Distance(lin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    if(query.next()){
       id = query.value(0).toString();
    }



    return id;
}

QString DbConnection::getPointIdAtCoordinates(double lat, double lon){
    QString id="-1";

    QSqlQuery query(db);

    QString q=QString("SELECT id FROM point AS poin where ST_Distance(poin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))<500 ORDER BY ST_Distance(poin.coordinates, ST_GeographyFromText('SRID=4326;POINT(%1 %2)'))").arg(lon).arg(lat);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

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

