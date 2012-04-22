#ifndef ACL_H
#define ACL_H
#include <QtCore>
#include <QDebug>
class Acl
{
public:
    Acl(QString id, QString name);
    void setId(QString id);
    void setName(QString name);
    void setFrom(QString from);
    void setTo(QString to);

    QString getId();
    QString getName();
    QString getFrom();
    QString getTo();


private:
    QString id;
    QString name;
    QString from;
    QString to;
};

#endif // ACL_H
