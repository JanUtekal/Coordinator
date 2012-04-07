/*
Tato trida vychazi z Tomáš Vaòák: Klient XMPP v Nokia Qt SDK, bakaláøská práce, Brno, FIT VUT v Brnì,
2011
*/

#include "jabberregistrationtool.h"

JabberRegistrationTool::JabberRegistrationTool(QObject *parent) :
    QSslSocket(parent)
{
      connect(this, SIGNAL(connected()), this, SLOT(openStream()));

      connect(this, SIGNAL(readyRead()), SLOT(newDataFromServerAreAvailabel()));


      connectionPending=false;
      registrationPart=0;
      timer = new QTimer();
      connect(timer,SIGNAL(timeout()),this,SLOT(keepConnection()));


}
void JabberRegistrationTool::openStream(){
    QByteArray data;
    data.append("<?xml version='1.0'?>\n");
    data.append("<stream:stream\n");
    data.append(QString().append("\tto='").append("jabber.cz").append("'\n"));
    data.append("\tversion='1.0'\n");
    data.append("\txmlns='jabber:client'\n");
    data.append("\txmlns:stream='http://etherx.jabber.org/streams'> ");


    qDebug() << "bude se odesilat openStream()";
    sendData(data);
    qDebug() << "openStream() odeslan";

    QByteArray data2;
    data2.append("<iq type='get' id='reg1' to='jabber.cz'>");
    data2.append("<query xmlns='jabber:iq:register'/></iq>");
    sendData(data2);


}

void JabberRegistrationTool::newDataFromServerAreAvailabel()
{
   QByteArray data = readAll();
  // qDebug() << "server poslal: =========================================";
    qDebug() << "   " << data;
   if(data.contains("unreg")){
       qDebug()<<data;
   }

   if(data.contains("'CAPTCHA web page' var='url'><value>"))

    if(data.contains("<x xmlns='jabber:x:data'")){
        if(data.contains("required")){
            QString form=QString(data);
            QStringList list1=form.split("<x xmlns='jabber:x:data'");
            QStringList list2=list1.at(1).split("</x>");
            form=list2.at(0);
            form.prepend("<x xmlns='jabber:x:data'");
            form.append("</x>");
            myform=form;
            QStringList list3=form.split("'CAPTCHA web page' var='url'><value>");
            QStringList list4=list3.at(1).split("</value>");
           // captcha=list4.at(0);
         //   qDebug()<<list4.at(0);
            emit sendCaptcha(list4.at(0));

            timer->setInterval(30000);
            timer->start();
        } else if(!data.contains("error")) {
            if(registrationPart==2){
                qDebug()<<"Registration probably successfull ";
                qDebug()<<data;
                this->closeStream();
                emit sendSuccess();
            }
        } else {
            qDebug()<<"ërror during registration";
            QString error=QString(data);
            error=error.split("<error code").at(1).split("</error>").at(0);
            error.prepend("<error code");
            error.append("</error>");

            qDebug()<<error;
            emit sendError(error);
        }



    }

    //handleData(data);
}

void JabberRegistrationTool::connectToServer(){

    if(connectionPending){
        this->closeStream();
        QTimer::singleShot(1000,this,SLOT(connectToServer()));
        connectionPending=false;
    } else {
        QString host="jabber.cz";
        this->connectToHost(host,5222);
        connectionPending=true;
        registrationPart=1;
    }
}

void JabberRegistrationTool::registerUser(QString name, QString password, QString captcha)
{
    timer->stop();

    QByteArray data;
    data.append("<iq type='set' id='reg1'><query xmlns='jabber:iq:register'>");

    QStringList list3=myform.split("<required/>");
    if(list3.length()==4){
        QString part1=list3.at(0);
        part1+=QString("<value>%1</value>").arg(name);
        QString part2=list3.at(1);
        part2+=QString("<value>%1</value>").arg(password);
        QString part3=list3.at(2);
        part3+=QString("<value>%1</value>").arg(captcha);
        QString part4=list3.at(3);
        QString finalForm=part1+part2+part3+part4;
        data.append(finalForm);
    } else {
        qDebug()<<"registration line does not have 3 required fields";
        return;
    }

    registrationPart=2;

    data.append("</query></iq>");

    sendData(data);

}

bool JabberRegistrationTool::sendData(const QByteArray &data)
{


 //   qDebug() << "odesilano: ==================================";
  //  qDebug() << "     " << data;

    return write(data) == data.size();
}

void JabberRegistrationTool::closeStream(){

    timer->stop();
    sendData("</stream:stream>");


}


void JabberRegistrationTool::keepConnection(){
    connectToServer();


}

