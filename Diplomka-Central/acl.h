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

    QString getId();
    QString getName();

private:
    QString id;
    QString name;
};

#endif // ACL_H
