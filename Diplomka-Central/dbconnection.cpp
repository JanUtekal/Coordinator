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

int DbConnection::deletePoint(QString id){

    QSqlQuery query(db);

    QString q=QString("DELETE FROM point WHERE id=%1").arg(id);

    query.prepare(q);



    if(query.exec()){
        return 0;
    }

    qDebug()<<query.executedQuery();

    return -1;

}

void DbConnection::getObjectsFromDB(){

    QList<QLandmark> *dbLandmarks = new QList<QLandmark>();

    QSqlQuery query(db);

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


            qDebug()<<lat<< lon<<coordinate.latitude();

            lm.setCoordinate(coordinate);
        }

        dbLandmarks->append(lm);

    }
    qDebug()<<"sending";
    emit sendAllObjects(dbLandmarks);



}

QString DbConnection::getLastObjectIdFor(QString jid){

    QSqlQuery query(db);

    QString q=QString("SELECT lastobject FROM userterrain WHERE jid=\'%1\'").arg(jid);

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


            qDebug()<<lat<< lon<<coordinate.latitude();

            lm.setCoordinate(coordinate);
        }

        dbLandmarks.append(lm);

        lastId=id;//nastavuje se posledni ziskane id

    }

    if(hadNext){
        updateUserTerrainLastObject(jid,lastId);//nastavuje se nova hodnota pro posledni odeslany objekt
    }

    return dbLandmarks;

}

void DbConnection::updateUserTerrainLastObject(QString jid, QString id){
    QSqlQuery query(db);

    QString q=QString("UPDATE userterrain SET lastobject=%1 WHERE jid=\'%2'").arg(id).arg(jid);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

void DbConnection::insertTerrainUser(QString id, QString name, QString surname, QString jid, QString password){

    QSqlQuery query(db);

    QString q=QString("INSERT INTO userterrain (id, name, surname, jid, password, lastobject) VALUES (%1, \'%2\', \'%3\', \'%4\', \'%5\', 0)").arg(id).arg(name).arg(surname).arg(jid).arg(password);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

}

void DbConnection::insertAcl(QString name, QString currentCentralUser){
    QSqlQuery query(db);

    QString q=QString("INSERT INTO acl (name, usercentral) VALUES (\'%1\', %2)").arg(name).arg(currentCentralUser);

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

    return aclList;

}

QList<TerrainUser> DbConnection::getAllTerrainUsers(){


    QList<TerrainUser> terrainUserList;

    QSqlQuery query(db);

    QString q=QString("SELECT id,name,surname,jid FROM userterrain");

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();
        QString surname= query.value(2).toString();
        QString jid=query.value(3).toString();

        TerrainUser user(id,name,surname,jid);

        terrainUserList.append(user);

    }

    return terrainUserList;

}

QList<TerrainUser> DbConnection::getTerrainUsersFromAcl(QString id){


    QList<TerrainUser> terrainUserList;

    QSqlQuery query(db);

    QString q=QString("SELECT id, name, surname, jid FROM userterrain WHERE acl=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name= query.value(1).toString();
        QString surname= query.value(2).toString();
        QString jid=query.value(3).toString();

        TerrainUser user(id,name,surname,jid);

        terrainUserList.append(user);

    }

    return terrainUserList;

}

void DbConnection::updateUserTerrainAcl(QString idUser, QString idAcl){

    QSqlQuery query(db);

    QString q=QString("UPDATE userterrain SET acl=%1 WHERE id=%2").arg(idAcl).arg(idUser);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();


}

void DbConnection::deleteAcl(QString id){
    QList<TerrainUser> terrainUserList=this->getTerrainUsersFromAcl(id);

    foreach(TerrainUser user, terrainUserList){

        this->updateUserTerrainAcl(user.getId(),"NULL");
    }

    QSqlQuery query(db);

    QString q=QString("DELETE FROM acl WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}

void DbConnection::deleteTerrainUser(QString id){

    QSqlQuery query(db);

    QString q=QString("DELETE FROM userterrain WHERE id=%1").arg(id);

    query.prepare(q);



    qDebug()<< query.exec()<<query.executedQuery();
}
