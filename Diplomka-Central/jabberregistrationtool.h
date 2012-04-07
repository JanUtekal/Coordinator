#ifndef JABBERREGISTRATIONTOOL_H
#define JABBERREGISTRATIONTOOL_H


#include <QObject>
#include <QSslSocket>
#include <QDomDocument>
#include <QtCore>
#include <QDebug>
#include <QTimer>

class JabberRegistrationTool : public QSslSocket
{
    Q_OBJECT
public:
    explicit JabberRegistrationTool(QObject *parent = 0);



    void registerUser(QString name, QString password, QString captcha);

    void closeStream();
private:

    QString myform;
    bool connectionPending;
    int registrationPart;
    QTimer *timer;


signals:

    void sendCaptcha(QString captcha);
    void sendError(QString error);
    void sendSuccess();
public slots:
    void connectToServer();

private slots:


    void openStream();
    void newDataFromServerAreAvailabel();
    void keepConnection();

    bool sendData(const QByteArray &data);


};

#endif // JABBERREGISTRATIONTOOL_H
