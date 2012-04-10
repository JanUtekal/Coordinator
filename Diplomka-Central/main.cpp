#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QDeclarativeContext>
#include <QtDeclarative>

#include "controller.h"
#include <QLandmarkManager>
#include <QLandmark>
#include <QLandmarkManagerEngine>
#include <qlandmarkmanager.h>
#include <QSqlDatabase>


#include "xmppClient.h"
#include "QXmppLogger.h"
#include "extension.h"

#include "QXmppStream.h"

#define USERNAME "centraluser1@jabber.cz"

#define PASSWORD "asasasd"
#define PATH ""

bool createConnection(Controller *cont)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgis");
    db.setUserName("postgres");
    db.setPassword("asd");
    if (!db.open()) {
        qDebug()<<"connection error";
        return false;
    }

    cont->createDb(db);
    return true;
}

void eraseFile(){
    QString path=PATH;
    path+="QXmppClientLog.log";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out<< "";
    file.close();
}


int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    Controller cont;

    if (!createConnection(&cont)){
        return 1;
    }

    QmlApplicationViewer viewer;

    eraseFile();




    viewer.rootContext()->setContextProperty("cont", &cont);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/DiplomkaCentral/main.qml"));


    XmppClient client;
    Extension ex;
    client.addExtension(&ex);
    QObject::connect(&ex, SIGNAL(sendCoords(QString,QString,QString,QString)),&client,SLOT(getNewCoords(QString, QString, QString, QString)));

      //  QXmppDiscoveryManager m;
      //  m.setClientCapabilitiesNode("geoloc") ;



    QObject *object = viewer.rootObject();
    cont.getRootObject(object);

    viewer.showExpanded();



    QObject::connect(&client,SIGNAL(refresh(QList<QLandmark>*)),&cont,SLOT(getConnectedUsers(QList<QLandmark>*)));
    QObject::connect(&client,SIGNAL(updateUser(QString,QGeoCoordinate)),&cont,SLOT(updateUserPosition(QString,QGeoCoordinate)));
    QObject::connect(&client,SIGNAL(setUserOffline(QString)),&cont,SLOT(setUserOffline(QString)));



    QObject::connect(&cont,SIGNAL(sendObjects(QList<QLandmark>*)),&client,SLOT(sendObjectsToUsers(QList<QLandmark>*)));
    QObject::connect(&cont,SIGNAL(test()),&client,SLOT(sendMess()));
    QObject::connect(&cont,SIGNAL(subscribeToUser(QString)),&client,SLOT(subscribeToUser(QString)));
    QObject::connect(&cont,SIGNAL(sendMapObject(QString,QList<TerrainUser>)),&client,SLOT(sendObjectToUsers(QString,QList<TerrainUser>)));

    QObject::connect(&cont,SIGNAL(disconnectUser()),&client,SLOT(disconnectFromServer()));


    QObject::connect(&cont,SIGNAL(subscribeToLocation(QString)),&client,SLOT(subscribeLocation(QString)));
    QObject::connect(&cont,SIGNAL(sendNote(Note,QList<TerrainUser>)),&client,SLOT(sendNoteToUsers(Note,QList<TerrainUser>)));
    QObject::connect(&cont,SIGNAL(sendNegativeObject(QString,QList<TerrainUser>)),&client,SLOT(sendNegativeObjectToUsers(QString,QList<TerrainUser>)));


    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::FileLogging);
    QXmppLogger::getLogger()->setMessageTypes(QXmppLogger::AnyMessage);
  //  client.connectToServer(USERNAME, PASSWORD);
    QXmppConfiguration config;
    config.setJid(USERNAME);
    config.setPassword(PASSWORD);
    config.setAutoAcceptSubscriptions(true);
   // config.setIgnoreAuth(true);
    client.connectToServer(config);

/*
    QXmppIq iq;
        iq.setTo("jabber.org");
       // iq.setFrom("pokusnfhg1@jabber.cz");
        iq.setType(QXmppIq::Get);
      //  iq.setQueryNode("jabber:iq:register");
     //   iq.setItems(items);
        QXmppElement query;
        query.setTagName("query");
        query.setAttribute("xmlns","jabber:iq:register");

        QXmppElementList elList;
        elList.append(query);



        iq.setExtensions(elList);

        QXmppConfiguration config;
        //config.setDomain("jabber.cz");
        config.setHost("jabber.cz");
       //config.setIgnoreAuth(true);
       config.setIgnoreSslErrors(true);
     //  config.set
        //config.setJid("");
        //config.setPassword("");
        client.connectToServer(config);
*/
 //   QObject::connect(&cont, SIGNAL(aclListReady()),&object,SLOT())

   // client.findExtension<QXmppDiscoveryManager>()->setClientCapabilitiesNode ("http://jabber.org/protocol/geoloc+notify");;
    return app->exec();
}
