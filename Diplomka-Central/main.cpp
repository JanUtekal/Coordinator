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


//#define USERNAME "H.a.n.s@jabber.cz"
#define USERNAME "asasasd@jabber.cz"
//#define PASSWORD "7145774"
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

    if (!createConnection(&cont)){
        return 1;
    }

    QObject::connect(&client,SIGNAL(refresh(QList<QLandmark>*)),&cont,SLOT(getConnectedUsers(QList<QLandmark>*)));
    QObject::connect(&client,SIGNAL(updateUser(QString,QGeoCoordinate)),&cont,SLOT(updateUserPosition(QString,QGeoCoordinate)));
    QObject::connect(&client,SIGNAL(setUserOffline(QString)),&cont,SLOT(setUserOffline(QString)));



    QObject::connect(&cont,SIGNAL(sendObjects(QList<QLandmark>*)),&client,SLOT(sendObjectsToUsers(QList<QLandmark>*)));



    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::FileLogging);
    QXmppLogger::getLogger()->setMessageTypes(QXmppLogger::AnyMessage);
    client.connectToServer(USERNAME, PASSWORD);


 //   QObject::connect(&cont, SIGNAL(aclListReady()),&object,SLOT())

   // client.findExtension<QXmppDiscoveryManager>()->setClientCapabilitiesNode ("http://jabber.org/protocol/geoloc+notify");;
    return app->exec();
}
