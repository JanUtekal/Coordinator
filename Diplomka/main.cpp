#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "xmppclient.h"
#include <QXmppLogger.h>
#include "controller.h"
#include <QtDeclarative>
//#include "QXmppPubSubManager.h"
#include "extension.h"

#define USERNAME "terrainuser4@jabber.cz"

#define PASSWORD "asasasd"



int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    Controller cont;
    XmppClient client;

    Extension ex;
    client.addExtension(&ex);
    QObject::connect(&ex, SIGNAL(sendCoords(QString,QString,QString,QString)),&client,SLOT(getNewCoords(QString, QString, QString, QString)));

  //  QXmppPubSubManager pubsub;
  //  client.addExtension(pubsub);

    cont.setClient(&client);

    QDeclarativeContext *ctxt = viewer->rootContext();
    ctxt->setContextProperty("cont", &cont);
    QVariantList list;
    ctxt->setContextProperty("arr",list);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    viewer->setMainQmlFile(QLatin1String("qml/Diplomka/main.qml"));
    viewer->showExpanded();


    QObject::connect(&client,SIGNAL(updateUser(QString,QGeoCoordinate)),&cont,SLOT(updateUserPosition(QString,QGeoCoordinate)));

    QObject::connect(&client,SIGNAL(refresh()),&cont,SLOT(refreshPoints()));
    QObject::connect(&client,SIGNAL(sendPointFromCentral(QVector<QPointF>, QString, QString)),&cont,SLOT(getPointFromCentral(QVector<QPointF>, QString, QString)));
    QObject::connect(&client,SIGNAL(sendLineFromCentral(QVector<QPointF>, QString, QString)),&cont,SLOT(getLineFromCentral(QVector<QPointF>, QString, QString)));
    QObject::connect(&client,SIGNAL(sendPolygonFromCentral(QVector<QPointF>, QString, QString)),&cont,SLOT(getPolygonFromCentral(QVector<QPointF>, QString, QString)));
    QObject::connect(&client,SIGNAL(sendNote(Note)),&cont,SLOT(getNote(Note)));
    QObject::connect(&client,SIGNAL(sendNegativeObject(QString)),&cont,SLOT(getNegativeObject(QString)));
    //  viewer.rootContext()->setContextProperty("cont", &cont);

    QObject::connect(&client,SIGNAL(setUserOffline(QString)),&cont,SLOT(setUserOffline(QString)));




    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::FileLogging);


  // client.connectToServer(USERNAME, PASSWORD);
   QXmppConfiguration config;
   config.setJid(USERNAME);
   config.setPassword(PASSWORD);
   config.setAutoAcceptSubscriptions(true);
   config.setIgnoreSslErrors(true);

  // QXmppPresence pr;
  // pr.setCapabilityNode("http://jabber.org/protocol/geoloc");
  // client.addProperCapability(pr);
 //  QXmppDiscoveryManager d;
  // d.setClientCapabilitiesNode("http://jabber.org/protocol/geoloc");

   client.connectToServer(config);


   qDebug()<<"vypis";

    return app->exec();
}
