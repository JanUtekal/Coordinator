#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "xmppClient.h"
#include "QXmppLogger.h"
#include "interface.h"
#include <QtDeclarative>
//#include "QXmppPubSubManager.h"
#include "extension.h"

#define USERNAME "terrainuser1@jabber.cz"

#define PASSWORD "asasasd"



int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    Interface iface;
    xmppClient client;

    Extension ex;
    client.addExtension(&ex);
    QObject::connect(&ex, SIGNAL(sendCoords(QString,QString,QString,QString)),&client,SLOT(getNewCoords(QString, QString, QString, QString)));

  //  QXmppPubSubManager pubsub;
  //  client.addExtension(pubsub);

    iface.setClient(&client);

    QDeclarativeContext *ctxt = viewer->rootContext();
    ctxt->setContextProperty("iface", &iface);
    QVariantList list;
    ctxt->setContextProperty("arr",list);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    viewer->setMainQmlFile(QLatin1String("qml/Diplomka/main.qml"));
    viewer->showExpanded();


    QObject::connect(&client,SIGNAL(updateUser(QString,QGeoCoordinate)),&iface,SLOT(updateUserPosition(QString,QGeoCoordinate)));

    QObject::connect(&client,SIGNAL(refresh()),&iface,SLOT(refreshPoints()));
    QObject::connect(&client,SIGNAL(sendPointFromCentral(QString)),&iface,SLOT(getPointFromCentral(QString)));
    QObject::connect(&client,SIGNAL(sendLineFromCentral(QString)),&iface,SLOT(getLineFromCentral(QString)));
  //  viewer.rootContext()->setContextProperty("iface", &iface);

    QObject::connect(&client,SIGNAL(setUserOffline(QString)),&iface,SLOT(setUserOffline(QString)));




    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::FileLogging);


   client.connectToServer(USERNAME, PASSWORD);


    return app->exec();
}
